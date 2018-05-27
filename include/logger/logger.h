#pragma once

#include <ostream>
#include <iostream>

/*

Example useage:

    #include "logger/logger.h"
    using namespace logging;

    void something(int a) {
        DebugLogger(std::cout, "a has a value of", a);

        if(a != 0)
            InfoLogger("a is not 0");

        if(a > 25)
            WarningLogger("Oh goodness a is greater than 25!")

        if(a > 50)
            ErrorLogger(std::cerr, "a cannot be greater than 50!")

        if(a >= 100) {
            CriticalLogger(std::cerr, "a is greater or equal to 100, shutting down!");
            exit(-1);
        }
    }

When something is called with a value of 100 (so it hits all loggers).

When compiled with no specific flags you can expect to see:
[Error] a cannot be greater than 50!
[Critical] a is greater or equal to 100, shutting down!

When compiled with NO_LOGGING being defined, nothing will print and
the program will simply exit (this overrides all other flags).

When compiled with DEBUG or LOG_EVERYTHING
[Debug] a has a value of 100
[Info] a is not 0
[Warning] Oh goodness a is greather than 25!
[Error] a cannot be greater than 50!
[Critical] a is greater or equal to 100, shutting down!

You can turn off certain loggers aswell, i.e compiling with
LOG_EVERYTHING and NO_INFO_LOGGING we get:
[Debug] a has a value of 100
[Warning] Oh goodness a is greather than 25!
[Error] a cannot be greater than 50!
[Critical] a is greater or equal to 100, shutting down!

This is of course intended so that if a logger isn't active, it isn't
simply skipped at run time, but is ommited at compile time, so hopefully
there shouldn't be any cost adding it to code if you aren't using it.

You can specify an ostream as the first argument, otherwise it
falls back to using std::cerr.

The loggers can handle mulitple arguments and attempts to pass them
directly to the ostream it's trying to print to.

*/

// Turn off all loggers individually if no logging
// is to occur (this overrides whether or not loggers
// were previously turned on.
#ifdef NO_LOGGING
    #ifndef NO_DEBUG_LOGGING
        #define NO_DEBUG_LOGGING
    #endif
    #ifndef NO_INFO_LOGGING
        #define NO_INFO_LOGGING
    #endif
    #ifndef NO_WARNING_LOGGING
        #define NO_WARNING_LOGGING
    #endif
    #ifndef NO_ERROR_LOGGING
        #define NO_ERROR_LOGGING
    #endif
    #ifndef NO_CRITICAL_LOGGING
        #define NO_CRITICAL_LOGGING
    #endif
#endif


#if (defined(DEBUG) || defined(LOG_EVERYTHING)) && !defined(USE_DEBUG_LOGGER)
    #define USE_DEBUG_LOGGER
#elif !defined(USE_ERROR_LOGGER)
    #define USE_ERROR_LOGGER
#endif


#if defined(USE_DEBUG_LOGGER) && !defined(USE_INFO_LOGGER)
    #define USE_INFO_LOGGER
#endif

#if defined(USE_INFO_LOGGER) && !defined(USE_WARNING_LOGGER)
    #define USE_WARNING_LOGGER
#endif

#if defined(USE_WARNING_LOGGER) && !defined(USE_ERROR_LOGGER)
    #define USE_ERROR_LOGGER
#endif

#if defined(USE_ERROR_LOGGER) && !defined(USE_CRITICAL_LOGGER)
    #define USE_CRITICAL_LOGGER
#endif


namespace logging {

    enum LogType {
        Debug,
        Info,
        Warning,
        Error,
        Critical
    };


    template <LogType>
    struct Logger {
        
        template <typename...>
        const static void log(std::ostream& out, ...){}

        template <typename...>
        const static void log(...){}

    };


    #if defined(USE_DEBUG_LOGGER) && !defined(NO_DEBUG_LOGGING)
    template <>
    struct Logger <LogType::Debug> {

        template <typename... Args>
        const static void log(Args... args) {
            Logger<LogType::Debug>::log(std::cerr, args...);
        }

        template <typename... Args>
        const static void log(std::ostream& out, Args... args) {
            out << "[Debug]";
            // http://en.cppreference.com/w/cpp/language/parameter_pack
            // under: Brace-enclosed initializers
            using dummy = int[];
            dummy { (out << ' ' << args, 0)... };
            out << '\n';
        }
    };
    #endif


    #if defined(USE_INFO_LOGGER) && !defined(NO_INFO_LOGGING)
    template <>
    struct Logger <LogType::Info> {

        template <typename... Args>
        const static void log(Args... args) {
            Logger<LogType::Info>::log(std::cerr, args...);
        }

        template <typename... Args>
        const static void log(std::ostream& out, Args... args) {
            out << "[Info]";
            using dummy = int[];
            dummy { (out << ' ' << args, 0)... };
            out << '\n';
        }
    };
    #endif


    #if defined(USE_WARNING_LOGGER) && !defined(NO_ERROR_LOGGING)
    template <>
    struct Logger <LogType::Warning> {

        template <typename... Args>
        const static void log(Args... args) {
            Logger<LogType::Warning>::log(std::cerr, args...);
        }

        template <typename... Args>
        const static void log(std::ostream& out, Args... args) {
            out << "[Warning]";
            using dummy = int[];
            dummy { (out << ' ' << args, 0)... };
            out << '\n';
        }
    };
    #endif


    #if defined(USE_ERROR_LOGGER) && !defined(NO_ERROR_LOGGING)
    template <>
    struct Logger <LogType::Error> {

        template <typename... Args>
        const static void log(Args... args) {
            Logger<LogType::Error>::log(std::cerr, args...);
        }

        template <typename... Args>
        const static void log(std::ostream& out, Args... args) {
            out << "[Error]";
            using dummy = int[];
            dummy { (out << ' ' << args, 0)... };
            out << '\n';
        }
    };
    #endif


    #if defined(USE_CRITICAL_LOGGER) && !defined(NO_CRITICAL_LOGGING)
    template <>
    struct Logger <LogType::Critical> {

        template <typename... Args>
        const static void log(Args... args) {
            Logger<LogType::Critical>::log(std::cerr, args...);
        }

        template <typename... Args>
        const static void log(std::ostream& out, Args... args) {
            out << "[Critical]";
            using dummy = int[];
            dummy { (out << ' ' << args, 0)... };
            out << '\n';
        }
    };
    #endif


    using DebugLogger = Logger<LogType::Debug>;
    using InfoLogger = Logger<LogType::Info>;
    using WarningLogger = Logger<LogType::Warning>;
    using ErrorLogger = Logger<LogType::Error>;
    using CriticalLogger = Logger<LogType::Critical>;

}  // namespace logging
