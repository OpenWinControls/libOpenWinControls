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
#include "../include/BackButtonMode.h"
#include "../include/EmulationMode.h"

namespace OWC {
    class OWC_EXPORT ControllerV2 final: public Controller {
    private:
        enum struct CMD: int {
            Init1 = 0x21,
            Init2 = 0x2b,
            Read = 0x44,
            Write = 0x43,
            Commit1 = 0x27,
            Commit2 = 0x22
        };

        static constexpr int sendPacketLen = 64 + 1;
        static constexpr int respPacketLen = 64 + 1;
        static constexpr int configBufLen = 1024;
        uint8_t writeReqHeader[12] = {0};
        uint8_t *sendBuf = nullptr;
        uint8_t *respBuf = nullptr;
        uint8_t *configBuf = nullptr;
        int8_t *configI8 = nullptr; // alias
        uint16_t *configU16 = nullptr; // alias
        std::pair<int, int> version;

        [[nodiscard]] bool readStatusInterrupt();
        [[nodiscard]] bool initReadCommunication() const;
        [[nodiscard]] bool initWriteCommunication() const;
        [[nodiscard]] bool sendReadRequest(int *respBytesCount = nullptr) const;
        [[nodiscard]] bool sendWriteRequest() const;
        void prepareSendBuffer(CMD cmd) const;
        void prepareRespBuffer() const;
        [[nodiscard]] bool isValidRespPacket() const;
        [[nodiscard]] int getBackButtonModeIdx(int num) const;
        [[nodiscard]] int getBackButtonKeyPos(int num, int slot) const;

    protected:
        [[nodiscard]] int getVID() const override { return 0x2f24; }
        [[nodiscard]] int getPID() const override { return 0x137; }

    public:
        explicit ControllerV2(int controllerFeatures = 0);
        ~ControllerV2() override;

        [[nodiscard]] int getControllerType() const override { return 2; }
        [[nodiscard]] std::pair<int, int> getVersion() const { return version; }

        [[nodiscard]] bool readConfig() override;
        [[nodiscard]] bool writeConfig() const override;
        [[nodiscard]] EmulationMode getEmulationMode() const;
        [[nodiscard]] bool setButton(Button btn, const std::string &key) const override;
        [[nodiscard]] std::string getButton(Button btn) const override;
        //void setBackButtonMode(int num, BackButtonMode mode) const;
        [[nodiscard]] BackButtonMode getBackButtonMode(int num) const;
        //void setBackButtonMacroType(int num, BackButtonMacroType type) const;
        //[[nodiscard]] BackButtonMacroType getBackButtonMacroType(int num) const;
        //void setBackButtonActiveSlots(int num, uint8_t count) const;
        [[nodiscard]] int getBackButtonActiveSlots(int num) const;
        [[nodiscard]] bool setBackButton(int num, int slot, const std::string &key) const override;
        [[nodiscard]] std::string getBackButton(int num, int slot) const override;
        void setBackButtonStartTime(int num, int slot, int timeMs) const override;
        [[nodiscard]] int getBackButtonStartTime(int num, int slot) const override;
        void setBackButtonHoldTime(int num, int slot, int timeMs) const;
        [[nodiscard]] int getBackButtonHoldTime(int num, int slot) const;
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
