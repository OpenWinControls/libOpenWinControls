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
 * @file LedMode.h
 */
namespace OWC {
    /*!
     * @enum LedMode
     * @brief led mode
     */
    enum struct LedMode: int {
        Unknown = -1, ///< invalid/unknown mode
        Off = 0, ///< disabled
        Solid = 1, ///< fixed custom color, no effects
        Breathe = 2, ///< fixed custom color, breathe effect
        Rotate = 3 ///< automatic, rotate all supported colors
    };
}
