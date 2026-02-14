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

#include <cstdint>

#include "include/export.h"
#include "include/LedMode.h"
#include "include/RumbleMode.h"

namespace OWC {
    [[nodiscard]] std::wstring bufferToString(const uint8_t *buf, int sz);
    [[nodiscard]] std::wstring strTowstr(const char *str);
    [[nodiscard]] bool findHIDKeycode(const std::string &key, uint16_t &outCode);
    [[nodiscard]] bool findXinputKeycode(const std::string &key, uint16_t &outCode);
    [[nodiscard]] int getBytesSum(const uint8_t *buf, int len);

    [[nodiscard]] OWC_EXPORT std::string rumbleModeToString(RumbleMode mode);
    [[nodiscard]] OWC_EXPORT std::string ledModeToString(LedMode mode);
}
