#ifndef BLSCALCULATOR_HPP
#define BLSCALCULATOR_HPP

#include <QObject>

class BlsCalculator : public QObject
{
    double K, S, T, v, r, q;

    Q_OBJECT
    Q_PROPERTY(double K READ getK WRITE setK NOTIFY inputChanged)
    Q_PROPERTY(double S READ getS WRITE setS NOTIFY inputChanged)
    Q_PROPERTY(double T READ getT WRITE setT NOTIFY inputChanged)
    Q_PROPERTY(double V READ getV WRITE setV NOTIFY inputChanged)
    Q_PROPERTY(double R READ getR WRITE setR NOTIFY inputChanged)
    Q_PROPERTY(double call READ callPrice NOTIFY inputChanged)
    Q_PROPERTY(double put  READ putPrice  NOTIFY inputChanged)
public:
    explicit BlsCalculator(QObject *parent = nullptr);

    double getK() const;
    void setK(double value);

    double getS() const;
    void setS(double value);

    double getT() const;
    void setT(double value);

    double getV() const;
    void setV(double value);

    double getR() const;
    void setR(double value);

    double getQ() const;
    void setQ(double value);

// Events
signals:
    void inputChanged();

public slots:
    double callPrice() const;
    double putPrice() const;
};

#endif // BLSCALCULATOR_HPP
