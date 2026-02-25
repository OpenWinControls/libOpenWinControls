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
 * @file RumbleMode.h
 */
namespace OWC {
    /*!
     * @enum RumbleMode
     * @brief vibration intensity
     */
    enum struct RumbleMode: int {
        Unknown = -1, ///< invalid/unknown mode
        Off = 0, ///< disabled
        Low = 1, ///< low intensity
        High = 2 ///< high intensity
    };
}
