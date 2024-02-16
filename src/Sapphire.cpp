#include "Sapphire.h"

Sapphire::ErrorHandler *errorHandler;

void Sapphire::Init() 
{
    errorHandler = nullptr;
}

Sapphire::ErrorHandler::ErrorHandler() 
{
    throws = false;
    logs = false;
}

Sapphire::ErrorHandler::ErrorHandler(bool throws, bool logs) 
{
    this->throws = throws;
    this->logs = logs;
}

void Sapphire::ErrorHandler::setThrows(bool value) 
{
    throws = value;
}

void Sapphire::ErrorHandler::setLogs(bool value) 
{
    logs = value;
}

bool Sapphire::ErrorHandler::throwsErrors() 
{
    return throws;
}

bool Sapphire::ErrorHandler::logsErrors() 
{
    return logs;
}

std::vector<std::string> Sapphire::ErrorHandler::getErrors()
{
    return errors;
}

std::string Sapphire::ErrorHandler::getLastError() 
{
    return errors.back();
}

void Sapphire::ErrorHandler::err(const std::string& message) 
{
    errors.push_back(message);
    if (logs) std::cout << message;
    if (throws) throw std::runtime_error(message);
}

void Sapphire::SetErrorHandler(ErrorHandler& handler) 
{
    errorHandler = &handler;
}


