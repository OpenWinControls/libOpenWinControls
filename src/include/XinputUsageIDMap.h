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

#include <map>
#include <string>

namespace OWC {
    // custom GPD codes
    static const std::map<int, std::string> XinputUsageIDMap = {
        {0x8000, "DPAD_UP"},
        {0x8001, "DPAD_DOWN"},
        {0x8002, "DPAD_LEFT"},
        {0x8003, "DPAD_RIGHT"},
        {0x8004, "START"},
        {0x8005, "SELECT"},
        {0x8006, "MENU"},
        {0x8007, "BTN_A"},
        {0x8008, "BTN_B"},
        {0x8009, "BTN_X"},
        {0x800a, "BTN_Y"},
        {0x800b, "L1"},
        {0x800c, "R1"},
        {0x800d, "L2"},
        {0x800e, "R2"},
        {0x800f, "L3"},
        {0x8010, "R3"},
        {0x8011, "LSTICK_UP"},
        {0x8012, "LSTICK_DOWN"},
        {0x8013, "LSTICK_LEFT"},
        {0x8014, "LSTICK_RIGHT"},
        {0x8015, "RSTICK_UP"},
        {0x8016, "RSTICK_DOWN"},
        {0x8017, "RSTICK_LEFT"},
        {0x8018, "RSTICK_RIGHT"}
    };
}
