#pragma once

#include <input/iinput.h>
#include <input/inputids.h>

#include <internal/input/devices/mouse.h>
#include <internal/input/devices/keyboard.h>

namespace puma::app
{
    class Input : public IInput
    {
    public:

        void init() override;
        void uninit() override;

        void update() override;

        const IMouse& getMouse() const { return m_mouseDevice; }
        const IKeyboard& getKeyboard() const { return m_keyboardDevice; }

        void consumeSdlEvents() override { m_peekSdlEvents = false; }
        void peekSdlEvents() override { m_peekSdlEvents = true; }

    private:

        void clearPreviousStates();        

        Mouse m_mouseDevice;
        Keyboard m_keyboardDevice;

        bool m_peekSdlEvents = false;
    };
}