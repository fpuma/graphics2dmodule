#pragma once

namespace puma::app
{
    using StateMask = u8;

    using MouseKeyStates = std::array<StateMask, static_cast<InputId>(MouseKey::TotalKeys)>;
    using KeyboardKeyStates = std::array<StateMask, static_cast<InputId>(KeyboardKey::TotalKeys)>;

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

    template<class T>
    void updateKeyStates( T& _states, InputId _inputId, InputButtonEvent _buttonEvent );


}