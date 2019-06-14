#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <QObject>

class Logger: public QObject
{
    Q_OBJECT
public:
    Logger();

public slots:
    void log(QString const& msg) const;
};

#endif // LOGGER_HPP
