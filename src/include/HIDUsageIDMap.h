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

namespace OWC {
    static const std::map<int, std::string> HIDUsageIDMap = {
        {0x00, "UNSET"},

        {0x04, "A"},
        {0x05, "B"},
        {0x06, "C"},
        {0x07, "D"},
        {0x08, "E"},
        {0x09, "F"},
        {0x0a, "G"},
        {0x0b, "H"},
        {0x0c, "I"},
        {0x0d, "J"},
        {0x0e, "K"},
        {0x0f, "L"},
        {0x10, "M"},
        {0x11, "N"},
        {0x12, "O"},
        {0x13, "P"},
        {0x14, "Q"},
        {0x15, "R"},
        {0x16, "S"},
        {0x17, "T"},
        {0x18, "U"},
        {0x19, "V"},
        {0x1a, "W"},
        {0x1b, "X"},
        {0x1c, "Y"},
        {0x1d, "Z"},

        {0x1e, "1"},
        {0x1f, "2"},
        {0x20, "3"},
        {0x21, "4"},
        {0x22, "5"},
        {0x23, "6"},
        {0x24, "7"},
        {0x25, "8"},
        {0x26, "9"},
        {0x27, "0"},

        {0x28, "ENTER"},
        {0x29, "ESC"},
        {0x2a, "BACKSPACE"},
        {0x2b, "TAB"},
        {0x2c, "SPACE"},
        {0x2d, "MINUS"},
        {0x2e, "EQUAL"},
        {0x2f, "LEFTBRACE"},
        {0x30, "RIGHTBRACE"},
        {0x31, "BACKSLASH"},
        {0x32, "HASHTILDE"},
        {0x33, "SEMICOLON"},
        {0x34, "APOSTROPHE"},
        {0x35, "GRAVE"},
        {0x36, "COMMA"},
        {0x37, "DOT"},
        {0x38, "SLASH"},
        {0x39, "CAPSLOCK"},

        {0x3a, "F1"},
        {0x3b, "F2"},
        {0x3c, "F3"},
        {0x3d, "F4"},
        {0x3e, "F5"},
        {0x3f, "F6"},
        {0x40, "F7"},
        {0x41, "F8"},
        {0x42, "F9"},
        {0x43, "F10"},
        {0x44, "F11"},
        {0x45, "F12"},

        {0x46, "SYSRQ"},
        {0x47, "SCROLLLOCK"},
        {0x48, "PAUSE"},
        {0x49, "INSERT"},
        {0x4a, "HOME"},
        {0x4b, "PAGEUP"},
        {0x4c, "DELETE"},
        {0x4d, "END"},
        {0x4e, "PAGEDOWN"},
        {0x4f, "RIGHT"},
        {0x50, "LEFT"},
        {0x51, "DOWN"},
        {0x52, "UP"},

        {0x53, "NUMLOCK"},
        {0x54, "KPSLASH"},
        {0x55, "KPASTERISK"},
        {0x56, "KPMINUS"},
        {0x57, "KPPLUS"},
        {0x58, "KPENTER"},
        {0x59, "KP1"},
        {0x5a, "KP2"},
        {0x5b, "KP3"},
        {0x5c, "KP4"},
        {0x5d, "KP5"},
        {0x5e, "KP6"},
        {0x5f, "KP7"},
        {0x60, "KP8"},
        {0x61, "KP9"},
        {0x62, "KP0"},
        {0x63, "KPDOT"},

        {0x64, "102ND"},
        {0x65, "COMPOSE"},
        {0x66, "POWER"},
        {0x67, "KPEQUAL"},

        {0x68, "F13"},
        {0x69, "F14"},
        {0x6a, "F15"},
        {0x6b, "F16"},
        {0x6c, "F17"},
        {0x6d, "F18"},
        {0x6e, "F19"},
        {0x6f, "F20"},
        {0x70, "F21"},
        {0x71, "F22"},
        {0x72, "F23"},
        {0x73, "F24"},

        {0x74, "OPEN"},
        {0x75, "HELP"},
        {0x76, "PROPS"},
        {0x77, "FRONT"},
        {0x78, "STOP"},
        {0x79, "AGAIN"},
        {0x7a, "UNDO"},
        {0x7b, "CUT"},
        {0x7c, "COPY"},
        {0x7d, "PASTE"},
        {0x7e, "FIND"},
        {0x7f, "MUTE"},
        {0x80, "VOLUMEUP"},
        {0x81, "VOLUMEDOWN"},

        {0x85, "KPCOMMA"},

        {0x87, "RO"},
        {0x88, "KATAKANAHIRAGANA"},
        {0x89, "YEN"},
        {0x8a, "HENKAN"},
        {0x8b, "MUHENKAN"},
        {0x8c, "KPJPCOMMA"},

        {0x90, "HANGEUL"},
        {0x91, "HANJA"},
        {0x92, "KATAKANA"},
        {0x93, "HIRAGANA"},
        {0x94, "ZENKAKUHANKAKU"},

        {0xb6, "KPLEFTPAREN"},
        {0xb7, "KPRIGHTPAREN"},

        {0xe0, "LEFTCTRL"},
        {0xe1, "LEFTSHIFT"},
        {0xe2, "LEFTALT"},
        {0xe3, "LEFTMETA"},

        {0xe4, "RIGHTCTRL"},
        {0xe5, "RIGHTSHIFT"},
        {0xe6, "RIGHTALT"},
        {0xe7, "RIGHTMETA"},

        {0xe8, "MOUSE_WHEELUP"},
        {0xe9, "MOUSE_WHEELDOWN"},
        {0xea, "MOUSE_LEFT"},
        {0xeb, "MOUSE_RIGHT"},
        {0xec, "MOUSE_MIDDLE"},
        {0xed, "MOUSE_FAST"},

        /* can only be set for gamepad mode
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
        */
    };
}
