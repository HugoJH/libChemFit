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

QVector<double> mathOps::vAbs(const QVector<double>& X)
{
   QVector<double> result;
   foreach (double d, X)
   {
      result << qAbs(d);
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
double mathOps::var(const QVector<double> &X)
{
    double result  = 0;
    double mean_x = mean(X);
    for(int i = 0; i < X.count(); ++i)
    {
        result  += qPow((X[i] - mean_x), 2);
    }

    return result / (X.count() - 1);
}


double mathOps::stdDev(const QVector<double> &X)
{
    return sqrt(var(X));
}
double mathOps::stdResidualsSum(const QVector<double>& sumOfComponents, const QVector<double>& Y)
{
   QVector<double> diffTC = mathOps::vPow(Y - sumOfComponents, 2);
   double stddiff = mathOps::stdDev(diffTC);
   return mathOps::sum(diffTC / stddiff);
}

QVector<double> operator+(const QVector<double>& X, const QVector<double>& Y)
{
   QVector<double> result;

   for (int i = 0; i < X.count(); ++i)
   {
      result << X[i] + Y[i];
   }
   return result;
}

QVector<double> operator+(const QVector<double>& X, double n)
{
   QVector<double> result;

   for (int i = 0; i < X.count(); ++i)
   {
      result << X[i] + n;
   }
   return result;
}

QVector<double> operator+(double n, const QVector<double>& X)
{
   return operator +(X, n);
}

QVector<double> operator*(const QVector<double>& X, const QVector<double>& Y)
{
   QVector<double> result;

   for (int i = 0; i < X.count(); ++i)
   {
      result << X[i] * Y[i];
   }
   return result;
}

QVector<double> operator-(const QVector<double>& X, const QVector<double>& Y)
{
   QVector<double> result;

   for (int i = 0; i < X.count(); ++i)
   {
      result << X[i] - Y[i];
   }
   return result;
}

QVector<double> operator/(const QVector<double>& X, double n)
{
   QVector<double> result;

   for (int i = 0; i < X.count(); ++i)
   {
      result << X[i] / n;
   }
   return result;
}
