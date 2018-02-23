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

QPair<double, double> SingleExponential::computePreParameters(const QVectorExtended& X, const QVectorExtended& Y)
{
   QPair<double, double> preParameters;
   preParameters.first = computeFirstPreParameter(X, Y);
   preParameters.second = computeSecondPreParameter(X, Y);
   return preParameters;
}

QPair<double,double> SingleExponential::computeParameters(const QVectorExtended &X,
                                                          const QVectorExtended &Y)
{
   QPair<double,double> parameters(-1,-1);

   QPair<double, double> preParameters = computePreParameters(X, Y);

   if (!(std::isnan(preParameters.first) ||
         std::isnan(preParameters.second)))
   {
      QVariantList arguments;
      arguments.push_back(X.toQVariantList());
      arguments.push_back(Y.toQVariantList());
      arguments.push_back(preParameters.first);
      arguments.push_back(preParameters.second);

      QString moduleName = "fit1comp";
      QString functionName = "LMPARAMS";
      QVariant output = PythonInterface::getInstance().callFunction(moduleName, functionName, arguments);
      parameters.first = output.toList()[0].toDouble();
      parameters.second = output.toList()[1].toDouble();
   }
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

double SingleExponential::computeExperimentalAreaUnderCurve(const QVectorExtended& X, const QVectorExtended& Y)
{
   QPair<double, double> parameters = computeParameters(X, Y);
   QVector<double> vEAUC;
   double temp = (((parameters.first) + Y[0]) / 2.0);
   temp = temp * X[0];
   vEAUC << temp;

   for (int i = 0; i < (X.size() - 1); ++i )
   {
      int a = X[i + 1] - X[i];
      vEAUC << (a * Y[i]) - (a * ((Y[i] - Y[i + 1]) / 2));
   }

   vEAUC << Y.last() / parameters.second;

   return mathOps::sum(vEAUC);
}

double SingleExponential::computeTheoreticalAreaUnderCurve(const QVectorExtended& X, const QVectorExtended& Y)
{
   QPair<double, double> parameters = computeParameters(X, Y);
   return parameters.first/parameters.second;
}

double SingleExponential::computeExperimentalVolumeOfDistribution(const QVectorExtended& X, const QVectorExtended& Y)
{
   return 0.0;
}
