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

        bool keyState( MouseKey _key ) const override { return m_mouseDevice.keyState( static_cast<InputId>(_key) ); }
        bool keyState( KeyboardKey _key ) const override { return m_keyboardDevice.keyState( static_cast<InputId>(_key) ); }

        bool keyPressed( MouseKey _key ) const override { return m_mouseDevice.keyPressed( static_cast<InputId>(_key) ); }
        bool keyPressed( KeyboardKey _key ) const override { return m_keyboardDevice.keyPressed( static_cast<InputId>(_key) ); }

        bool keyReleased( MouseKey _key ) const override { return m_mouseDevice.keyReleased( static_cast<InputId>(_key) ); }
        bool keyReleased( KeyboardKey _key ) const override { return m_keyboardDevice.keyReleased( static_cast<InputId>(_key) ); }

        void consumeSdlEvents() override { m_peekSdlEvents = false; }
        void peekSdlEvents() override { m_peekSdlEvents = true; }

    private:

        void clearPreviousStates();        

        Mouse m_mouseDevice;
        Keyboard m_keyboardDevice;

        bool m_peekSdlEvents = false;
    };
}