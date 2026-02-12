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

#include "ControllerV1.h"
#include "../Utils.h"

#ifdef _WIN32
#define HID_SEND_REPORT hid_send_output_report
#else
#define HID_SEND_REPORT hid_send_feature_report
#endif

namespace OWC {
    ControllerV1::ControllerV1(const int controllerFeatures) {
        dpadUp_offt = 0;
        dpadDown_offt = 1;
        dpadLeft_offt = 2;
        dpadRight_offt = 3;
        a_offt = 4;
        b_offt = 5;
        x_offt = 6;
        y_offt = 7;
        leftAnalogUp_offt = 8;
        leftAnalogDown_offt = 9;
        leftAnalogLeft_offt = 10;
        leftAnalogRight_offt = 11;
        l3_offt = 12;
        r3_offt = 13;
        start_offt = 14;
        select_offt = 15;
        menu_offt = 16;
        l1_offt = 17;
        r1_offt = 18;
        l2_offt = 19;
        r2_offt = 20;
        backBtnLeftKey1_offt = 25;
        backBtnLeftKey2_offt = 26;
        backBtnLeftKey3_offt = 27;
        backBtnLeftKey4_offt = 28;
        backBtnRightKey1_offt = 29;
        backBtnRightKey2_offt = 30;
        backBtnRightKey3_offt = 31;
        backBtnRightKey4_offt = 32;
        rumbleMode_offt = 33;
        backBtnLeftKey1Delay_offt = 40;
        backBtnLeftKey2Delay_offt = 41;
        backBtnLeftKey3Delay_offt = 42;
        backBtnLeftKey4Delay_offt = 43;
        backBtnRightKey1Delay_offt = 44;
        backBtnRightKey2Delay_offt = 45;
        backBtnRightKey3Delay_offt = 46;
        backBtnRightKey4Delay_offt = 47;
        ledMode_offt = 68;
        ledColorR_offt = 69;
        ledColorG_offt = 70;
        ledColorB_offt = 71;
        leftAnalogCenter_offt = 72;
        leftAnalogBoundary_offt = 73;
        rightAnalogCenter_offt = 74;
        rightAnalogBoundary_offt = 75;

        sendBuf = new uint8_t[sendPacketLen];
        respBuf = new uint8_t[respPacketLen];
        configBuf = new uint8_t[configBufLen];
        configi8 = reinterpret_cast<int8_t *>(configBuf);
        configu16 = reinterpret_cast<uint16_t *>(configBuf);
        features = controllerFeatures;

        std::memset(configBuf, 0, configBufLen);
    }

    ControllerV1::~ControllerV1() {
        delete[] sendBuf;
        delete[] respBuf;
    }

    // this call also puts version numbers into resp buffer
    bool ControllerV1::initCommunication(const Mode mode) const {
        prepareSendPacket(mode, CMD::Init);

        return sendReadRequest() && (respBuf[8] == 0xaa);
    }

    bool ControllerV1::sendReadRequest() const {
        prepareRespBuffer();
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

        writeLog(bufferToString(respBuf, respPacketLen));
        return true;
    }

    bool ControllerV1::sendWriteRequest() const {
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

    int ControllerV1::calcConfigChecksum(const uint8_t *buf) const {
        int ret = 0;

        for (int i=0; i<configBufLen; ++i)
            ret += buf[i];

        return ret;
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

        if (!isConfigValid(calcConfigChecksum(configBuf), Mode::Read)) {
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

        if (!isConfigValid(calcConfigChecksum(configBuf), Mode::Write)) {
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

    bool ControllerV1::isConfigValid(const int configChecksum, const Mode mode) const {
        prepareSendPacket(mode, CMD::Checksum);

        if (!sendReadRequest()) {
            if (logFn)
                logFn(L"failed to send checksum request");

            return false;
        }

        return (reinterpret_cast<uint16_t *>(respBuf)[12]) == configChecksum;
    }
}
