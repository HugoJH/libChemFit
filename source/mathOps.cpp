#include "mathOps.h"

#include <QtMath>

QVector<double> mathOps::vLn(const QVector<double>& X)
{
   QVector<double> result;

   foreach (double d, X)
   {
      result << qLn(d);
   }
   return result;
}

QVector<double> mathOps::vPow(const QVector<double>& X, double power)
{
   QVector<double> result;
   foreach (double d, X)
   {
      result << qPow(d, power);
   }
   return result;
}

double mathOps::mean(const QVector<double>& X)
{
   return sum(X) / X.count();
}

double mathOps::sum(const QVector<double>& X)
{
   double result = 0;
   foreach (double d, X)
   {
      result += d;
   }
   return result;
}
