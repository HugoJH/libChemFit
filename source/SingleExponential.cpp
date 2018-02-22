#include "SingleExponential.h"

#include "mathOps.h"
#include "PythonInterface.h"
#include <QtMath>
#include <utility>
#include <QPair>

SingleExponential::SingleExponential()
{

}

double SingleExponential::computeFirstPreParameter(const QVectorExtended& X, const QVectorExtended& Y)
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

double SingleExponential::computeSecondPreParameter(const QVectorExtended& X, const QVectorExtended& Y)
{
   double num;
   double denom;

   num = (X.size() * mathOps::sum(X * mathOps::vLn(Y))) - \
           (mathOps::sum(X) * mathOps::sum(mathOps::vLn(Y)));

   denom = (X.size() * mathOps::sum(mathOps::vPow(X, 2))) - \
           (qPow(mathOps::sum(X), 2));

   return num / denom;
}

QPair<double,double> SingleExponential::computeParameters(const QVectorExtended &X,
                                                          const QVectorExtended &Y,
                                                          double pre1,
                                                          double pre2)
{
   QVariantList arguments;

   arguments.push_back(X.toQVariantList());
   arguments.push_back(Y.toQVariantList());
   arguments.push_back(pre1);
   arguments.push_back(pre2);

   QString moduleName = "fit1comp";
   QString functionName = "LMPARAMS";
   QVariant output = PythonInterface::getInstance().callFunction(moduleName, functionName, arguments);
   QPair<double,double> parameters(output.toList()[0].toDouble(), output.toList()[1].toDouble());
   return parameters;
}

QVectorExtended SingleExponential::computeExponential(const QVectorExtended& X, double P1, double P2)
{
   QVectorExtended vector;
   for (int i = 0; i < X.size(); ++i)
   {
       vector.push_back(P1 * exp(-P2 * X[i]));
   }
   return vector;
}
