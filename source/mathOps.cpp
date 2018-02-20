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

QVector<double> operator+(const QVector<double>& X, const QVector<double>& Y)
{
   QVector<double> temp;

   for (int i = 0; i < X.count(); ++i)
   {
      temp << Y[i] + X[i];
   }
   return temp;
}

QVector<double> operator+(const QVector<double>& X, double n)
{
   QVector<double> temp;

   for (int i = 0; i < X.count(); ++i)
   {
      temp << X[i] + n;
   }
   return temp;
}

QVector<double> operator+(double n, const QVector<double>& X)
{
   return operator +(X, n);
}

QVector<double> operator*(const QVector<double>& X, const QVector<double>& Y)
{
   QVector<double> temp;

   for (int i = 0; i < X.count(); ++i)
   {
      temp << X[i] * Y[i];
   }
   return temp;
}
