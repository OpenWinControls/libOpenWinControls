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

        static constexpr int sendPacketLen = 32 + 1;
        static constexpr int respPacketLen = 64 + 1;
        static constexpr int configBufLen = respPacketLen * 2;
        std::pair<int, int> xVersion;
        std::pair<int, int> kVersion;
        uint8_t *sendBuf = nullptr;
        uint8_t *respBuf = nullptr;
        uint8_t *configBuf = nullptr;
        int8_t *configI8 = nullptr; // alias
        uint16_t *configU16 = nullptr; // alias

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
        explicit ControllerV1(int controllerFeatures = 0);
        ~ControllerV1() override;

        [[nodiscard]] int getControllerType() const override { return 1; }
        [[nodiscard]] std::pair<int, int> getXVersion() const { return xVersion; }
        [[nodiscard]] std::pair<int, int> getKVersion() const { return kVersion; }

        [[nodiscard]] bool readConfig() override;
        [[nodiscard]] bool writeConfig() const override;
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
