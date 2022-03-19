#pragma once

#include <internal/applogger/applogger.h>
#include <internal/input/sdlinputmapping.h>

namespace puma::nina
{
    using StateMask = u8;

    using MouseKeyStates = std::array<StateMask, static_cast<InputId>(MouseButton::TotalButtons)>;
    using KeyboardKeyStates = std::array<StateMask, static_cast<InputId>(KeyboardKey::TotalKeys)>;
    using ControllerKeyStates = std::array<StateMask, static_cast<InputId>(ControllerButton::TotalButtons)>;

    enum class InputButtonEvent
    {
        Up,
        Down,
    };

    enum StateFlag
    {
        CurrentStateBit = 0x01,
        PressedStateBit = 0x02,
        ReleasedStateBit = 0x04,
    };

    InputId resolveInputID( const SDLInputMapping& _sdlInputMapping, s32 _sdlInputNumber );

    template<class DeviceKeysType>
    class DeviceKeyStates
    {
    public:
        
        virtual ~DeviceKeyStates() {}

        void clearStates()
        {
            for ( StateMask& stateMask : m_keyStates )
            {
                stateMask &= ~ReleasedStateBit;
                stateMask &= ~PressedStateBit;
            }
            internalClearStates();
        }

        void updateKeyStates( InputId _inputId, InputButtonEvent _buttonEvent )
        {
            switch ( _buttonEvent )
            {
            case InputButtonEvent::Up:
            {
                if ( _inputId != kInvalidInputId )
                {
                    if ( m_keyStates[(int)_inputId] & CurrentStateBit )
                    {
                        m_keyStates[(int)_inputId] |= ReleasedStateBit;
                    }
                    else
                    {
                        m_keyStates[(int)_inputId] &= ~ReleasedStateBit;
                    }

                    m_keyStates[(int)_inputId] &= ~CurrentStateBit;
                }
                break;
            }
            case InputButtonEvent::Down:
            {
                if ( _inputId != kInvalidInputId )
                {
                    if ( m_keyStates[(int)_inputId] & CurrentStateBit )
                    {
                        m_keyStates[(int)_inputId] &= ~PressedStateBit;
                    }
                    else
                    {
                        m_keyStates[(int)_inputId] |= PressedStateBit;
                    }

                    m_keyStates[(int)_inputId] |= CurrentStateBit;
                }
                break;
            }
            default:
                assert( false ); //InputButtonEvent not yet supported
                break;
            }
        }

    protected:

        virtual void internalClearStates() = 0;

        bool inputState( InputId _inputId ) const
        { 
            assert( _inputId != kInvalidInputId ); 
            assert( _inputId < m_keyStates.size() );
            return m_keyStates[(int)_inputId] & CurrentStateBit; 
        }
        
        bool inputPressed( InputId _inputId ) const
        { 
            assert( _inputId != kInvalidInputId ); 
            assert( _inputId < m_keyStates.size() );
            return m_keyStates[(int)_inputId] & PressedStateBit; 
        }
        
        bool inputReleased( InputId _inputId ) const
        { 
            assert( _inputId != kInvalidInputId ); 
            assert( _inputId < m_keyStates.size() );
            return m_keyStates[(int)_inputId] & ReleasedStateBit; 
        }

    private:

        DeviceKeysType m_keyStates = {};
    };
}