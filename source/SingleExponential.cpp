#include "SingleExponential.h"

#include "mathOps.h"
#include <QtMath>


SingleExponential::SingleExponential()
{

}

double SingleExponential::computeFirstPreParameter(const QVector<double>& X, const QVector<double>& Y)
{
   double num;
   double denom;

   num = (mathOps::sum(mathOps::vLn(Y)) * \
          mathOps::sum(mathOps::vPow(X, 2))) - \
           (mathOps::sum(X) * \
            mathOps::sum(X * mathOps::vLn(Y)));

   denom = (X.size() * mathOps::sum(mathOps::vPow(X, 2))) - \
           (qPow(mathOps::sum(X), 2));

   return num / denom;

}

double SingleExponential::computeSecondPreParameter(const QVector<double>& X, const QVector<double>& Y)
{
   double num;
   double denom;

   num = (X.size() * mathOps::sum(X * mathOps::vLn(Y))) - \
           (mathOps::sum(X) * mathOps::sum(mathOps::vLn(Y)));

   denom = (X.size() * mathOps::sum(mathOps::vPow(X, 2))) - \
           (qPow(mathOps::sum(X), 2));

   return num / denom;
}
