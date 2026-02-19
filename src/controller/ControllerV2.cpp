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

#include "ControllerV2.h"
#include "../Utils.h"
#include "../include/HIDUsageIDMap.h"
#include "../include/XinputUsageIDMap.h"

#ifdef _WIN32
#define HID_SEND_REPORT hid_send_output_report
#else
#define HID_SEND_REPORT hid_send_feature_report
#endif

namespace OWC {
    ControllerV2::ControllerV2(const int controllerFeatures) {
        sendBuf = new uint8_t[sendPacketLen];
        respBuf = new uint8_t[respPacketLen];
        configBuf = new uint8_t[configBufLen];
        configI8 = reinterpret_cast<int8_t *>(configBuf);
        configU16 = reinterpret_cast<uint16_t *>(configBuf);
        features = controllerFeatures;

        std::memset(configBuf, 0, configBufLen);
    }

    ControllerV2::~ControllerV2() {
        delete[] sendBuf;
        delete[] respBuf;
        delete[] configBuf;
    }

    bool ControllerV2::readVersion() {
        prepareSendBuffer(CMD::Version);

        if (!sendReadRequest() || !isValidRespPacket())
            return false;

        version = std::make_pair(respBuf[12], respBuf[13]);
        return true;
    }

    bool ControllerV2::initReadCommunication() const {
        prepareSendBuffer(CMD::Init1);

        if (!sendReadRequest() || respBuf[8] != 0xaa)
            return false;

        sendBuf[1] = static_cast<uint8_t>(CMD::Init2);

        if (!sendReadRequest() || respBuf[8] != 0xaa)
            return false;

        return true;
    }

    bool ControllerV2::initWriteCommunication() const {
        prepareSendBuffer(CMD::Init1);

        return sendReadRequest() && respBuf[8] == 0xaa;
    }

    bool ControllerV2::sendReadRequest(int *respBytesCount) const {
        int ret = 0;

        prepareRespBuffer();
        writeLog(bufferToString(sendBuf, sendPacketLen));

        if (HID_SEND_REPORT(gamepad, sendBuf, sendPacketLen) < 0) {
            if (logFn)
                writeLog(hid_error(gamepad));

            return false;
        }

        ret = hid_get_input_report(gamepad, respBuf, respPacketLen);
        if (ret < 0) {
            if (logFn)
                writeLog(hid_error(gamepad));

            return false;
        }

        if (respBytesCount != nullptr)
            *respBytesCount = ret;

        writeLog(bufferToString(respBuf, respPacketLen));
        return true;
    }

    bool ControllerV2::sendWriteRequest() const {
        writeLog(bufferToString(sendBuf, sendPacketLen));

        if (HID_SEND_REPORT(gamepad, sendBuf, sendPacketLen) < 0) {
            if (logFn)
                writeLog(hid_error(gamepad));

            return false;
        }

        return true;
    }

    void ControllerV2::prepareSendBuffer(const CMD cmd) const {
        std::memset(sendBuf, 0, sendPacketLen);

        sendBuf[0] = 1; // id
        sendBuf[1] = static_cast<uint8_t>(cmd);
    }

    void ControllerV2::prepareRespBuffer() const {
        std::memset(respBuf, 0, respPacketLen);

        respBuf[0] = 1; // report id
    }

    bool ControllerV2::isValidRespPacket() const {
        const int checksum = *reinterpret_cast<uint16_t *>(respBuf + 6);
        const int sum = getBytesSum(respBuf + 8, respPacketLen - 8);

        return checksum == sum;
    }

    int ControllerV2::getBackButtonModeIdx(const int num) const {
        // btn 1 pos + btn num * btn struct size
        return 160 + ((num - 1) * 196);
    }

    int ControllerV2::getBackButtonKeyPos(const int num, const int slot) const {
        // btn 1 key 1 pos + btn num * u16 size to next btn key 1 + key slot offset
        return (82 + ((num - 1) * 98)) + ((slot - 1) * 3);
    }

    bool ControllerV2::readConfig() {
        int respBytesCnt;

        if (!initReadCommunication()) {
            if (logFn)
                writeLog(L"failed to init communication");

            return false;
        }

        if (!readVersion()) {
            if (logFn)
                writeLog(L"failed to read version");

            return false;
        }

        prepareSendBuffer(CMD::Read);

        // required args
        sendBuf[2] = 2; // unk
        sendBuf[6] = 4; // checksum
        sendBuf[9] = 4; // unk

        if (!sendReadRequest(&respBytesCnt) || respBuf[8] == 0xe2 || !isValidRespPacket()) {
            if (logFn)
                writeLog(L"failed to start config read request");

            return false;
        }

        // copy request packet header
        std::memcpy(writeReqHeader, respBuf + 8, sizeof(writeReqHeader));

        // copy first chunck of the config
        std::memcpy(configBuf, respBuf + 20, respBytesCnt - 20);

        for (int i=(respBytesCnt-20); i<0x3f0; i+=(respBytesCnt-8)) {
            prepareRespBuffer();

            respBytesCnt = hid_get_input_report(gamepad, respBuf, respPacketLen);
            if (respBytesCnt < 0) {
                if (logFn)
                    writeLog(hid_error(gamepad));

                return false;
            }

            writeLog(bufferToString(respBuf, respPacketLen));

            if (!isValidRespPacket()) {
                if (logFn)
                    writeLog(L"corrupted packet received, checksum failed");

                return false;
            }

            std::memcpy(configBuf + i, respBuf + 8, respBytesCnt - 8);
        }

        if (logFn)
            writeLog(bufferToString(configBuf, configBufLen));

        return true;
    }

    bool ControllerV2::writeConfig() const {
        uint16_t *sendBufU16 = reinterpret_cast<uint16_t *>(sendBuf);

        if (!initWriteCommunication()) {
            if (logFn)
                writeLog(L"failed to init communication");

            return false;
        }

        if (logFn)
            writeLog(bufferToString(configBuf, configBufLen));

        prepareSendBuffer(CMD::Write);

        // prepare write request packet
        sendBuf[2] = 0x38; // unk
        std::memcpy(sendBuf + 8, writeReqHeader, sizeof(writeReqHeader));
        std::memcpy(sendBuf + 20, configBuf, 44);
        sendBufU16[3] = getBytesSum(sendBuf + 8, sendPacketLen - 8); // checksum

        if (!sendWriteRequest()) {
            if (logFn)
                logFn(L"failed to start write config request");

            return false;
        }

        for (int i=56,j=44; i<=0x3f0; i+=56,j+=56) {
            prepareSendBuffer(CMD::Write);

            sendBuf[2] = i == 0x3f0 ? 0x10 : 0x38;
            std::memcpy(sendBuf + 8, configBuf + j, std::clamp(configBufLen - j, 0, 56));
            sendBufU16[2] = i; // page index
            sendBufU16[3] = getBytesSum(sendBuf + 8, sendPacketLen - 8);

            if (!sendWriteRequest()) {
                if (logFn)
                    writeLog(L"failed to write config");

                return false;
            }
        }

        prepareSendBuffer(CMD::Commit1);

        sendBuf[2] = 2; // unk
        sendBuf[6] = 4; // checksum
        sendBuf[9] = 4; // unk

        if (!sendWriteRequest()) {
            if (logFn)
                writeLog(L"failed to prepare config commit");

            return false;
        }

        prepareSendBuffer(CMD::Commit2);
        if (!sendWriteRequest()) {
            if (logFn)
                writeLog(L"failed to commit config");

            return false;
        }

        return true;
    }

    EmulationMode ControllerV2::getEmulationMode() const {
        switch (configBuf[959]) {
            case 0:
                return EmulationMode::Xinput;
            case 1:
                return EmulationMode::KeyboardMouse;
            case 2:
                return EmulationMode::KeyboardSpecial;
            default:
                break;
        }

        return EmulationMode::Unknown;
    }

    bool ControllerV2::setButton(const Button btn, const std::string &key) const {
        switch (btn) {
            case Button::KBD_DPAD_UP:
                return setButtonKey(configU16, key);
            case Button::KBD_DPAD_DOWN:
                return setButtonKey(configU16 + 1, key);
            case Button::KBD_DPAD_LEFT:
                return setButtonKey(configU16 + 2, key);
            case Button::KBD_DPAD_RIGHT:
                return setButtonKey(configU16 + 3, key);
            case Button::KBD_START:
                return setButtonKey(configU16 + 4, key);
            case Button::KBD_SELECT:
                return setButtonKey(configU16 + 5, key);
            case Button::KBD_MENU:
                return setButtonKey(configU16 + 6, key);
            case Button::KBD_A:
                return setButtonKey(configU16 + 7, key);
            case Button::KBD_B:
                return setButtonKey(configU16 + 8, key);
            case Button::KBD_X:
                return setButtonKey(configU16 + 9, key);
            case Button::KBD_Y:
                return setButtonKey(configU16 + 10, key);
            case Button::KBD_L1:
                return setButtonKey(configU16 + 11, key);
            case Button::KBD_R1:
                return setButtonKey(configU16 + 12, key);
            case Button::KBD_L2:
                return setButtonKey(configU16 + 13, key);
            case Button::KBD_R2:
                return setButtonKey(configU16 + 14, key);
            case Button::KBD_L3:
                return setButtonKey(configU16 + 15, key);
            case Button::KBD_R3:
                return setButtonKey(configU16 + 16, key);
            case Button::KBD_LANALOG_UP:
                return setButtonKey(configU16 + 17, key);
            case Button::KBD_LANALOG_DOWN:
                return setButtonKey(configU16 + 18, key);
            case Button::KBD_LANALOG_LEFT:
                return setButtonKey(configU16 + 19, key);
            case Button::KBD_LANALOG_RIGHT:
                return setButtonKey(configU16 + 20, key);
            case Button::X_DPAD_UP:
                return setXinputKey(configU16 + 40, key);
            case Button::X_DPAD_DOWN:
                return setXinputKey(configU16 + 41, key);
            case Button::X_DPAD_LEFT:
                return setXinputKey(configU16 + 42, key);
            case Button::X_DPAD_RIGHT:
                return setXinputKey(configU16 + 43, key);
            case Button::X_START:
                return setXinputKey(configU16 + 44, key);
            case Button::X_SELECT:
                return setXinputKey(configU16 + 45, key);
            case Button::X_MENU:
                return setXinputKey(configU16 + 46, key);
            case Button::X_A:
                return setXinputKey(configU16 + 47, key);
            case Button::X_B:
                return setXinputKey(configU16 + 48, key);
            case Button::X_X:
                return setXinputKey(configU16 + 49, key);
            case Button::X_Y:
                return setXinputKey(configU16 + 50, key);
            case Button::X_L1:
                return setXinputKey(configU16 + 51, key);
            case Button::X_R1:
                return setXinputKey(configU16 + 52, key);
            case Button::X_L2:
                return setXinputKey(configU16 + 53, key);
            case Button::X_R2:
                return setXinputKey(configU16 + 54, key);
            case Button::X_L3:
                return setXinputKey(configU16 + 55, key);
            case Button::X_R3:
                return setXinputKey(configU16 + 56, key);
            case Button::X_LANALOG_UP:
                return setXinputKey(configU16 + 57, key);
            case Button::X_LANALOG_DOWN:
                return setXinputKey(configU16 + 58, key);
            case Button::X_LANALOG_LEFT:
                return setXinputKey(configU16 + 59, key);
            case Button::X_LANALOG_RIGHT:
                return setXinputKey(configU16 + 60, key);
            case Button::X_RANALOG_UP:
                return setXinputKey(configU16 + 61, key);
            case Button::X_RANALOG_DOWN:
                return setXinputKey(configU16 + 62, key);
            case Button::X_RANALOG_LEFT:
                return setXinputKey(configU16 + 63, key);
            case Button::X_RANALOG_RIGHT:
                return setXinputKey(configU16 + 64, key);
            default:
                break;
        }

        return false;
    }

    std::string ControllerV2::getButton(const Button btn) const {
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
            case Button::KBD_START:
                key = configU16[4];
                break;
            case Button::KBD_SELECT:
                key = configU16[5];
                break;
            case Button::KBD_MENU:
                key = configU16[6];
                break;
            case Button::KBD_A:
                key = configU16[7];
                break;
            case Button::KBD_B:
                key = configU16[8];
                break;
            case Button::KBD_X:
                key = configU16[9];
                break;
            case Button::KBD_Y:
                key = configU16[10];
                break;
            case Button::KBD_L1:
                key = configU16[11];
                break;
            case Button::KBD_R1:
                key = configU16[12];
                break;
            case Button::KBD_L2:
                key = configU16[13];
                break;
            case Button::KBD_R2:
                key = configU16[14];
                break;
            case Button::KBD_L3:
                key = configU16[15];
                break;
            case Button::KBD_R3:
                key = configU16[16];
                break;
            case Button::KBD_LANALOG_UP:
                key = configU16[17];
                break;
            case Button::KBD_LANALOG_DOWN:
                key = configU16[18];
                break;
            case Button::KBD_LANALOG_LEFT:
                key = configU16[19];
                break;
            case Button::KBD_LANALOG_RIGHT:
                key = configU16[20];
                break;
            case Button::X_DPAD_UP:
                key = configU16[40];
                break;
            case Button::X_DPAD_DOWN:
                key = configU16[41];
                break;
            case Button::X_DPAD_LEFT:
                key = configU16[42];
                break;
            case Button::X_DPAD_RIGHT:
                key = configU16[43];
                break;
            case Button::X_START:
                key = configU16[44];
                break;
            case Button::X_SELECT:
                key = configU16[45];
                break;
            case Button::X_MENU:
                key = configU16[46];
                break;
            case Button::X_A:
                key = configU16[47];
                break;
            case Button::X_B:
                key = configU16[48];
                break;
            case Button::X_X:
                key = configU16[49];
                break;
            case Button::X_Y:
                key = configU16[50];
                break;
            case Button::X_L1:
                key = configU16[51];
                break;
            case Button::X_R1:
                key = configU16[52];
                break;
            case Button::X_L2:
                key = configU16[53];
                break;
            case Button::X_R2:
                key = configU16[54];
                break;
            case Button::X_L3:
                key = configU16[55];
                break;
            case Button::X_R3:
                key = configU16[56];
                break;
            case Button::X_LANALOG_UP:
                key = configU16[57];
                break;
            case Button::X_LANALOG_DOWN:
                key = configU16[58];
                break;
            case Button::X_LANALOG_LEFT:
                key = configU16[59];
                break;
            case Button::X_LANALOG_RIGHT:
                key = configU16[60];
                break;
            case Button::X_RANALOG_UP:
                key = configU16[61];
                break;
            case Button::X_RANALOG_DOWN:
                key = configU16[62];
                break;
            case Button::X_RANALOG_LEFT:
                key = configU16[63];
                break;
            case Button::X_RANALOG_RIGHT:
                key = configU16[64];
                break;
            default:
                return "";
        }

        if (HIDUsageIDMap.contains(key))
            return HIDUsageIDMap.at(key);
        else if (XinputUsageIDMap.contains(key))
            return XinputUsageIDMap.at(key);

        if (logFn)
            writeLog(std::format(L"failed to find key: {:x}", key));

        return "";
    }

    /*void ControllerV2::setBackButtonMode(const int num, const BackButtonMode mode) const {
        switch (mode) {
            case BackButtonMode::Single:
                configBuf[getBackButtonModeIdx(num)] = 0;
                break;
            case BackButtonMode::Four:
                configBuf[getBackButtonModeIdx(num)] = 1;
                break;
            case BackButtonMode::Macro:
                configBuf[getBackButtonModeIdx(num)] = 2;
                break;
            default:
                break;
        }
    }*/

    BackButtonMode ControllerV2::getBackButtonMode(const int num) const {
        switch (configBuf[getBackButtonModeIdx(num)]) {
            case 0:
            case 4: // xinput
                return BackButtonMode::Single;
            case 1:
            case 5: // xinput
                return BackButtonMode::Four;
            case 2:
            case 6: // xinput
                return BackButtonMode::Macro;
            default:
                break;
        }

        return BackButtonMode::Unknown;
    }

    /*void ControllerV2::setBackButtonMacroType(const int num, const BackButtonMacroType type) const {
        const int pos = getBackButtonModeIdx(num);

        switch (type) {
            case BackButtonMacroType::Keyboard:
                configBuf[pos] &= 0xfb;
                break;
            case BackButtonMacroType::Xinput:
                configBuf[pos] |= 0x04;
                break;
            default:
                break;
        }
    }

    BackButtonMacroType ControllerV2::getBackButtonMacroType(const int num) const {
        return !!(configBuf[getBackButtonModeIdx(num)] & 0x04) ? BackButtonMacroType::Xinput : BackButtonMacroType::Keyboard;
    }

    void ControllerV2::setBackButtonActiveSlots(const int num, const uint8_t count) const {
        configBuf[getBackButtonModeIdx(num) + 1] = count;
    }*/

    int ControllerV2::getBackButtonActiveSlots(const int num) const {
        return configBuf[getBackButtonModeIdx(num) + 1];
    }

    bool ControllerV2::setBackButton(const int num, const int slot, const std::string &key) const {
        uint16_t *btn = configU16 + getBackButtonKeyPos(num, slot);

        return setButtonKey(btn, key) || setXinputKey(btn, key);
    }

    std::string ControllerV2::getBackButton(const int num, const int slot) const {
        const uint16_t key = configU16[getBackButtonKeyPos(num, slot)];

        if (HIDUsageIDMap.contains(key))
            return HIDUsageIDMap.at(key);
        else if (XinputUsageIDMap.contains(key))
            return XinputUsageIDMap.at(key);

        if (logFn)
            writeLog(std::format(L"failed to find key: {:x}", key));

        return "";
    }

    void ControllerV2::setBackButtonStartTime(const int num, const int slot, const int timeMs) const {
        configU16[getBackButtonKeyPos(num, slot) + 1] = timeMs;
    }

    int ControllerV2::getBackButtonStartTime(const int num, const int slot) const {
        return configU16[getBackButtonKeyPos(num, slot) + 1];
    }

    void ControllerV2::setBackButtonHoldTime(const int num, const int slot, const int timeMs) const {
        configU16[getBackButtonKeyPos(num, slot) + 2] = timeMs;
    }

    int ControllerV2::getBackButtonHoldTime(const int num, const int slot) const {
        return configU16[getBackButtonKeyPos(num, slot) + 2];
    }

    void ControllerV2::setRumble(const RumbleMode mode) const {
        switch (mode) {
            case RumbleMode::Off:
                configBuf[944] = 0;
                break;
            case RumbleMode::Low:
                configBuf[944] = 1;
                break;
            case RumbleMode::High:
                configBuf[944] = 2;
                break;
            default:
                break;
        }
    }

    RumbleMode ControllerV2::getRumbleMode() const {
        switch (configBuf[944]) {
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

    void ControllerV2::setLedMode(const LedMode mode) const {
        // unsed for now, do nothing
    }

    LedMode ControllerV2::getLedMode() const {
        // unsed for now
        return LedMode::Unknown;
    }

    void ControllerV2::setLedColor(const int r, const int g, const int b) const {
        // unsed for now, do nothing
    }

    std::tuple<int, int, int> ControllerV2::getLedColor() const {
        // unsed for now
        return {0, 0, 0};
    }

    void ControllerV2::setAnalogCenter(const int center, const bool left) const {
        setAnalogDeadzone(configI8 + (left ? 949:951), center);
    }

    int ControllerV2::getAnalogCenter(const bool left) const {
        return configI8[left ? 949:951];
    }

    void ControllerV2::setAnalogBoundary(const int boundary, const bool left) const {
        setAnalogDeadzone(configI8 + (left ? 950:952), boundary);
    }

    int ControllerV2::getAnalogBoundary(const bool left) const {
        return configI8[left ? 950:952];
    }
}
