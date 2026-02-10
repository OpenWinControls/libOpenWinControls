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
#include <algorithm>

#include "Controller.h"
#include "../Utils.h"
#include "../include/HIDUsageIDMap.h"

namespace OWC {
    Controller::~Controller() {
        if (gamepad)
            hid_close(gamepad);

        hid_exit();
        delete[] configBuf;
    }

    void Controller::writeLog(const std::wstring &msg, const std::source_location loc) const {
        logFn(std::format(L"{}:{}\n{}", strTowstr(loc.function_name()), loc.line(), msg));
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

    bool Controller::setButtonKey(const int offt, const std::string &key) const {
        uint16_t keycode;

        if (!findHIDKeycode(key, keycode))
            return false;

        configu16[offt] = keycode;
        return true;
    }

    void Controller::setBackButtonDelay(const int offt, const int delay) const {
        configu16[offt] = std::clamp(delay, 0, INT16_MAX - 1);
    }

    void Controller::setAnalogDeadzone(const int offt, const int value) const {
        configBuf[offt] = std::clamp(value, -10, 10);
    }

    bool Controller::hasFeature(const int feature) const {
        return !!(features & feature);
    }

    bool Controller::setDpadUp(const std::string &key) const {
        return setButtonKey(dpadUp_offt, key);
    }

    bool Controller::setDpadDown(const std::string &key) const {
        return setButtonKey(dpadDown_offt, key);
    }

    bool Controller::setDpadLeft(const std::string &key) const {
        return setButtonKey(dpadLeft_offt, key);
    }

    bool Controller::setDpadRight(const std::string &key) const {
        return setButtonKey(dpadRight_offt, key);
    }

    bool Controller::setA(const std::string &key) const {
        return setButtonKey(a_offt, key);
    }

    bool Controller::setB(const std::string &key) const {
        return setButtonKey(b_offt, key);
    }

    bool Controller::setX(const std::string &key) const {
        return setButtonKey(x_offt, key);
    }

    bool Controller::setY(const std::string &key) const {
        return setButtonKey(y_offt, key);
    }

    bool Controller::setL1(const std::string &key) const {
        return setButtonKey(l1_offt, key);
    }

    bool Controller::setL2(const std::string &key) const {
        return setButtonKey(l2_offt, key);
    }

    bool Controller::setL3(const std::string &key) const {
        return setButtonKey(l3_offt, key);
    }

    bool Controller::setR1(const std::string &key) const {
        return setButtonKey(r1_offt, key);
    }

    bool Controller::setR2(const std::string &key) const {
        return setButtonKey(r2_offt, key);
    }

    bool Controller::setR3(const std::string &key) const {
        return setButtonKey(r3_offt, key);
    }

    bool Controller::setStart(const std::string &key) const {
        return setButtonKey(start_offt, key);
    }

    bool Controller::setSelect(const std::string &key) const {
        return setButtonKey(select_offt, key);
    }

    bool Controller::setMenu(const std::string &key) const {
        return setButtonKey(menu_offt, key);
    }

    bool Controller::setLAnalogUp(const std::string &key) const {
        return setButtonKey(leftAnalogUp_offt, key);
    }

    bool Controller::setLAnalogDown(const std::string &key) const {
        return setButtonKey(leftAnalogDown_offt, key);
    }

    bool Controller::setLAnalogLeft(const std::string &key) const {
        return setButtonKey(leftAnalogLeft_offt, key);
    }

    bool Controller::setLAnalogRight(const std::string &key) const {
        return setButtonKey(leftAnalogRight_offt, key);
    }

    bool Controller::setLBack1(const std::string &key) const {
        return setButtonKey(backBtnLeftKey1_offt, key);
    }

    bool Controller::setLBack2(const std::string &key) const {
        return setButtonKey(backBtnLeftKey2_offt, key);
    }

    bool Controller::setLBack3(const std::string &key) const {
        return setButtonKey(backBtnLeftKey3_offt, key);
    }

    bool Controller::setLBack4(const std::string &key) const {
        return setButtonKey(backBtnLeftKey4_offt, key);
    }

    bool Controller::setRBack1(const std::string &key) const {
        return setButtonKey(backBtnRightKey1_offt, key);
    }

    bool Controller::setRBack2(const std::string &key) const {
        return setButtonKey(backBtnRightKey2_offt, key);
    }

    bool Controller::setRBack3(const std::string &key) const {
        return setButtonKey(backBtnRightKey3_offt, key);
    }

    bool Controller::setRBack4(const std::string &key) const {
        return setButtonKey(backBtnRightKey4_offt, key);
    }

    void Controller::setLBack1Delay(const int delay) const {
        setBackButtonDelay(backBtnLeftKey1Delay_offt, delay);
    }

    void Controller::setLBack2Delay(const int delay) const {
        setBackButtonDelay(backBtnLeftKey2Delay_offt, delay);
    }

    void Controller::setLBack3Delay(const int delay) const {
        setBackButtonDelay(backBtnLeftKey3Delay_offt, delay);
    }

    void Controller::setLBack4Delay(const int delay) const {
        setBackButtonDelay(backBtnLeftKey4Delay_offt, delay);
    }

    void Controller::setRBack1Delay(const int delay) const {
        setBackButtonDelay(backBtnRightKey1Delay_offt, delay);
    }

    void Controller::setRBack2Delay(const int delay) const {
        setBackButtonDelay(backBtnRightKey2Delay_offt, delay);
    }

    void Controller::setRBack3Delay(const int delay) const {
        setBackButtonDelay(backBtnRightKey3Delay_offt, delay);
    }

    void Controller::setRBack4Delay(const int delay) const {
        setBackButtonDelay(backBtnRightKey4Delay_offt, delay);
    }

    void Controller::setRumble(const std::string &mode) const {
        configBuf[rumbleMode_offt] = rumbleStrToRumbleMode(mode);
    }

    void Controller::setLAnalogCenter(const int center) const {
        setAnalogDeadzone(leftAnalogCenter_offt, center);
    }

    void Controller::setLAnalogBoundary(const int boundary) const {
        setAnalogDeadzone(leftAnalogBoundary_offt, boundary);
    }

    void Controller::setRAnalogCenter(const int center) const {
        setAnalogDeadzone(rightAnalogCenter_offt, center);
    }

    void Controller::setRAnalogBoundary(const int boundary) const {
        setAnalogDeadzone(rightAnalogBoundary_offt, boundary);
    }

    void Controller::setLedMode(const std::string &mode) const {
        configBuf[ledMode_offt] = ledModeStrToLedMode(mode);

        if (configBuf[ledMode_offt] == 0x21) // rotate also resets the color
            setLedColor(0xff, 0, 0);
    }

    void Controller::setLedColor(const int r, const int g, const int b) const {
        if (configBuf[ledMode_offt] == 0 || configBuf[ledMode_offt] == 0x21)
            return;

        configBuf[ledColorR_offt] = std::clamp(r, 0, 255);
        configBuf[ledColorG_offt] = std::clamp(g, 0, 255);
        configBuf[ledColorB_offt] = std::clamp(b, 0, 255);
    }

    std::string Controller::getDpadUp() const {
        return HIDUsageIDMap.at(configu16[dpadUp_offt]);
    }

    std::string Controller::getDpadDown() const {
        return HIDUsageIDMap.at(configu16[dpadDown_offt]);
    }

    std::string Controller::getDpadLeft() const {
        return HIDUsageIDMap.at(configu16[dpadLeft_offt]);
    }

    std::string Controller::getDpadRight() const {
        return HIDUsageIDMap.at(configu16[dpadRight_offt]);
    }

    std::string Controller::getA() const {
        return HIDUsageIDMap.at(configu16[a_offt]);
    }

    std::string Controller::getB() const {
        return HIDUsageIDMap.at(configu16[b_offt]);
    }

    std::string Controller::getX() const {
        return HIDUsageIDMap.at(configu16[x_offt]);
    }

    std::string Controller::getY() const {
        return HIDUsageIDMap.at(configu16[y_offt]);
    }

    std::string Controller::getL1() const {
        return HIDUsageIDMap.at(configu16[l1_offt]);
    }

    std::string Controller::getL2() const {
        return HIDUsageIDMap.at(configu16[l2_offt]);
    }

    std::string Controller::getL3() const {
        return HIDUsageIDMap.at(configu16[l3_offt]);
    }

    std::string Controller::getR1() const {
        return HIDUsageIDMap.at(configu16[r1_offt]);
    }

    std::string Controller::getR2() const {
        return HIDUsageIDMap.at(configu16[r2_offt]);
    }

    std::string Controller::getR3() const {
        return HIDUsageIDMap.at(configu16[r3_offt]);
    }

    std::string Controller::getStart() const {
        return HIDUsageIDMap.at(configu16[start_offt]);
    }

    std::string Controller::getSelect() const {
        return HIDUsageIDMap.at(configu16[select_offt]);
    }

    std::string Controller::getMenu() const {
        return HIDUsageIDMap.at(configu16[menu_offt]);
    }

    std::string Controller::getLAnalogUp() const {
        return HIDUsageIDMap.at(configu16[leftAnalogUp_offt]);
    }

    std::string Controller::getLAnalogDown() const {
        return HIDUsageIDMap.at(configu16[leftAnalogDown_offt]);
    }

    std::string Controller::getLAnalogLeft() const {
        return HIDUsageIDMap.at(configu16[leftAnalogLeft_offt]);
    }

    std::string Controller::getLAnalogRight() const {
        return HIDUsageIDMap.at(configu16[leftAnalogRight_offt]);
    }

    std::string Controller::getLBack1() const {
        return HIDUsageIDMap.at(configu16[backBtnLeftKey1_offt]);
    }

    std::string Controller::getLBack2() const {
        return HIDUsageIDMap.at(configu16[backBtnLeftKey2_offt]);
    }

    std::string Controller::getLBack3() const {
        return HIDUsageIDMap.at(configu16[backBtnLeftKey3_offt]);
    }

    std::string Controller::getLBack4() const {
        return HIDUsageIDMap.at(configu16[backBtnLeftKey4_offt]);
    }

    std::string Controller::getRBack1() const {
        return HIDUsageIDMap.at(configu16[backBtnRightKey1_offt]);
    }

    std::string Controller::getRBack2() const {
        return HIDUsageIDMap.at(configu16[backBtnRightKey2_offt]);
    }

    std::string Controller::getRBack3() const {
        return HIDUsageIDMap.at(configu16[backBtnRightKey3_offt]);
    }

    std::string Controller::getRBack4() const {
        return HIDUsageIDMap.at(configu16[backBtnRightKey4_offt]);
    }

    int Controller::getLBack1Delay() const {
        return configu16[backBtnLeftKey1Delay_offt];
    }

    int Controller::getLBack2Delay() const {
        return configu16[backBtnLeftKey2Delay_offt];
    }

    int Controller::getLBack3Delay() const {
        return configu16[backBtnLeftKey3Delay_offt];
    }

    int Controller::getLBack4Delay() const {
        return configu16[backBtnLeftKey4Delay_offt];
    }

    int Controller::getRBack1Delay() const {
        return configu16[backBtnRightKey1Delay_offt];
    }

    int Controller::getRBack2Delay() const {
        return configu16[backBtnRightKey2Delay_offt];
    }

    int Controller::getRBack3Delay() const {
        return configu16[backBtnRightKey3Delay_offt];
    }

    int Controller::getRBack4Delay() const {
        return configu16[backBtnRightKey4Delay_offt];
    }

    std::string Controller::getRumbleMode() const {
        return rumbleModeToString(configBuf[rumbleMode_offt]);
    }

    int Controller::getLAnalogCenter() const {
        return configi8[leftAnalogCenter_offt];
    }

    int Controller::getLAnalogBoundary() const {
        return configi8[leftAnalogBoundary_offt];
    }

    int Controller::getRAnalogCenter() const {
        return configi8[rightAnalogCenter_offt];
    }

    int Controller::getRAnalogBoundary() const {
        return configi8[rightAnalogBoundary_offt];
    }

    std::string Controller::getLedMode() const {
        return ledModeToString(configBuf[ledMode_offt]);
    }

    std::tuple<int, int, int> Controller::getLedColor() const {
        return std::make_tuple(configBuf[ledColorR_offt], configBuf[ledColorG_offt], configBuf[ledColorB_offt]);
    }
}
