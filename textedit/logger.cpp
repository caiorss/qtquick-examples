#include "logger.hpp"

#include <iostream>

Logger::Logger()
{

}

void Logger::log(const QString &msg) const
{
    std::cout << msg.toStdString() << std::endl;
}
