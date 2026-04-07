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
#include <chrono>
#include <thread>

#include "Controller.h"
#include "../Utils.h"

#ifdef _WIN32
#define HID_SEND_REPORT hid_send_output_report
#else
#define HID_SEND_REPORT hid_send_feature_report
#endif

namespace OWC {
    Controller::Controller(const int controllerFeatures, const int sendBufSz, const int respBufSz) {
        sendPacketLen = sendBufSz;
        respPacketLen = respBufSz;
        sendBuf = new uint8_t[sendPacketLen];
        respBuf = new uint8_t[respPacketLen];
        features = controllerFeatures;
    }

    Controller::~Controller() {
        if (gamepad)
            hid_close(gamepad);

        hid_exit();
        delete[] sendBuf;
        delete[] respBuf;
    }

    void Controller::prepareRespBuffer() const {
        std::memset(respBuf, 0, respPacketLen);

        respBuf[0] = 1; // report id
    }

    void Controller::writeLog(const std::wstring &msg, const std::source_location loc) const {
        logFn(std::format(L"{}:{}\n{}", strTowstr(loc.function_name()), loc.line(), msg));
    }

    bool Controller::sendReadRequest() const {
        using namespace std::chrono_literals;

        prepareRespBuffer();

        if (logFn)
            writeLog(bufferToString(sendBuf, sendPacketLen));

        if (HID_SEND_REPORT(gamepad, sendBuf, sendPacketLen) < 0) {
            if (logFn)
                writeLog(hid_error(gamepad));

            return false;
        }

        std::this_thread::sleep_for(0.05s);

        if (hid_get_input_report(gamepad, respBuf, respPacketLen) < 0) {
            if (logFn)
                writeLog(hid_error(gamepad));

            return false;
        }

        if (logFn)
            writeLog(bufferToString(respBuf, respPacketLen));

        return true;
    }

    bool Controller::sendWriteRequest() const {
        if (logFn)
            writeLog(bufferToString(sendBuf, sendPacketLen));

        if (HID_SEND_REPORT(gamepad, sendBuf, sendPacketLen) < 0) {
            if (logFn)
                writeLog(hid_error(gamepad));

            return false;
        }

        return true;
    }

    bool Controller::setButtonKey(uint16_t *btn, const std::string &key) const {
        uint16_t keycode;

        if (!findHIDKeycode(strToUpper(key), keycode))
            return false;

        *btn = keycode;
        return true;
    }

    bool Controller::setXinputKey(uint16_t *btn, const std::string &key) const {
        uint16_t keycode;

        if (!findXinputKeycode(strToUpper(key), keycode))
            return false;

        *btn = keycode;
        return true;
    }

    void Controller::setBackButtonTime(uint16_t *field, const int time) const {
        *field = std::clamp(time, 0, INT16_MAX - 1);
    }

    void Controller::setAnalogDeadzone(int8_t *field, const int value) const {
        *field = std::clamp(value, -10, 10);
    }

    bool Controller::init() {
        if (hid_init() != 0) {
            if (logFn)
                writeLog(hid_error(nullptr));

            return false;
        }

        struct hid_device_info *devInfo = hid_enumerate(getVID(), getPID());

        if (devInfo == nullptr) {
            if (logFn)
                writeLog(hid_error(nullptr));

            return false;
        }

        for (struct hid_device_info *dev=devInfo; dev; dev=dev->next) {
            if (dev->usage_page != 0xff00)
                continue;

            if (logFn)
                logFn(std::format(L"found gamepad: {} [{:x}:{:x}]", strTowstr(dev->path), getVID(), getPID()));

            gamepad = hid_open_path(dev->path);
            break;
        }

        if (gamepad == nullptr && logFn)
            writeLog(hid_error(nullptr));

        hid_free_enumeration(devInfo);
        return (gamepad != nullptr);
    }

    bool Controller::hasFeature(const int feature) const {
        return !!(features & feature);
    }
}
