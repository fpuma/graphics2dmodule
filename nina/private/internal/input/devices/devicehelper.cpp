#include <precompiledapplication.h>
#include "devicehelper.h"

namespace puma::nina
{
    InputId resolveInputID( const SDLInputMapping& _sdlInputMapping, s32 _sdlInputNumber )
    {
        auto itInputId = _sdlInputMapping.find( _sdlInputNumber );
        InputId result = kInvalidInputId;
        if ( _sdlInputMapping.end() != itInputId )
        {
            result = itInputId->second;
        }
        else
        {
            gAppLogger->error( formatString( "Error: Key not recognized! %d", _sdlInputNumber ).c_str() );
        }
        return result;
    }
}