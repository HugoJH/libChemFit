#ifndef MATHOPS_H
#define MATHOPS_H

#include <QVector>

class mathOps
{
   public:

      static QVector<double> vLn(const QVector<double>& X);
      static QVector<double> vPow(const QVector<double>& X, double power);
      static QVector<double> vAbs(const QVector<double>& X);
      static double mean(const QVector<double>& X);
      static double sum(const QVector<double>& X);
};
QVector<double> operator+(const QVector<double> & X, const QVector<double> & Y);

QVector<double> operator+(const QVector<double> & X, double n);

QVector<double> operator+(double n, const QVector<double> & X);

QVector<double> operator*(const QVector<double> & X, const QVector<double> & Y);

#endif // MATHOPS_H
