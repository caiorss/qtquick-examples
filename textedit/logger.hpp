#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <QObject>

/** Logger for QML engine */
class Logger: public QObject
{
    Q_OBJECT
public:
    Logger();

public slots:
    void log(QString const& msg) const;
    void info(QString const& msg) const;

};

#endif // LOGGER_HPP
