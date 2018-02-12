#ifndef MATHOPS_H
#define MATHOPS_H

#include <QVector>

class mathOps
{
   public:

      static QVector<double> vLn(const QVector<double>& X);
      static QVector<double> vPow(const QVector<double>& X, double power);
      static double mean(const QVector<double>& X);
      static double sum(const QVector<double>& X);
};

#endif // MATHOPS_H
