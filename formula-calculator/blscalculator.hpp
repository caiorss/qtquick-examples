#ifndef BLSCALCULATOR_HPP
#define BLSCALCULATOR_HPP

#include <QObject>

class BlsCalculator : public QObject
{
    Q_OBJECT
public:
    explicit BlsCalculator(QObject *parent = nullptr);

signals:

public slots:
};

#endif // BLSCALCULATOR_HPP
