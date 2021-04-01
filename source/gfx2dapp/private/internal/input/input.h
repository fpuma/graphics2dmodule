#pragma once

#include <input/iinput.h>
#include <input/inputids.h>

namespace puma::app
{
    class Input : public IInput
    {
    public:

        void init() override;
        void uninit() override;

        void update() override;

        bool getKeyState( InputID _inputId ) override { assert( _inputId < InputID::TotalKeys ); return m_inputState[(int)_inputId] & CurrentStateBit; }
        bool keyPressed( InputID _inputId )  override { assert( _inputId < InputID::TotalKeys ); return m_inputState[(int)_inputId] & PressedStateBit; }
        bool keyReleased( InputID _inputId ) override { assert( _inputId < InputID::TotalKeys ); return m_inputState[(int)_inputId] & ReleasedStateBit; }

        MousePosition getMousePosition() override { return m_mousePosition; }

        void consumeSdlEvents() override { m_peekSdlEvents = false; }
        void peekSdlEvents() override { m_peekSdlEvents = true; }

    private:

        void clearPreviousStates();

        enum StateFlag
        {
            CurrentStateBit  = 0x01,
            PressedStateBit  = 0x02,
            ReleasedStateBit = 0x04,
        };

        using StateMask = u8;

        std::array< StateMask, (int)InputID::TotalKeys> m_inputState = {};

        MousePosition m_mousePosition = {};

        bool m_peekSdlEvents = false;
    };
}