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

#include "Controller.h"

namespace OWC {
    /*!
     * @class ControllerV1
     * @brief interact with controller V1 devices
     */
    class OWC_EXPORT ControllerV1 final: public Controller {
    private:
        enum struct Mode: int {
            Read = 1,
            Write = 2
        };

        enum struct CMD: int {
            Init = 0,
            ReadWrite = 1,
            Checksum = 2,
            Commit = 3
        };

        static constexpr uint8_t resetBuf[] = {0x4b, 0x00, 0x4e, 0x00, 0x4a, 0x00, 0x4d, 0x00, 0x2c, 0x00, 0x06, 0x00, 0x15, 0x00, 0x1e, 0x00, 0x1a, 0x00, 0x16, 0x00, 0x04, 0x00, 0x07, 0x00, 0xe1, 0x00, 0x08, 0x00, 0x09, 0x00, 0x2b, 0x00, 0x29, 0x00, 0xeb, 0x00, 0xea, 0x00, 0x14, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x21, 0xff, 0x00, 0x00, 0xf7, 0xff, 0xf7, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2c, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2c, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        std::pair<int, int> xVersion;
        std::pair<int, int> kVersion;

        [[nodiscard]] bool initCommunication(Mode mode) const;
        [[nodiscard]] bool sendReadRequest() const;
        [[nodiscard]] bool sendWriteRequest() const;
        void prepareSendPacket(Mode mode, CMD cmd, uint8_t page = 0) const;
        void prepareRespBuffer() const;
        [[nodiscard]] bool isConfigValid(int configChecksum, Mode mode) const;
        void parseVersion();

    protected:
        [[nodiscard]] int getVID() const override { return 0x2f24; }
        [[nodiscard]] int getPID() const override { return 0x135; }

    public:
        /*!
         * @brief create a new @ref ControllerV1 controller
         * @param controllerFeatures @ref ControllerFeature flag
         */
        explicit ControllerV1(const int controllerFeatures = 0): Controller(controllerFeatures, 32, 64, 64 * 2) {}
        ~ControllerV1() override = default;

        [[nodiscard]] int getControllerType() const override { return 1; }

        /*!
         * @brief get the firmware xinput mode version
         * @return major and minor version as a pair
         */
        [[nodiscard]] std::pair<int, int> getXVersion() const { return xVersion; }

        /*!
         * @brief get the firmware keyboard mode version
         * @return major and minor version as a pair
         */
        [[nodiscard]] std::pair<int, int> getKVersion() const { return kVersion; }

        [[nodiscard]] bool readConfig() override;
        [[nodiscard]] bool writeConfig() const override;
        [[nodiscard]] bool resetConfig() const override;
        [[nodiscard]] bool setButton(Button btn, const std::string &key) const override;
        [[nodiscard]] std::string getButton(Button btn) const override;
        [[nodiscard]] bool setBackButton(int num, int slot, const std::string &key) const override;
        [[nodiscard]] std::string getBackButton(int num, int slot) const override;
        void setBackButtonStartTime(int num, int slot, int timeMs) const override;
        [[nodiscard]] int getBackButtonStartTime(int num, int slot) const override;
        void setRumble(RumbleMode mode) const override;
        [[nodiscard]] RumbleMode getRumbleMode() const override;
        void setLedMode(LedMode mode) const override;
        [[nodiscard]] LedMode getLedMode() const override;
        void setLedColor(int r, int g, int b) const override;
        [[nodiscard]] std::tuple<int, int, int> getLedColor() const override;
        void setAnalogCenter(int center, bool left) const override;
        [[nodiscard]] int getAnalogCenter(bool left) const override;
        void setAnalogBoundary(int boundary, bool left) const override;
        [[nodiscard]] int getAnalogBoundary(bool left) const override;
    };
}
