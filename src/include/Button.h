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

/*!
 * @file Button.h
 */
namespace OWC {
    /*!
     * @enum Button
     * @brief enum to refer to a physical button and its mode
     */
    enum struct Button {
        // keyboard&mode
        KBD_A, ///< keyboard mode A button
        KBD_B, ///< keyboard mode B button
        KBD_X, ///< keyboard mode X button
        KBD_Y, ///< keyboard mode Y button
        KBD_DPAD_UP, ///< keyboard mode D-pad up button
        KBD_DPAD_DOWN, ///< keyboard mode D-pad down button
        KBD_DPAD_LEFT, ///< keyboard mode D-pad left button
        KBD_DPAD_RIGHT, ///< keyboard mode D-pad right button
        KBD_LANALOG_UP, ///< keyboard mode left analog up button
        KBD_LANALOG_DOWN, ///< keyboard mode left analog down button
        KBD_LANALOG_LEFT, ///< keyboard mode left analog left button
        KBD_LANALOG_RIGHT, ///< keyboard mode left analog right button
        KBD_START, ///< keyboard mode Start button
        KBD_SELECT, ///< keyboard mode Select button
        KBD_MENU, ///< keyboard mode Menu button
        KBD_L1, ///< keyboard mode L1 button
        KBD_L2, ///< keyboard mode L2 button
        KBD_L3, ///< keyboard mode L3 button
        KBD_R1, ///< keyboard mode R1 button
        KBD_R2, ///< keyboard mode R2 button
        KBD_R3, ///< keyboard mode R3 button

        // xinput
        X_A, ///< xinput mode A button
        X_B, ///< xinput mode B button
        X_X, ///< xinput mode X button
        X_Y, ///< xinput mode Y button
        X_DPAD_UP, ///< xinput mode D-pad up button
        X_DPAD_DOWN, ///< xinput mode D-pad down button
        X_DPAD_LEFT, ///< xinput mode D-pad left button
        X_DPAD_RIGHT, ///< xinput mode D-pad right button
        X_LANALOG_UP, ///< xinput mode left analog up button
        X_LANALOG_DOWN, ///< xinput mode left analog down button
        X_LANALOG_LEFT, ///< xinput mode left analog left button
        X_LANALOG_RIGHT, ///< xinput mode left analog right button
        X_RANALOG_UP, ///< xinput mode right analog up button
        X_RANALOG_DOWN, ///< xinput mode right analog down button
        X_RANALOG_LEFT, ///< xinput mode right analog left button
        X_RANALOG_RIGHT, ///< xinput mode right analog right button
        X_START, ///< xinput mode Start button
        X_SELECT, ///< xinput mode Select button
        X_MENU, ///< xinput mode Menu button
        X_L1, ///< xinput mode L1 button
        X_L2, ///< xinput mode L2 button
        X_L3, ///< xinput mode L3 button
        X_R1, ///< xinput mode R1 button
        X_R2, ///< xinput mode R2 button
        X_R3, ///< xinput mode R3 button
    };
}
