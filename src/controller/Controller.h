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
#include "../include/Button.h"
#include "../include/LedMode.h"
#include "../include/RumbleMode.h"

namespace OWC {
    class OWC_EXPORT Controller {
    protected:
        std::function<void(const std::wstring &)> logFn;
        hid_device *gamepad = nullptr;
        int features = 0;

        [[nodiscard]] virtual int getVID() const = 0;
        [[nodiscard]] virtual int getPID() const = 0;

        void writeLog(const std::wstring &msg, std::source_location loc = std::source_location::current()) const;
        [[nodiscard]] bool setButtonKey(uint16_t *btn, const std::string &key) const;
        [[nodiscard]] bool setXinputKey(uint16_t *btn, const std::string &key) const;
        void setBackButtonTime(uint16_t *field, int time) const;
        void setAnalogDeadzone(int8_t *field, int value) const;

    public:
        virtual ~Controller();

        [[nodiscard]] virtual int getControllerType() const = 0;
        [[nodiscard]] virtual bool readConfig() = 0;
        [[nodiscard]] virtual bool writeConfig() const = 0;
        [[nodiscard]] virtual bool setButton(Button btn, const std::string &key) const = 0;
        [[nodiscard]] virtual std::string getButton(Button btn) const = 0;
        [[nodiscard]] virtual bool setBackButton(int num, int slot, const std::string &key) const = 0;
        [[nodiscard]] virtual std::string getBackButton(int num, int slot) const = 0;
        virtual void setBackButtonStartTime(int num, int slot, int timeMs) const = 0;
        [[nodiscard]] virtual int getBackButtonStartTime(int num, int slot) const = 0;
        virtual void setRumble(RumbleMode mode) const = 0;
        [[nodiscard]] virtual RumbleMode getRumbleMode() const = 0;
        virtual void setLedMode(LedMode mode) const = 0;
        [[nodiscard]] virtual LedMode getLedMode() const = 0;
        virtual void setLedColor(int r, int g, int b) const = 0;
        [[nodiscard]] virtual std::tuple<int, int, int> getLedColor() const = 0;
        virtual void setAnalogCenter(int center, bool left) const = 0;
        [[nodiscard]] virtual int getAnalogCenter(bool left) const = 0;
        virtual void setAnalogBoundary(int boundary, bool left) const = 0;
        [[nodiscard]] virtual int getAnalogBoundary(bool left) const = 0;

        void enableLogging(const std::function<void(const std::wstring &)> &logCB) { logFn = logCB; }

        [[nodiscard]] bool init();
        [[nodiscard]] bool hasFeature(int feature) const;
    };
}
