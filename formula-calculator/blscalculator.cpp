#include "blscalculator.hpp"
#include <cmath>
#include <iostream>

/** @brief Normal Probability Density Function (mean = 0) and standard deviation = 1  */
double normal_pdf(double x)
{
    return 1/(std::sqrt(2.0 * M_PI)) * std::exp(- x * x / 2);
}

/** @brief Cumulative normal distribution approximation  (with mean = 0 and standard deviation = 1)
 */
double normal_cdf(double d)
{
    constexpr double A [] =
        {
            0.31938153,
            -0.356563782,
            1.781477937,
            -1.821255978,
            1.330274429
        };
    constexpr double RSQRT2PI = 0.39894228040143267793994605993438;
    double K = 1.0 / (1.0 + 0.2316419 * std::fabs(d));
    double c = RSQRT2PI * std::exp(- 0.5 * d * d) *
               (K * (A[0] + K * (A[1] + K * (A[2] + K * (A[3] + K * A[4])))));
    if(d > 0) return 1.0 - c;
    return c;
}



double BlsCalculator::getK() const
{
    return K;
}

void BlsCalculator::setK(double value)
{
    if(K == value) return;
    K = value;
    std::cout << " [INFO] Updated K - strike price to " << K << std::endl;
    emit this->inputChanged();
}

double BlsCalculator::getS() const
{
    return S;
}

void BlsCalculator::setS(double value)
{
    if(S == value) return;
    S = value;
    emit this->inputChanged();
}

double BlsCalculator::getT() const
{
    return T;
}

void BlsCalculator::setT(double value)
{
    if(T == value) return;
    T = value;
    emit this->inputChanged();
}

double BlsCalculator::getV() const
{
    return v;
}

void BlsCalculator::setV(double value)
{
    if(v == value) return;
    v = value;
    emit this->inputChanged();
}

double BlsCalculator::getR() const
{
    return r;
}

void BlsCalculator::setR(double value)
{
    if(r == value) return;
    r = value;
    emit this->inputChanged();
}

double BlsCalculator::getQ() const
{
    return q;
}

void BlsCalculator::setQ(double value)
{
    if(q == value) return;
    q = value;
    emit this->inputChanged();
}

double BlsCalculator::callPrice() const
{
    int a = 1;
    double b = r;
    double sigma = v;
    double d1 = (log(S/K) + (b + sigma * sigma / 2.0) * T) / (sigma * sqrt(T));
    double d2 = d1 - sigma * std::sqrt(T);
    // Helper parameter
    double exp_brt = std::exp((b - r) * T);
    double exp_rt = std::exp(-r * T);

    a = 1;
    double Vcall = a * S * exp_brt * normal_cdf(a * d1)
                   - a * K * exp_rt * normal_cdf(a * d2);
    return Vcall;
}

double BlsCalculator::putPrice() const
{

    int a = -1;
    double b = r;
    double sigma = v;
    double d1 = (log(S/K) + (b + sigma * sigma / 2.0) * T) / (sigma * sqrt(T));
    double d2 = d1 - sigma * std::sqrt(T);
    // Helper parameter
    double exp_brt = std::exp((b - r) * T);
    double exp_rt = std::exp(-r * T);

    double Vput = a * S * exp_brt * normal_cdf(a * d1)
                  - a * K * exp_rt * normal_cdf(a * d2);

    return Vput;
}

BlsCalculator::BlsCalculator(QObject *parent)
    : QObject(parent)
    , K{0.0}, S{0.0}, T{0.0}, v{0.0}, r{0.0}, q{0.0}
{

}
