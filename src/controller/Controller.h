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
#pragma once

#include <functional>
#include <source_location>
#include <cstdint>

#include "../extern/hidapi/hidapi/hidapi.h"
#include "../include/export.h"

namespace OWC {
    class OWC_EXPORT Controller {
    protected:
        int dpadUp_offt;
        int dpadDown_offt;
        int dpadLeft_offt;
        int dpadRight_offt;
        int a_offt;
        int b_offt;
        int x_offt;
        int y_offt;
        int leftAnalogUp_offt;
        int leftAnalogDown_offt;
        int leftAnalogLeft_offt;
        int leftAnalogRight_offt;
        int start_offt;
        int select_offt;
        int menu_offt;
        int l1_offt;
        int l2_offt;
        int l3_offt;
        int r1_offt;
        int r2_offt;
        int r3_offt;
        int backBtnLeftKey1_offt;
        int backBtnLeftKey1Delay_offt;
        int backBtnLeftKey2_offt;
        int backBtnLeftKey2Delay_offt;
        int backBtnLeftKey3_offt;
        int backBtnLeftKey3Delay_offt;
        int backBtnLeftKey4_offt;
        int backBtnLeftKey4Delay_offt;
        int backBtnRightKey1_offt;
        int backBtnRightKey1Delay_offt;
        int backBtnRightKey2_offt;
        int backBtnRightKey2Delay_offt;
        int backBtnRightKey3_offt;
        int backBtnRightKey3Delay_offt;
        int backBtnRightKey4_offt;
        int backBtnRightKey4Delay_offt;
        int rumbleMode_offt;
        int ledMode_offt;
        int ledColorR_offt;
        int ledColorG_offt;
        int ledColorB_offt;
        int leftAnalogCenter_offt;
        int leftAnalogBoundary_offt;
        int rightAnalogCenter_offt;
        int rightAnalogBoundary_offt;
        std::function<void(const std::wstring &)> logFn;
        int features = 0;
        hid_device *gamepad = nullptr;
        uint8_t *configBuf = nullptr;
        int8_t *configi8 = nullptr; // alias to get i8 data
        uint16_t *configu16 = nullptr; // alias to get u16 data

        [[nodiscard]] virtual int getVID() const = 0;
        [[nodiscard]] virtual int getPID() const = 0;

        void logSendPacketBytes(const uint8_t *buf, int sz, std::source_location loc = std::source_location::current()) const;
        void logRespPacketBytes(const uint8_t *buf, int sz, std::source_location loc = std::source_location::current()) const;
        [[nodiscard]] bool setButtonKey(int offt, const std::string &key) const;
        void setBackButtonDelay(int offt, int delay) const;
        void setAnalogDeadzone(int offt, int value) const;

    public:
        virtual ~Controller();

        [[nodiscard]] virtual int getControllerType() const = 0;
        [[nodiscard]] virtual bool readConfig() = 0;
        [[nodiscard]] virtual bool writeConfig() const = 0;

        void enableLogging(const std::function<void(const std::wstring &)> &logCB) { logFn = logCB; }

        [[nodiscard]] bool init();
        [[nodiscard]] bool hasFeature(int feature) const;
        [[nodiscard]] bool setDpadUp(const std::string &key) const;
        [[nodiscard]] bool setDpadDown(const std::string &key) const;
        [[nodiscard]] bool setDpadLeft(const std::string &key) const;
        [[nodiscard]] bool setDpadRight(const std::string &key) const;
        [[nodiscard]] bool setA(const std::string &key) const;
        [[nodiscard]] bool setB(const std::string &key) const;
        [[nodiscard]] bool setX(const std::string &key) const;
        [[nodiscard]] bool setY(const std::string &key) const;
        [[nodiscard]] bool setL1(const std::string &key) const;
        [[nodiscard]] bool setL2(const std::string &key) const;
        [[nodiscard]] bool setL3(const std::string &key) const;
        [[nodiscard]] bool setR1(const std::string &key) const;
        [[nodiscard]] bool setR2(const std::string &key) const;
        [[nodiscard]] bool setR3(const std::string &key) const;
        [[nodiscard]] bool setStart(const std::string &key) const;
        [[nodiscard]] bool setSelect(const std::string &key) const;
        [[nodiscard]] bool setMenu(const std::string &key) const;
        [[nodiscard]] bool setLAnalogUp(const std::string &key) const;
        [[nodiscard]] bool setLAnalogDown(const std::string &key) const;
        [[nodiscard]] bool setLAnalogLeft(const std::string &key) const;
        [[nodiscard]] bool setLAnalogRight(const std::string &key) const;
        [[nodiscard]] bool setLBack1(const std::string &key) const;
        [[nodiscard]] bool setLBack2(const std::string &key) const;
        [[nodiscard]] bool setLBack3(const std::string &key) const;
        [[nodiscard]] bool setLBack4(const std::string &key) const;
        [[nodiscard]] bool setRBack1(const std::string &key) const;
        [[nodiscard]] bool setRBack2(const std::string &key) const;
        [[nodiscard]] bool setRBack3(const std::string &key) const;
        [[nodiscard]] bool setRBack4(const std::string &key) const;
        void setLBack1Delay(int delay) const;
        void setLBack2Delay(int delay) const;
        void setLBack3Delay(int delay) const;
        void setLBack4Delay(int delay) const;
        void setRBack1Delay(int delay) const;
        void setRBack2Delay(int delay) const;
        void setRBack3Delay(int delay) const;
        void setRBack4Delay(int delay) const;
        void setRumble(const std::string &mode) const;
        void setLAnalogCenter(int center) const;
        void setLAnalogBoundary(int boundary) const;
        void setRAnalogCenter(int center) const;
        void setRAnalogBoundary(int boundary) const;
        void setLedMode(const std::string &mode) const;
        void setLedColor(int r, int g, int b) const;
        [[nodiscard]] std::string getDpadUp() const;
        [[nodiscard]] std::string getDpadDown() const;
        [[nodiscard]] std::string getDpadLeft() const;
        [[nodiscard]] std::string getDpadRight() const;
        [[nodiscard]] std::string getA() const;
        [[nodiscard]] std::string getB() const;
        [[nodiscard]] std::string getX() const;
        [[nodiscard]] std::string getY() const;
        [[nodiscard]] std::string getL1() const;
        [[nodiscard]] std::string getL2() const;
        [[nodiscard]] std::string getL3() const;
        [[nodiscard]] std::string getR1() const;
        [[nodiscard]] std::string getR2() const;
        [[nodiscard]] std::string getR3() const;
        [[nodiscard]] std::string getStart() const;
        [[nodiscard]] std::string getSelect() const;
        [[nodiscard]] std::string getMenu() const;
        [[nodiscard]] std::string getLAnalogUp() const;
        [[nodiscard]] std::string getLAnalogDown() const;
        [[nodiscard]] std::string getLAnalogLeft() const;
        [[nodiscard]] std::string getLAnalogRight() const;
        [[nodiscard]] std::string getLBack1() const;
        [[nodiscard]] std::string getLBack2() const;
        [[nodiscard]] std::string getLBack3() const;
        [[nodiscard]] std::string getLBack4() const;
        [[nodiscard]] std::string getRBack1() const;
        [[nodiscard]] std::string getRBack2() const;
        [[nodiscard]] std::string getRBack3() const;
        [[nodiscard]] std::string getRBack4() const;
        [[nodiscard]] int getLBack1Delay() const;
        [[nodiscard]] int getLBack2Delay() const;
        [[nodiscard]] int getLBack3Delay() const;
        [[nodiscard]] int getLBack4Delay() const;
        [[nodiscard]] int getRBack1Delay() const;
        [[nodiscard]] int getRBack2Delay() const;
        [[nodiscard]] int getRBack3Delay() const;
        [[nodiscard]] int getRBack4Delay() const;
        [[nodiscard]] std::string getRumbleMode() const;
        [[nodiscard]] int getLAnalogCenter() const;
        [[nodiscard]] int getLAnalogBoundary() const;
        [[nodiscard]] int getRAnalogCenter() const;
        [[nodiscard]] int getRAnalogBoundary() const;
        [[nodiscard]] std::string getLedMode() const;
        [[nodiscard]] std::tuple<int, int, int> getLedColor() const;
    };
}
