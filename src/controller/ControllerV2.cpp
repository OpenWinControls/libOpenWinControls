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

#include "ControllerV2.h"
#include "../Utils.h"
#include "../include/HIDUsageIDMap.h"
#include "../include/XinputUsageIDMap.h"

namespace OWC {
    ControllerV2::ControllerV2(const int controllerFeatures): Controller(controllerFeatures, 64, 64) {
        configBuf = new uint8_t[configBufLen];
        configData = configBuf + configHeaderSz;
        configDataI8 = reinterpret_cast<int8_t *>(configData);
        configDataU16 = reinterpret_cast<uint16_t *>(configData);

        std::memset(configBuf, 0, configBufLen);
    }

    ControllerV2::~ControllerV2() {
        delete[] configBuf;
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

    void ControllerV2::prepareSendBuffer(const CMD cmd, const int bytesCount) const {
        std::memset(sendBuf, 0, sendPacketLen);

        sendBuf[0] = 1; // id
        sendBuf[1] = static_cast<uint8_t>(cmd);
        sendBuf[2] = bytesCount;
    }

    bool ControllerV2::isCmdRejected() const {
        return respBuf[8] == 0xe2;
    }

    bool ControllerV2::isValidRespPacket() const {
        const int checksum = *reinterpret_cast<uint16_t *>(respBuf + 6);
        const int sum = getBytesSum(respBuf + 8, respPacketLen - 8);

        return checksum == sum;
    }

    bool ControllerV2::isChecksumValid() const {
        const int configSum = getBytesSum(configBuf, configBufLen);

        prepareSendBuffer(CMD::Checksum, 2);

        sendBuf[6] = 4; // checksum
        sendBuf[9] = 4; // unk

        if (!sendReadRequest() || isCmdRejected()) {
            if (logFn)
                writeLog(L"failed to get checksum");

            return false;
        }

        if (configSum != reinterpret_cast<uint16_t *>(respBuf)[5]) {
            if (logFn)
                writeLog(std::format(L"checksum mismatch: {:x} != {:x}", configSum, reinterpret_cast<uint16_t *>(respBuf)[5]));

            return false;
        }

        prepareSendBuffer(CMD::EndCmd);
        if (!sendReadRequest() || isCmdRejected()) {
            if (logFn)
                writeLog(L"failed end cmd");

            return false;
        }

        return true;
    }

    int ControllerV2::getBackButtonModeIdx(const int num) const {
        // btn 1 pos + btn num * btn struct size
        return 160 + ((num - 1) * 196);
    }

    int ControllerV2::getBackButtonKeyPos(const int num, const int slot) const {
        // btn 1 key 1 pos + btn num * u16 size to next btn key 1 + key slot offset
        return (82 + ((num - 1) * 98)) + ((slot - 1) * 3);
    }

    bool ControllerV2::readVersion() {
        if (!initReadCommunication()) {
            if (logFn)
                writeLog(L"failed to init communication");

            return false;
        }

        prepareSendBuffer(CMD::Version);

        if (!sendReadRequest() || isCmdRejected() || !isValidRespPacket())
            return false;

        version = std::make_pair(respBuf[12], respBuf[13]);
        return true;
    }

    bool ControllerV2::readConfig() {
        if (!initReadCommunication()) {
            if (logFn)
                writeLog(L"failed to init communication");

            return false;
        }

        prepareSendBuffer(CMD::Read, 2);

        // required args
        sendBuf[6] = 4; // checksum
        sendBuf[9] = 4; // unk

        if (!sendWriteRequest()) {
            if (logFn)
                writeLog(L"failed to request config data");

            return false;
        }

        for (int i=0; i<configBufLen;) {
            prepareRespBuffer();

            if (hid_get_input_report(gamepad, respBuf, respPacketLen) < 0) {
                if (logFn)
                    writeLog(hid_error(gamepad));

                return false;
            }

            if (logFn)
                writeLog(bufferToString(respBuf, respPacketLen));

            if (isCmdRejected()) {
                if (logFn)
                    writeLog(L"failed to read: interal error");

                return false;

            } else if (!isValidRespPacket()) {
                if (logFn)
                    writeLog(L"corrupted packet received, checksum failed");

                return false;
            }

            std::memcpy(configBuf + i, respBuf + 8, respBuf[2]);
            i += respBuf[2];
        }

        if (logFn)
            writeLog(bufferToString(configBuf, configBufLen));

        prepareSendBuffer(CMD::Init2);
        if (!sendReadRequest() || isCmdRejected()) {
            if (logFn)
                writeLog(L"failed to init checksum");

            return false;
        }

        return isChecksumValid();
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

        for (int i=0; i<configBufLen; i+=56) {
            const int bytesCount = std::min(configBufLen - i, 56);

            prepareSendBuffer(CMD::Write, bytesCount);
            std::memcpy(sendBuf + 8, configBuf + i, bytesCount);

            sendBufU16[2] = i; // page index
            sendBufU16[3] = getBytesSum(sendBuf + 8, bytesCount); // checksum

            if (!sendWriteRequest()) {
                if (logFn)
                    writeLog(L"failed to write config");

                return false;
            }
        }

        return isChecksumValid();
    }

    bool ControllerV2::resetConfig() const {
        // v2 has some kind of reset sequence, but this should do for most cases
        std::memcpy(configBuf + configHeaderSz, resetBuf, sizeof(resetBuf));
        return writeConfig();
    }

    EmulationMode ControllerV2::getEmulationMode() const {
        switch (configData[959]) {
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
                return setButtonKey(configDataU16, key);
            case Button::KBD_DPAD_DOWN:
                return setButtonKey(configDataU16 + 1, key);
            case Button::KBD_DPAD_LEFT:
                return setButtonKey(configDataU16 + 2, key);
            case Button::KBD_DPAD_RIGHT:
                return setButtonKey(configDataU16 + 3, key);
            case Button::KBD_START:
                return setButtonKey(configDataU16 + 4, key);
            case Button::KBD_SELECT:
                return setButtonKey(configDataU16 + 5, key);
            case Button::KBD_MENU:
                return setButtonKey(configDataU16 + 6, key);
            case Button::KBD_A:
                return setButtonKey(configDataU16 + 7, key);
            case Button::KBD_B:
                return setButtonKey(configDataU16 + 8, key);
            case Button::KBD_X:
                return setButtonKey(configDataU16 + 9, key);
            case Button::KBD_Y:
                return setButtonKey(configDataU16 + 10, key);
            case Button::KBD_L1:
                return setButtonKey(configDataU16 + 11, key);
            case Button::KBD_R1:
                return setButtonKey(configDataU16 + 12, key);
            case Button::KBD_L2:
                return setButtonKey(configDataU16 + 13, key);
            case Button::KBD_R2:
                return setButtonKey(configDataU16 + 14, key);
            case Button::KBD_L3:
                return setButtonKey(configDataU16 + 15, key);
            case Button::KBD_R3:
                return setButtonKey(configDataU16 + 16, key);
            case Button::KBD_LANALOG_UP:
                return setButtonKey(configDataU16 + 17, key);
            case Button::KBD_LANALOG_DOWN:
                return setButtonKey(configDataU16 + 18, key);
            case Button::KBD_LANALOG_LEFT:
                return setButtonKey(configDataU16 + 19, key);
            case Button::KBD_LANALOG_RIGHT:
                return setButtonKey(configDataU16 + 20, key);
            case Button::X_DPAD_UP:
                return setXinputKey(configDataU16 + 40, key);
            case Button::X_DPAD_DOWN:
                return setXinputKey(configDataU16 + 41, key);
            case Button::X_DPAD_LEFT:
                return setXinputKey(configDataU16 + 42, key);
            case Button::X_DPAD_RIGHT:
                return setXinputKey(configDataU16 + 43, key);
            case Button::X_START:
                return setXinputKey(configDataU16 + 44, key);
            case Button::X_SELECT:
                return setXinputKey(configDataU16 + 45, key);
            case Button::X_MENU:
                return setXinputKey(configDataU16 + 46, key);
            case Button::X_A:
                return setXinputKey(configDataU16 + 47, key);
            case Button::X_B:
                return setXinputKey(configDataU16 + 48, key);
            case Button::X_X:
                return setXinputKey(configDataU16 + 49, key);
            case Button::X_Y:
                return setXinputKey(configDataU16 + 50, key);
            case Button::X_L1:
                return setXinputKey(configDataU16 + 51, key);
            case Button::X_R1:
                return setXinputKey(configDataU16 + 52, key);
            case Button::X_L2:
                return setXinputKey(configDataU16 + 53, key);
            case Button::X_R2:
                return setXinputKey(configDataU16 + 54, key);
            case Button::X_L3:
                return setXinputKey(configDataU16 + 55, key);
            case Button::X_R3:
                return setXinputKey(configDataU16 + 56, key);
            case Button::X_LANALOG_UP:
                return setXinputKey(configDataU16 + 57, key);
            case Button::X_LANALOG_DOWN:
                return setXinputKey(configDataU16 + 58, key);
            case Button::X_LANALOG_LEFT:
                return setXinputKey(configDataU16 + 59, key);
            case Button::X_LANALOG_RIGHT:
                return setXinputKey(configDataU16 + 60, key);
            case Button::X_RANALOG_UP:
                return setXinputKey(configDataU16 + 61, key);
            case Button::X_RANALOG_DOWN:
                return setXinputKey(configDataU16 + 62, key);
            case Button::X_RANALOG_LEFT:
                return setXinputKey(configDataU16 + 63, key);
            case Button::X_RANALOG_RIGHT:
                return setXinputKey(configDataU16 + 64, key);
            default:
                break;
        }

        return false;
    }

    std::string ControllerV2::getButton(const Button btn) const {
        uint16_t key;

        switch (btn) {
            case Button::KBD_DPAD_UP:
                key = configDataU16[0];
                break;
            case Button::KBD_DPAD_DOWN:
                key = configDataU16[1];
                break;
            case Button::KBD_DPAD_LEFT:
                key = configDataU16[2];
                break;
            case Button::KBD_DPAD_RIGHT:
                key = configDataU16[3];
                break;
            case Button::KBD_START:
                key = configDataU16[4];
                break;
            case Button::KBD_SELECT:
                key = configDataU16[5];
                break;
            case Button::KBD_MENU:
                key = configDataU16[6];
                break;
            case Button::KBD_A:
                key = configDataU16[7];
                break;
            case Button::KBD_B:
                key = configDataU16[8];
                break;
            case Button::KBD_X:
                key = configDataU16[9];
                break;
            case Button::KBD_Y:
                key = configDataU16[10];
                break;
            case Button::KBD_L1:
                key = configDataU16[11];
                break;
            case Button::KBD_R1:
                key = configDataU16[12];
                break;
            case Button::KBD_L2:
                key = configDataU16[13];
                break;
            case Button::KBD_R2:
                key = configDataU16[14];
                break;
            case Button::KBD_L3:
                key = configDataU16[15];
                break;
            case Button::KBD_R3:
                key = configDataU16[16];
                break;
            case Button::KBD_LANALOG_UP:
                key = configDataU16[17];
                break;
            case Button::KBD_LANALOG_DOWN:
                key = configDataU16[18];
                break;
            case Button::KBD_LANALOG_LEFT:
                key = configDataU16[19];
                break;
            case Button::KBD_LANALOG_RIGHT:
                key = configDataU16[20];
                break;
            case Button::X_DPAD_UP:
                key = configDataU16[40];
                break;
            case Button::X_DPAD_DOWN:
                key = configDataU16[41];
                break;
            case Button::X_DPAD_LEFT:
                key = configDataU16[42];
                break;
            case Button::X_DPAD_RIGHT:
                key = configDataU16[43];
                break;
            case Button::X_START:
                key = configDataU16[44];
                break;
            case Button::X_SELECT:
                key = configDataU16[45];
                break;
            case Button::X_MENU:
                key = configDataU16[46];
                break;
            case Button::X_A:
                key = configDataU16[47];
                break;
            case Button::X_B:
                key = configDataU16[48];
                break;
            case Button::X_X:
                key = configDataU16[49];
                break;
            case Button::X_Y:
                key = configDataU16[50];
                break;
            case Button::X_L1:
                key = configDataU16[51];
                break;
            case Button::X_R1:
                key = configDataU16[52];
                break;
            case Button::X_L2:
                key = configDataU16[53];
                break;
            case Button::X_R2:
                key = configDataU16[54];
                break;
            case Button::X_L3:
                key = configDataU16[55];
                break;
            case Button::X_R3:
                key = configDataU16[56];
                break;
            case Button::X_LANALOG_UP:
                key = configDataU16[57];
                break;
            case Button::X_LANALOG_DOWN:
                key = configDataU16[58];
                break;
            case Button::X_LANALOG_LEFT:
                key = configDataU16[59];
                break;
            case Button::X_LANALOG_RIGHT:
                key = configDataU16[60];
                break;
            case Button::X_RANALOG_UP:
                key = configDataU16[61];
                break;
            case Button::X_RANALOG_DOWN:
                key = configDataU16[62];
                break;
            case Button::X_RANALOG_LEFT:
                key = configDataU16[63];
                break;
            case Button::X_RANALOG_RIGHT:
                key = configDataU16[64];
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

    void ControllerV2::setBackButtonMode(const int num, const BackButtonMode mode) const {
        switch (mode) {
            case BackButtonMode::Single:
                configData[getBackButtonModeIdx(num)] = 0;
                break;
            case BackButtonMode::Four:
                configData[getBackButtonModeIdx(num)] = 1;
                break;
            case BackButtonMode::Macro:
                configData[getBackButtonModeIdx(num)] = 2;
                break;
            default:
                break;
        }
    }

    BackButtonMode ControllerV2::getBackButtonMode(const int num) const {
        switch (configData[getBackButtonModeIdx(num)]) {
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
                configData[pos] &= 0xfb;
                break;
            case BackButtonMacroType::Xinput:
                configData[pos] |= 0x04;
                break;
            default:
                break;
        }
    }

    BackButtonMacroType ControllerV2::getBackButtonMacroType(const int num) const {
        return !!(configData[getBackButtonModeIdx(num)] & 0x04) ? BackButtonMacroType::Xinput : BackButtonMacroType::Keyboard;
    }*/

    void ControllerV2::setBackButtonActiveSlots(const int num, const uint8_t count) const {
        configData[getBackButtonModeIdx(num) + 1] = count;
    }

    int ControllerV2::getBackButtonActiveSlots(const int num) const {
        return configData[getBackButtonModeIdx(num) + 1];
    }

    bool ControllerV2::setBackButton(const int num, const int slot, const std::string &key) const {
        uint16_t *btn = configDataU16 + getBackButtonKeyPos(num, slot);

        return setButtonKey(btn, key) || setXinputKey(btn, key);
    }

    std::string ControllerV2::getBackButton(const int num, const int slot) const {
        const uint16_t key = configDataU16[getBackButtonKeyPos(num, slot)];

        if (HIDUsageIDMap.contains(key))
            return HIDUsageIDMap.at(key);
        else if (XinputUsageIDMap.contains(key))
            return XinputUsageIDMap.at(key);

        if (logFn)
            writeLog(std::format(L"failed to find key: {:x}", key));

        return "";
    }

    void ControllerV2::setBackButtonStartTime(const int num, const int slot, const int timeMs) const {
        configDataU16[getBackButtonKeyPos(num, slot) + 1] = timeMs;
    }

    int ControllerV2::getBackButtonStartTime(const int num, const int slot) const {
        return configDataU16[getBackButtonKeyPos(num, slot) + 1];
    }

    void ControllerV2::setBackButtonHoldTime(const int num, const int slot, const int timeMs) const {
        configDataU16[getBackButtonKeyPos(num, slot) + 2] = timeMs;
    }

    int ControllerV2::getBackButtonHoldTime(const int num, const int slot) const {
        return configDataU16[getBackButtonKeyPos(num, slot) + 2];
    }

    void ControllerV2::setRumble(const RumbleMode mode) const {
        switch (mode) {
            case RumbleMode::Off:
                configData[944] = 0;
                break;
            case RumbleMode::Low:
                configData[944] = 1;
                break;
            case RumbleMode::High:
                configData[944] = 2;
                break;
            default:
                break;
        }
    }

    RumbleMode ControllerV2::getRumbleMode() const {
        switch (configData[944]) {
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
        // unused, do nothing
    }

    LedMode ControllerV2::getLedMode() const {
        // unused
        return LedMode::Unknown;
    }

    void ControllerV2::setLedColor(const int r, const int g, const int b) const {
        // unused, do nothing
    }

    std::tuple<int, int, int> ControllerV2::getLedColor() const {
        // unused
        return {0, 0, 0};
    }

    void ControllerV2::setAnalogCenter(const int center, const bool left) const {
        setAnalogDeadzone(configDataI8 + (left ? 949:951), center);
    }

    int ControllerV2::getAnalogCenter(const bool left) const {
        return configDataI8[left ? 949:951];
    }

    void ControllerV2::setAnalogBoundary(const int boundary, const bool left) const {
        setAnalogDeadzone(configDataI8 + (left ? 950:952), boundary);
    }

    int ControllerV2::getAnalogBoundary(const bool left) const {
        return configDataI8[left ? 950:952];
    }
}
