#include "DoubleExponential.h"
#include "mathOps.h"

#include <QtMath>

DoubleExponential::DoubleExponential()
{

}

QVector<double> DoubleExponential::computePreParameters(const QVector<double>& X,
                                                        const QVector<double>& Y)
{
   QVector<double> preParameters= {0,0,0,0};
   return preParameters;
}


double DoubleExponential::computeFirstPreParameter(const QVector<double>& X,
                                                   const QVector<double>& Y)
{
   double num;
   double denom;

   num = (mathOps::sum(mathOps::vPow(X, 2) * Y) *
          mathOps::sum(Y * mathOps::vLn(Y))) -
           (mathOps::sum(X * Y) *
            mathOps::sum(Y * X * mathOps::vLn(Y)));

   denom = (mathOps::sum(Y) *
            mathOps::sum(mathOps::vPow(X, 2) * Y)) -
           qPow(mathOps::sum(X * Y), 2);

   return num / denom;
}
