/*
 * This file is part of libOpenWinControls.
 * Copyright (C) 2026 kylon
 *
 * libOpenWinControls is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libOpenWinControls is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <format>
#include <cstring>
#include <algorithm>

#include "ControllerV1.h"
#include "../Utils.h"
#include "../include/HIDUsageIDMap.h"

#ifdef _WIN32
#define HID_SEND_REPORT hid_send_output_report
#else
#define HID_SEND_REPORT hid_send_feature_report
#endif

namespace OWC {
    ControllerV1::ControllerV1(const int controllerFeatures) {
        sendBuf = new uint8_t[sendPacketLen];
        respBuf = new uint8_t[respPacketLen];
        configBuf = new uint8_t[configBufLen];
        configI8 = reinterpret_cast<int8_t *>(configBuf);
        configU16 = reinterpret_cast<uint16_t *>(configBuf);
        features = controllerFeatures;

        std::memset(configBuf, 0, configBufLen);
    }

    ControllerV1::~ControllerV1() {
        delete[] sendBuf;
        delete[] respBuf;
        delete[] configBuf;
    }

    // this call also puts version numbers into resp buffer
    bool ControllerV1::initCommunication(const Mode mode) const {
        prepareSendPacket(mode, CMD::Init);

        return sendReadRequest() && (respBuf[8] == 0xaa);
    }

    bool ControllerV1::sendReadRequest() const {
        prepareRespBuffer();

        if (logFn)
            writeLog(bufferToString(sendBuf, sendPacketLen));

        if (HID_SEND_REPORT(gamepad, sendBuf, sendPacketLen) < 0) {
            if (logFn)
                writeLog(hid_error(gamepad));

            return false;
        }

        if (hid_get_input_report(gamepad, respBuf, respPacketLen) < 0) {
            if (logFn)
                writeLog(hid_error(gamepad));

            return false;
        }

        if (logFn)
            writeLog(bufferToString(respBuf, respPacketLen));

        return true;
    }

    bool ControllerV1::sendWriteRequest() const {
        if (logFn)
            writeLog(bufferToString(sendBuf, sendPacketLen));

        if (HID_SEND_REPORT(gamepad, sendBuf, sendPacketLen) < 0) {
            if (logFn)
                writeLog(hid_error(gamepad));

            return false;
        }

        return true;
    }

    void ControllerV1::prepareSendPacket(const Mode mode, const CMD cmd, const uint8_t page) const {
        const uint8_t umode = static_cast<uint8_t>(mode);
        const uint8_t ucmd = static_cast<uint8_t>(cmd);

        std::memset(sendBuf, 0, sendPacketLen);

        sendBuf[0] = 1; // report id
        sendBuf[1] = 0xa5; // const
        sendBuf[3] = 0x5a; // const inverted

        // set mode and cmd, packed to the same byte
        sendBuf[2] |= umode << 4;
        sendBuf[2] |= ucmd;
        sendBuf[4] |= (umode ^ 0xf) << 4; // mode inverted
        sendBuf[4] |= ucmd ^ 0xf; // cmd inverted

        sendBuf[6] = page;
    }

    void ControllerV1::prepareRespBuffer() const {
        std::memset(respBuf, 0, respPacketLen);

        respBuf[0] = 1; // report id
    }

    bool ControllerV1::isConfigValid(const int configChecksum, const Mode mode) const {
        prepareSendPacket(mode, CMD::Checksum);

        if (!sendReadRequest()) {
            if (logFn)
                writeLog(L"failed to send checksum request");

            return false;
        }

        return (reinterpret_cast<uint16_t *>(respBuf)[12]) == configChecksum;
    }

    void ControllerV1::parseVersion() {
        xVersion = std::make_pair(respBuf[9], respBuf[10]);
        kVersion = std::make_pair(respBuf[11], respBuf[12]);
    }

    bool ControllerV1::readConfig() {
        if (!initCommunication(Mode::Read)) {
            if (logFn)
                writeLog(L"failed to read version");

            return false;
        }

        parseVersion();

        prepareSendPacket(Mode::Read, CMD::ReadWrite);
        if (!sendReadRequest()) {
            if (logFn)
                writeLog(L"failed to read config");

            return false;
        }

        std::memcpy(configBuf, respBuf, respPacketLen);

        prepareSendPacket(Mode::Read, CMD::ReadWrite, 1);
        if (!sendReadRequest()) {
            if (logFn)
                writeLog(L"failed to read config");

            return false;
        }

        // real packet size is 64, start from there
        std::memcpy(configBuf + respPacketLen - 1, respBuf, respPacketLen);

        if (!isConfigValid(getBytesSum(configBuf, configBufLen), Mode::Read)) {
            if (logFn)
                writeLog(L"config memory checksum does not match");

            return false;
        }

        return true;
    }

    bool ControllerV1::writeConfig() const {
        if (logFn)
            writeLog(bufferToString(configBuf, configBufLen));

        prepareSendPacket(Mode::Write, CMD::Init);

        if (!initCommunication(Mode::Write)) {
            if (logFn)
                writeLog(L"failed to write config");

            return false;
        }

        for (int i=0,j=0; i<8; ++i,j+=16) {
            prepareSendPacket(Mode::Write, CMD::ReadWrite, i);

            std::memcpy(sendBuf + 8, configBuf + j, 16);

            if (!sendWriteRequest())
                return false;
        }

        if (!isConfigValid(getBytesSum(configBuf, configBufLen), Mode::Write)) {
            if (logFn)
                writeLog(L"config memory checksum does not match");

            return false;
        }

        prepareSendPacket(Mode::Write, CMD::Commit);
        if (!sendWriteRequest()) {
            if (logFn)
                writeLog(L"failed to commit config to controller");

            return false;
        }

        return true;
    }

    bool ControllerV1::setButton(const Button btn, const std::string &key) const {
        switch (btn) {
            case Button::KBD_DPAD_UP:
                return setButtonKey(configU16, key);
            case Button::KBD_DPAD_DOWN:
                return setButtonKey(configU16 + 1, key);
            case Button::KBD_DPAD_LEFT:
                return setButtonKey(configU16 + 2, key);
            case Button::KBD_DPAD_RIGHT:
                return setButtonKey(configU16 + 3, key);
            case Button::KBD_A:
                return setButtonKey(configU16 + 4, key);
            case Button::KBD_B:
                return setButtonKey(configU16 + 5, key);
            case Button::KBD_X:
                return setButtonKey(configU16 + 6, key);
            case Button::KBD_Y:
                return setButtonKey(configU16 + 7, key);
            case Button::KBD_LANALOG_UP:
                return setButtonKey(configU16 + 8, key);
            case Button::KBD_LANALOG_DOWN:
                return setButtonKey(configU16 + 9, key);
            case Button::KBD_LANALOG_LEFT:
                return setButtonKey(configU16 + 10, key);
            case Button::KBD_LANALOG_RIGHT:
                return setButtonKey(configU16 + 11, key);
            case Button::KBD_L3:
                return setButtonKey(configU16 + 12, key);
            case Button::KBD_R3:
                return setButtonKey(configU16 + 13, key);
            case Button::KBD_START:
                return setButtonKey(configU16 + 14, key);
            case Button::KBD_SELECT:
                return setButtonKey(configU16 + 15, key);
            case Button::KBD_MENU:
                return setButtonKey(configU16 + 16, key);
            case Button::KBD_L1:
                return setButtonKey(configU16 + 17, key);
            case Button::KBD_R1:
                return setButtonKey(configU16 + 18, key);
            case Button::KBD_L2:
                return setButtonKey(configU16 + 19, key);
            case Button::KBD_R2:
                return setButtonKey(configU16 + 20, key);
            default:
                break;
        }

        return false;
    }

    std::string ControllerV1::getButton(const Button btn) const {
        uint16_t key;

        switch (btn) {
            case Button::KBD_DPAD_UP:
                key = configU16[0];
                break;
            case Button::KBD_DPAD_DOWN:
                key = configU16[1];
                break;
            case Button::KBD_DPAD_LEFT:
                key = configU16[2];
                break;
            case Button::KBD_DPAD_RIGHT:
                key = configU16[3];
                break;
            case Button::KBD_A:
                key = configU16[4];
                break;
            case Button::KBD_B:
                key = configU16[5];
                break;
            case Button::KBD_X:
                key = configU16[6];
                break;
            case Button::KBD_Y:
                key = configU16[7];
                break;
            case Button::KBD_LANALOG_UP:
                key = configU16[8];
                break;
            case Button::KBD_LANALOG_DOWN:
                key = configU16[9];
                break;
            case Button::KBD_LANALOG_LEFT:
                key = configU16[10];
                break;
            case Button::KBD_LANALOG_RIGHT:
                key = configU16[11];
                break;
            case Button::KBD_L3:
                key = configU16[12];
                break;
            case Button::KBD_R3:
                key = configU16[13];
                break;
            case Button::KBD_START:
                key = configU16[14];
                break;
            case Button::KBD_SELECT:
                key = configU16[15];
                break;
            case Button::KBD_MENU:
                key = configU16[16];
                break;
            case Button::KBD_L1:
                key = configU16[17];
                break;
            case Button::KBD_R1:
                key = configU16[18];
                break;
            case Button::KBD_L2:
                key = configU16[19];
                break;
            case Button::KBD_R2:
                key = configU16[20];
                break;
            default:
                return "";
        }

        try {
            return HIDUsageIDMap.at(key);

        } catch (const std::out_of_range &ex) {
            if (logFn)
                writeLog(std::format(L"failed to find key: {:x}", key));

            return "";
        }
    }

    bool ControllerV1::setBackButton(const int num, const int slot, const std::string &key) const {
        const int pos = (num == 1 ? 25:29) + std::clamp(slot, 1, 4) - 1;

        return setButtonKey(configU16 + pos, key);
    }

    std::string ControllerV1::getBackButton(const int num, const int slot) const {
        const int pos = (num == 1 ? 25:29) + std::clamp(slot, 1, 4) - 1;

        try {
            return HIDUsageIDMap.at(configU16[pos]);

        } catch (const std::out_of_range &ex) {
            if (logFn)
                writeLog(std::format(L"failed to find key: {:x}", configU16[pos]));

            return "";
        }
    }

    void ControllerV1::setBackButtonStartTime(const int num, const int slot, const int timeMs) const {
        const int pos = (num == 1 ? 40:44) + std::clamp(slot, 1, 4) - 1;

        setBackButtonTime(configU16 + pos, timeMs);
    }

    int ControllerV1::getBackButtonStartTime(const int num, const int slot) const {
        const int pos = (num == 1 ? 40:44) + std::clamp(slot, 1, 4) - 1;

        return configU16[pos];
    }

    void ControllerV1::setRumble(const RumbleMode mode) const {
        switch (mode) {
            case RumbleMode::Off:
                configBuf[66] = 0;
                break;
            case RumbleMode::Low:
                configBuf[66] = 1;
                break;
            case RumbleMode::High:
                configBuf[66] = 2;
                break;
            default:
                break;
        }
    }

    RumbleMode ControllerV1::getRumbleMode() const {
        switch (configBuf[66]) {
            case 0:
                return RumbleMode::Off;
            case 1:
                return RumbleMode::Low;
            case 2:
                return RumbleMode::High;
            default:
                break;
        }

        return RumbleMode::Unknown;
    }

    void ControllerV1::setLedMode(const LedMode mode) const {
        switch (mode) {
            case LedMode::Off: {
                configBuf[68] = 0;
                setLedColor(0, 0, 0);
            }
                break;
            case LedMode::Solid:
                configBuf[68] = 1;
                break;
            case LedMode::Breathe:
                configBuf[68] = 0x11;
                break;
            case LedMode::Rotate: {
                configBuf[68] = 0x21;
                setLedColor(0xff, 0, 0);
            }
            default:
                break;
        }
    }

    LedMode ControllerV1::getLedMode() const {
        switch (configBuf[68]) {
            case 0:
                return LedMode::Off;
            case 1:
                return LedMode::Solid;
            case 0x11:
                return LedMode::Breathe;
            case 0x21:
                return LedMode::Rotate;
            default:
                break;
        }

        return LedMode::Unknown;
    }

    void ControllerV1::setLedColor(const int r, const int g, const int b) const {
        if (configBuf[68] == 0 || configBuf[68] == 0x21)
            return;

        configBuf[69] = std::clamp(r, 0, 255);
        configBuf[70] = std::clamp(g, 0, 255);
        configBuf[71] = std::clamp(b, 0, 255);
    }

    std::tuple<int, int, int> ControllerV1::getLedColor() const {
        return std::make_tuple(configBuf[69], configBuf[70], configBuf[71]);
    }

    void ControllerV1::setAnalogCenter(const int center, const bool left) const {
        setAnalogDeadzone(configI8 + (left ? 72:74), center);
    }

    int ControllerV1::getAnalogCenter(const bool left) const {
        return configI8[left ? 72:74];
    }

    void ControllerV1::setAnalogBoundary(const int boundary, const bool left) const {
        setAnalogDeadzone(configI8 + (left ? 73:75), boundary);
    }

    int ControllerV1::getAnalogBoundary(const bool left) const {
        return configI8[left ? 73:75];
    }
}
