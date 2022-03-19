#pragma once

#include <logger/logger.h>

namespace puma::nina
{
    class AppLogger
    {
    public:

        AppLogger();

        void info( const char* _log );
        void warning( const char* _log );
        void error( const char* _log );

        Logger* getLogger() { return &m_logger; }

    private:
        Logger m_logger;
        LogCategory m_appLogCategory;
    };
}

#include <utils/defaultinstance.h>

namespace puma::nina
{
    class Application;
}

#define gAppLogger puma::DefaultInstance<puma::nina::AppLogger, puma::nina::Application>::getInstance()