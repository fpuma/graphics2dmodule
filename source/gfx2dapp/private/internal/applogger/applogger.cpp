#include <precompiledapplication.h>
#include <internal/applogger/applogger.h>

namespace puma::app
{
    AppLogger::AppLogger()
    {
        m_appLogCategory = m_logger.registerCategory( "PumaApp" );
    }

    void AppLogger::info( const char* _log )
    {
        m_logger.info( m_appLogCategory, _log );
    }

    void AppLogger::warning( const char* _log )
    {
        m_logger.warning( m_appLogCategory, _log );
    }

    void AppLogger::error( const char* _log )
    {
        m_logger.error( m_appLogCategory, _log );
    }
}