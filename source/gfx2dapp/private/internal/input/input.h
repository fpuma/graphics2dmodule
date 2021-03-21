#pragma once

#include <input/iinput.h>
#include <input/inputids.h>

namespace puma::input
{
    class Input : public IInput
    {
    public:

        Input();
        ~Input();

        void init() override;
        void uninit() override;

        void update() override;

        bool getKeyState( InputID _inputId ) { assert( _inputId < InputID::TotalKeys ); return m_inputState[(int)_inputId]; }

        MousePosition getMousePosition() override { return m_mousePosition; }

        void consumeSdlEvents() override { m_peekSdlEvents = false; }
        void peekSdlEvents() override { m_peekSdlEvents = true; }

    private:

        bool m_inputState[(int)InputID::TotalKeys] = {};
        MousePosition m_mousePosition = {};

        bool m_peekSdlEvents = false;
    };
}