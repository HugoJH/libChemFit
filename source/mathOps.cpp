#include "mathOps.h"

#include <QtMath>

QVectorExtended mathOps::vLn(const QVectorExtended& X)
{
   QVectorExtended result;

   foreach (double d, X)
   {
      result << qLn(d);
   }
   return result;
}

QVectorExtended mathOps::vPow(const QVectorExtended& X, double power)
{
   QVectorExtended result;
   foreach (double d, X)
   {
      result << qPow(d, power);
   }
   return result;
}

QVectorExtended mathOps::vAbs(const QVectorExtended& X)
{
   QVectorExtended result;
   foreach (double d, X)
   {
      result << qAbs(d);
   }
   return result;
}

QVectorExtended mathOps::vAdd(const QVectorExtended& X, const QVectorExtended& Y)
{
   QVectorExtended result;

   for(int i = 0; i < X.count(); ++i)
   {
       result << X[i] + Y[i];
   }

   return result;
}

double mathOps::mean(const QVectorExtended& X)
{
   return sum(X) / X.count();
}

double mathOps::sum(const QVectorExtended& X)
{
   double result = 0;
   foreach (double d, X)
   {
      result += d;
   }
   return result;
}
double mathOps::var(const QVectorExtended &X)
{
    double result  = 0;
    double mean_x = mean(X);
    for(int i = 0; i < X.count(); ++i)
    {
        result  += qPow((X[i] - mean_x), 2);
    }

    return result / (X.count() - 1);
}


double mathOps::stdDev(const QVectorExtended &X)
{
    return sqrt(var(X));
}
double mathOps::stdResidualsSum(const QVectorExtended& sumOfComponents, const QVectorExtended& Y)
{
   QVectorExtended diffTC = mathOps::vPow(Y - sumOfComponents, 2);
   double stddiff = mathOps::stdDev(diffTC);
   return mathOps::sum(diffTC / stddiff);
}
