#pragma once

#include <input/iinput.h>
#include <input/inputids.h>

#include <internal/input/devices/mouse.h>

namespace puma::app
{
    class Input : public IInput
    {
    public:

        void init() override;
        void uninit() override;

        void update() override;

        bool getKeyState( InputId _inputId ) override { assert( _inputId != kInvalidInputId ); return m_inputState[(int)_inputId] & CurrentStateBit; }
        bool keyPressed( InputId _inputId )  override { assert( _inputId != kInvalidInputId ); return m_inputState[(int)_inputId] & PressedStateBit; }
        bool keyReleased( InputId _inputId ) override { assert( _inputId != kInvalidInputId ); return m_inputState[(int)_inputId] & ReleasedStateBit; }

        //MousePosition getMousePosition() override { return m_mousePosition; }

        void consumeSdlEvents() override { m_peekSdlEvents = false; }
        void peekSdlEvents() override { m_peekSdlEvents = true; }

    private:

        void clearPreviousStates();
        void updateInputState(InputId _inputId, InputButtonEvent _buttonEvent);

        

        Mouse m_mouseDevice;

        bool m_peekSdlEvents = false;
    };
}