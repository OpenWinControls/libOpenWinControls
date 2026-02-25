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
 * @file EmulationMode.h
 */
namespace OWC {
    /*!
     * @enum EmulationMode
     * @brief controller emulation mode
     */
    enum struct EmulationMode: int {
        Unknown = -1, ///< invalid/unknown mode
        Xinput = 0, ///< xinput mode (xbox360 controller emulation)
        KeyboardMouse = 1, ///< keyboard&mouse mode (keyboard emulation but right stick is mouse)
        KeyboardSpecial = 2 ///< keyboard mode (special mode)
    };
}
