#ifndef BLSCALCULATOR_HPP
#define BLSCALCULATOR_HPP

#include <QObject>

/** Any class exposed to QML engine must inherit QObject */
class BlsCalculator : public QObject
{
    double K, S, T, v, r, q;

    /* Schema: Q_PROPERTY(<TYPE> <PROPERTY NAME>
     *                    READ   <getter Function>
     *                    WRITE  <setter Function>
     *                    NOTIFY <SIGNAL Function>) */
    Q_OBJECT // Necessary for exposing signals and slots to QML engine
    Q_PROPERTY(double K READ getK WRITE setK NOTIFY inputChanged)
    Q_PROPERTY(double S READ getS WRITE setS NOTIFY inputChanged)
    Q_PROPERTY(double T READ getT WRITE setT NOTIFY inputChanged)
    Q_PROPERTY(double V READ getV WRITE setV NOTIFY inputChanged)
    Q_PROPERTY(double R READ getR WRITE setR NOTIFY inputChanged)
    Q_PROPERTY(double call READ getCallPrice NOTIFY inputChanged)
    Q_PROPERTY(double put  READ getPutPrice  NOTIFY inputChanged)
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
    // Note: Function implemented by MOC - Meta-Object Compiler
    void inputChanged();

// Functions callable by QObject::connetc callback and also from QML engine
// slot is just a macro that evaluates to nothing.
public slots:
    double getCallPrice() const;
    double getPutPrice() const;
};

#endif // BLSCALCULATOR_HPP
