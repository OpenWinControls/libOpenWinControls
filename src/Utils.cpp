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
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <memory>

#include "Utils.h"
#include "include/HIDUsageIDMap.h"
#include "include/XinputUsageIDMap.h"

namespace OWC {
    std::wstring bufferToString(const uint8_t *buf, const int sz) {
        std::wostringstream oss;

        for (int i=0; i<sz; ++i)
            oss << std::hex << std::setfill(L'0') << std::setw(2) << static_cast<int>(buf[i]);

        return oss.str();
    }

    std::wstring strTowstr(const char *str) {
        std::mbstate_t state = std::mbstate_t();
        const std::size_t len = 1 + std::mbsrtowcs(nullptr, &str, 0, &state);
        std::unique_ptr<wchar_t[]> ret = std::make_unique<wchar_t[]>(len);

        std::wmemset(ret.get(), 0, len);
        std::mbsrtowcs(ret.get(), &str, len - 1, &state);

        return std::wstring(ret.get());
    }

    std::string rumbleModeToString(const RumbleMode mode) {
        switch (mode) {
            case RumbleMode::Off:
                return "Off";
            case RumbleMode::Low:
                return "Low";
            case RumbleMode::High:
                return "High";
            default:
                break;
        }

        return "Unknown";
    }

    std::string ledModeToString(const LedMode mode) {
        switch (mode) {
            case LedMode::Off:
                return "Off";
            case LedMode::Solid:
                return "Solid";
            case LedMode::Breathe:
                return "Breathe";
            case LedMode::Rotate:
                return "Rotate";
            default:
                break;
        }

        return "Unknown";
    }

    std::string emulationModeToString(const EmulationMode mode) {
        switch (mode) {
            case EmulationMode::Xinput:
                return "Xinput";
            case EmulationMode::KeyboardMouse:
                return "Keyboard and mouse";
            case EmulationMode::KeyboardSpecial:
                return "Keyboard special mode";
            default:
                break;
        }

        return "Unknown";
    }

    std::string backButtonModeToString(const BackButtonMode mode) {
        switch (mode) {
            case BackButtonMode::Single:
                return "Single button";
            case BackButtonMode::Four:
                return "Four buttons";
            case BackButtonMode::Macro:
                return "Macro";
            default:
                break;
        }

        return "Unknown";
    }

    std::string backButtonMacroTypeToString(const BackButtonMacroType type) {
        switch (type) {
            case BackButtonMacroType::Xinput:
                return "Xinput";
            case BackButtonMacroType::Keyboard:
                return "Keyboard";
            default:
                break;
        }

        return "Unknown";
    }

    [[nodiscard]]
    static bool findKeyCode(const std::string &key, uint16_t &outCode, const bool hid) {
        for (const auto &[code, str]: (hid ? HIDUsageIDMap:XinputUsageIDMap)) {
            if (key != str)
                continue;

            outCode = code;
            return true;
        }

        return false;
    }

    bool findHIDKeycode(const std::string &key, uint16_t &outCode) {
        return findKeyCode(key, outCode, true);
    }

    bool findXinputKeycode(const std::string &key, uint16_t &outCode) {
        return findKeyCode(key, outCode, false);
    }

    int getBytesSum(const uint8_t *buf, const int len) {
        int ret = 0;

        for (int i=0; i<len; ++i)
            ret += buf[i];

        return ret;
    }
}
