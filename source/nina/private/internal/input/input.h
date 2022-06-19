#pragma once

#include <input/iinput.h>
#include <input/inputids.h>
#include <input/iinputlistener.h>

#include <internal/input/devices/mouse.h>
#include <internal/input/devices/keyboard.h>
#include <internal/input/devices/controller.h>

#include <utils/containers/containedvector.h>

namespace puma::nina
{
    class Input : public IInput
    {
    public:

        void init() override;
        void uninit() override;

        void update() override;

        const IMouse& getMouse() const override { return m_mouseDevice; }
        const IKeyboard& getKeyboard() const override { return m_keyboardDevice; }
        const IController& getController( ControllerId _id ) const override { assert( _id < m_controllerDevices.size() ); return m_controllerDevices[_id]; }
        u32 getControllerCount() const override { return (u32)m_controllerDevices.size(); }

        void setInputListener( std::unique_ptr<IInputListener>&& _inputListener ) { m_inputListener.release(); m_inputListener = std::move( _inputListener ); }
        void clearInputListener() { m_inputListener.release(); }

        void consumeSdlEvents() override { m_peekSdlEvents = false; }
        void peekSdlEvents() override { m_peekSdlEvents = true; }

    private:

        void clearPreviousStates();    
        void updateKeyboardKey( s32 _sdlInputId, InputButtonEvent _inputEvent );
        void updateMouseButton( s32 _sdlInputId, InputButtonEvent _inputEvent );
        void updateControllerButton( Controller& controller, s32 _sdlInputId, InputButtonEvent _inputEvent );
        void updateDPad( s32 _id, u32 input);
        Controller& handleControllerBySdlId( s32 _id );

        float m_joystickDeadZone = 0.2f;

        Mouse m_mouseDevice;
        Keyboard m_keyboardDevice;
        ContainedVector<Controller, 16> m_controllerDevices;

        std::unique_ptr<IInputListener> m_inputListener = nullptr;

        bool m_peekSdlEvents = false;
    };
}