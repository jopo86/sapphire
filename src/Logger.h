#pragma once

#include <iostream>
#include <string>
#include <vector>

/*
    @brief Sapphire is a C++ library that provides a large set of tools for developers.
    Every Sapphire function is under this namespace.
 */
namespace Sapphire {

    class Logger {
    public:

        /*
            @brief Creates a Logger object with all options enabled.
         */
        Logger();

        /*
            @brief Creates a Logger object with the specified options.
            @param logsEnabled If true, logs will be enabled.
            @param warningsEnabled If true, warnings will be enabled.
            @param errorsEnabled If true, errors will be enabled.
            @param throwsEnabled If true, errors will throw exceptions.
         */
        Logger(bool logsEnabled, bool warningsEnabled, bool errorsEnabled, bool throwsEnabled);
        
        /*
            @brief Logs a message.
            @param message The message to log.
         */
        void log(const std::string& message);

        /*
            @brief Logs a warning message.
            @param message The message to log.
         */
        void warn(const std::string& message);

        /*
            @brief Logs an error message.
            @param message The message to log.
         */
        void err(const std::string& message);

        /*
            @brief Gets whether logs are enabled.
            @return True if logs are enabled, false otherwise.
         */
        bool isLogsEnabled();

        /*
            @brief Gets whether warnings are enabled.
            @return True if warnings are enabled, false otherwise.
         */
        bool isWarningsEnabled();

        /*
            @brief Gets whether errors are enabled.
            @return True if errors are enabled, false otherwise.
         */
        bool isErrorsEnabled();

        /*
            @brief Gets whether errors throw exceptions.
            @return True if errors throw exceptions, false otherwise.
         */
        bool isThrowsEnabled();

        /*
            @brief Gets all log messages.
            @return A vector containing all logs.
         */
        std::vector<std::string> getLogs();

        /*
            @brief Gets all warning messages.
            @return A vector containing all warnings.
         */
        std::vector<std::string> getWarnings();

        /*
            @brief Gets all error messages.
            @return A vector containing all errors.
         */
        std::vector<std::string> getErrors();

        /*
            @brief Gets all messages (logs, warnings, errors)
            @return A vector containing all messages.
         */
        std::vector<std::string> getAllMessages();

        /*
            @brief Sets whether logs are enabled.
            @param value True to enable logs, false to disable them.
         */
        void setLogsEnabled(bool value);

        /*
            @brief Sets whether warnings are enabled.
            @param value True to enable warnings, false to disable them.
         */
        void setWarningsEnabled(bool value);

        /*
            @brief Sets whether errors are enabled.
            @param value True to enable errors, false to disable them.
         */
        void setErrorsEnabled(bool value);

        /*
            @brief Sets whether errors throw exceptions.
            @param value True to enable exceptions, false to disable them.
         */
        void setThrowsEnabled(bool value);

    private:
        bool logsEnabled;
        bool warningsEnabled;
        bool errorsEnabled;
        bool throwsEnabled;
        std::vector<std::string> logs;
        std::vector<std::string> warnings;
        std::vector<std::string> errors;
        std::vector<std::string> all;
    };
}