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
