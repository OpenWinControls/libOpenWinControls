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

#include <functional>
#include <source_location>
#include <cstdint>

#include "../extern/hidapi/hidapi/hidapi.h"
#include "../include/export.h"
#include "../include/Button.h"
#include "../include/LedMode.h"
#include "../include/RumbleMode.h"

namespace OWC {
    /*!
     * @class Controller
     * @brief Controller abstract base class
     */
    class OWC_EXPORT Controller {
    protected:
        std::function<void(const std::wstring &)> logFn;
        hid_device *gamepad = nullptr;
        uint8_t *sendBuf = nullptr;
        uint8_t *respBuf = nullptr;
        uint8_t *configBuf = nullptr;
        int8_t *configI8 = nullptr; // alias
        uint16_t *configU16 = nullptr; // alias
        int features = 0;
        int sendPacketLen;
        int respPacketLen;
        int configBufLen;

        [[nodiscard]] virtual int getVID() const = 0;
        [[nodiscard]] virtual int getPID() const = 0;

        void prepareRespBuffer() const;
        void writeLog(const std::wstring &msg, std::source_location loc = std::source_location::current()) const;
        [[nodiscard]] bool setButtonKey(uint16_t *btn, const std::string &key) const;
        [[nodiscard]] bool setXinputKey(uint16_t *btn, const std::string &key) const;
        void setBackButtonTime(uint16_t *field, int time) const;
        void setAnalogDeadzone(int8_t *field, int value) const;

    public:
        Controller(int controllerFeatures, int sendBufSz, int respBufSz, int configBufSz);
        virtual ~Controller();

        /*!
         * @brief int value of the controller class version
         * @return controller type (1,2, ..)
         */
        [[nodiscard]] virtual int getControllerType() const = 0;

        /*!
         * @brief read the whole configuration
         * @return true on success
         */
        [[nodiscard]] virtual bool readConfig() = 0;

        /*!
         * @brief write the configuration
         * @return true on success
         */
        [[nodiscard]] virtual bool writeConfig() const = 0;

        /*!
         * @brief reset the whole controller configuration memory
         * @details writes a known working configuration buffer
         * @return true on success
         */
        [[nodiscard]] virtual bool resetConfig() const = 0;

        /*!
         * @brief set a new @p key for the button @p btn
         * @param btn the controller button to remap
         * @param key one of @ref HIDUsageIDMap or @ref XinputUsageIDMap values (case insensitive)
         * @return true on success
         */
        [[nodiscard]] virtual bool setButton(Button btn, const std::string &key) const = 0;

        /*!
         * @brief get the current key of button @p btn
         * @param btn the controller button to read
         * @return one of @ref HIDUsageIDMap or @ref XinputUsageIDMap values
         */
        [[nodiscard]] virtual std::string getButton(Button btn) const = 0;

        /*!
         * @brief set a new @p key in slot @p slot for back button @p num
         * @details @p num is the order of appearance in firmware config
         * @sa https://github.com/OpenWinControls/libOpenWinControls/tree/main/docs
         * @param num back button number (1,2, ..)
         * @param slot back button key slot
         * @param key one of @ref HIDUsageIDMap or @ref XinputUsageIDMap values (case insensitive)
         * @return true on success
         */
        [[nodiscard]] virtual bool setBackButton(int num, int slot, const std::string &key) const = 0;

        /*!
         * @brief get the current key in slot @p slot of back button @p num
         * @details @p num is the order of appearance in firmware config
         * @sa https://github.com/OpenWinControls/libOpenWinControls/tree/main/docs
         * @param num back button number (1,2 ..)
         * @param slot back button key slot
         * @return one of @ref HIDUsageIDMap or @ref XinputUsageIDMap values
         */
        [[nodiscard]] virtual std::string getBackButton(int num, int slot) const = 0;

        /*!
         * @brief set start time for key in slot @p slot of back button @p num
         * @details @p num is the order of appearance in firmware config
         * @sa https://github.com/OpenWinControls/libOpenWinControls/tree/main/docs
         * @param num back button number (1,2 ..)
         * @param slot back button key slot
         * @param timeMs start time in milliseconds
         */
        virtual void setBackButtonStartTime(int num, int slot, int timeMs) const = 0;

        /*!
         * @brief get start time for key in slot @p slot of back button @p num
         * @details @p num is the order of appearance in firmware config
         * @sa https://github.com/OpenWinControls/libOpenWinControls/tree/main/docs
         * @param num back button number (1,2 ..)
         * @param slot back button key slot
         * @return start time in milliseconds
         */
        [[nodiscard]] virtual int getBackButtonStartTime(int num, int slot) const = 0;

        /*!
         * @brief set vibration intensity
         * @param mode one of @ref RumbleMode
         */
        virtual void setRumble(RumbleMode mode) const = 0;

        /*!
         * @brief get current vibration intesity
         * @return @ref RumbleMode
         */
        [[nodiscard]] virtual RumbleMode getRumbleMode() const = 0;

        /*!
         * @brief set led mode
         * @param mode one of @ref LedMode
         */
        virtual void setLedMode(LedMode mode) const = 0;

        /*!
         * @brief get current led mode
         * @return @ref LedMode
         */
        [[nodiscard]] virtual LedMode getLedMode() const = 0;

        /*!
         * @brief set a custom color for the leds
         * @details has no effect for modes other than @ref LedMode::Solid and @ref LedMode::Breathe
         * @param r red value of the color
         * @param g green value of the color
         * @param b blue value of the color
         */
        virtual void setLedColor(int r, int g, int b) const = 0;

        /*!
         * @brief get current led custom color
         * @details returned color is valid only when mode is one of @ref LedMode::Solid or @ref LedMode::Breathe
         * @return red,green,blue values of the color as tuple
         */
        [[nodiscard]] virtual std::tuple<int, int, int> getLedColor() const = 0;

        /*!
         * @brief set the analog stick offset from center (deadzone)
         * @param center offset
         * @param left flag indicating to which analog this setting applies to (left or right)
         */
        virtual void setAnalogCenter(int center, bool left) const = 0;

        /*!
         * @brief get the current analog stick offset from center (deadzone)
         * @param left flag indicating to which analog this setting applies to (left or right)
         * @return center offset
         */
        [[nodiscard]] virtual int getAnalogCenter(bool left) const = 0;

        /*!
         * @brief set the analog stick boundary offset (circularity)
         * @param boundary offset
         * @param left flag indicating to which analog this setting applies to (left or right)
         */
        virtual void setAnalogBoundary(int boundary, bool left) const = 0;

        /*!
         * @brief get the current analog stick boundary offset (circularity)
         * @param left flag indicating to which analog this setting applies to (left or right)
         * @return boundary offset
         */
        [[nodiscard]] virtual int getAnalogBoundary(bool left) const = 0;

        /*!
         * @brief Enable log messages
         * @param logCB log callback
         */
        void enableLogging(const std::function<void(const std::wstring &)> &logCB) { logFn = logCB; }

        /*!
         * @brief Initialize the controller
         * @details Try to find a supported GPD controller and connect to it
         * @return true on success
         */
        [[nodiscard]] bool init();

        /*!
         * @brief Check if @p feature is enabled for this controller
         * @param feature one of @ref ControllerFeature
         * @return true if the feature is enabled
         */
        [[nodiscard]] bool hasFeature(int feature) const;
    };
}
