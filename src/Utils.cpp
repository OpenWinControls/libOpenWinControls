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

#include "Utils.h"
#include "include/HIDUsageIDMap.h"

namespace OWC {
    std::string bufferToString(const uint8_t *buf, const int sz) {
        std::ostringstream oss;

        for (int i=0; i<sz; ++i)
            oss << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(buf[i]);

        return oss.str();
    }

    std::string wstrToString(const wchar_t *wstr) {
        std::string ret;

        ret.resize(std::wcslen(wstr) + 1);
        std::wcstombs(ret.data(), wstr, ret.length() - 1);
        return ret;
    }

    uint16_t rumbleStrToRumbleMode(std::string mode) {
        std::transform(mode.begin(), mode.end(), mode.begin(), ::tolower);

        if (mode == "low")
            return 1;
        else if (mode == "high")
            return 2;

        return 0;
    }

    std::string rumbleModeToString(const uint16_t mode) {
        return mode == 0 ? "off" : (mode == 1 ? "low":"high");
    }

    uint8_t ledModeStrToLedMode(std::string mode) {
        std::transform(mode.begin(), mode.end(), mode.begin(), ::tolower);

        if (mode == "solid")
            return 1;
        else if (mode == "breathe")
            return 0x11;
        else if (mode == "rotate")
            return 0x21;

        return 0;
    }

    std::string ledModeToString(const uint8_t mode) {
        switch (mode) {
            case 0:
                return "off";
            case 0x1:
                return "solid";
            case 0x11:
                return "breathe";
            case 0x21:
                return "rotate";
            default:
                break;
        }

        return "unknown";
    }

    bool findHIDKeycode(const std::string &key, uint16_t &outCode) {
        for (const auto &[code, str]: HIDUsageIDMap) {
            if (key != str)
                continue;

            outCode = code;
            return true;
        }

        return false;
    }
}
