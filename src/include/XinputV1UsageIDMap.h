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

/*!
 * @file XinputV1UsageIDMap.h
 */
namespace OWC {
    /*!
     * @brief map of supported controller keys and their GPD custom keycode
     * @details maps GPD custom HID usage ID -> string key name, V1 devices
     */
    static const std::map<int, std::string> XinputV1UsageIDMap = {
        {0, "UNSET"},
        {0xff01, "DPAD_UP"},
        {0xff02, "DPAD_DOWN"},
        {0xff03, "DPAD_LEFT"},
        {0xff04, "DPAD_RIGHT"},
        {0xff05, "BTN_A"},
        {0xff06, "BTN_B"},
        {0xff07, "BTN_X"},
        {0xff08, "BTN_Y"},
        {0xff09, "LSTICK_UP"},
        {0xff0a, "LSTICK_DOWN"},
        {0xff0b, "LSTICK_LEFT"},
        {0xff0c, "LSTICK_RIGHT"},
        {0xff0d, "L3"},
        {0xff0e, "R3"},
        {0xff0f, "START"},
        {0xff10, "SELECT"},
        {0xff11, "MENU"},
        {0xff12, "L1"},
        {0xff13, "R1"},
        {0xff14, "L2"},
        {0xff15, "R2"},
        {0xff16, "RSTICK_UP"},
        {0xff17, "RSTICK_DOWN"},

        // these 2 are inverted, at least on max2, either a v1 firmware typo or max2 bug
        // don't have a v1 device to test, so suppose we'll see if someone complains on other v1 devs
        {0xff18, "RSTICK_RIGHT"},
        {0xff19, "RSTICK_LEFT"},
    };
}