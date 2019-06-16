#include "logger.hpp"

#include <iostream>

Logger::Logger()
{

}

void Logger::log(const QString &msg) const
{
    std::cout << msg.toStdString() << std::endl;
}

void Logger::info(const QString &msg) const
{
    std::cout << " [INFO] " << msg.toStdString() << std::endl;
}
