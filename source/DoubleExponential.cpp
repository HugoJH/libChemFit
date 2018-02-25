#include "DoubleExponential.h"
#include "SingleExponential.h"
#include "PythonInterface.h"
#include "mathOps.h"

#include <QtMath>

DoubleExponential::DoubleExponential()
{

}

QVectorExtended DoubleExponential::computePreParameters(const QVectorExtended& X,
                                                        const QVectorExtended& Y)
{
   QVectorExtended parameters;
   try
   {
      int bestIndex = findBestCombinationsofPreParametersIndex(X, Y);

      QPair<double,double> Comp2ParametersDefinitive;
      Comp2ParametersDefinitive = SingleExponential::computeParameters(X.mid(X.size() - bestIndex),
                                                                       Y.mid(Y.size() - bestIndex));

      QVector <double> Comp2ExponentialDefinitive = SingleExponential::computeExponential(
                                                       X,
                                                       Comp2ParametersDefinitive.first,
                                                       Comp2ParametersDefinitive.second);

      QVectorExtended lny2 = mathOps::vAbs(Y - Comp2ExponentialDefinitive);

      QPair<double,double> Comp1ParametersDefinitive;
      Comp1ParametersDefinitive = SingleExponential::computeParameters(X.mid(0, X.size() - bestIndex),
                                                                       lny2.mid(0, lny2.size() - bestIndex));

      parameters.push_back(Comp2ParametersDefinitive.first);
      parameters.push_back(Comp2ParametersDefinitive.second);
      parameters.push_back(Comp1ParametersDefinitive.first);
      parameters.push_back(Comp1ParametersDefinitive.second);
   }
   catch(int e)
   {
      return QVectorExtended({-1,-1,-1,-1});
   }

   return parameters;
}

QVectorExtended DoubleExponential::computeParameters(const QVectorExtended& X, const QVectorExtended& Y)
{
   QVectorExtended preParameters = computePreParameters(X,Y);

   QVariantList arguments;
   arguments.push_back(X.toQVariantList());
   arguments.push_back(Y.toQVariantList());
   arguments.push_back(preParameters[0]);
   arguments.push_back(preParameters[1]);
   arguments.push_back(preParameters[2]);
   arguments.push_back(preParameters[3]);

   QString moduleName = "fit2comp";
   QString functionName = "LM2COMP";
   QVariant output = PythonInterface::getInstance().callFunction(moduleName, functionName, arguments);
   QVectorExtended parameters({output.toList()[0].toDouble(),
                               output.toList()[1].toDouble(),
                               output.toList()[2].toDouble(),
                               output.toList()[3].toDouble()});
   return parameters;
}

QVectorExtended DoubleExponential::computeExponential(const QVectorExtended& X, const QVectorExtended& parameters)
{
   QVectorExtended exponential;
   foreach (const double& d, X)
   {
          exponential << (parameters[0] * exp(-parameters[2] * d)) + parameters[1] * exp(-parameters[3] * d);
   }
   return exponential;
}

int DoubleExponential::findBestCombinationsofPreParametersIndex(const QVectorExtended& X, const QVectorExtended& Y)
{
   int goldIndex = 2;
   double goldStdRes = 888888888;

   for (int z = 2; z < X.size(); ++z)
   {
      /*----------Segunda---exponencial-----------------*/
      QPair<double,double> parametersSEComp2;
      parametersSEComp2 = SingleExponential::computeParameters(X.mid(X.size() - z),
                                                               Y.mid(Y.size() - z));
      if ((std::isnan(parametersSEComp2.first) ||
           std::isnan(parametersSEComp2.second)))
      {
         continue;
      }

      QVectorExtended exponentialComp2;
      exponentialComp2 = SingleExponential::computeExponential(
                            X,
                            parametersSEComp2.first,
                            parametersSEComp2.second);

      QVectorExtended lny2 = mathOps::vAbs(Y - exponentialComp2);

      /*----------Primera---exponencial-----------------*/
      QPair<double, double> parametersSEComp1;
      parametersSEComp1 = SingleExponential::computeParameters(X.mid(0, X.size() - z),
                                                               lny2.mid(0, lny2.size() - z));

      if ((std::isnan(parametersSEComp1.first) ||
           std::isnan(parametersSEComp1.second)))
      {
         continue;
      }

      QVectorExtended exponentialComp1 = SingleExponential::computeExponential(
                                            X,
                                            parametersSEComp1.first,
                                            parametersSEComp1.second);

      double stdRes = mathOps::stdResidualsSum(exponentialComp2 +
                                               exponentialComp1, Y);
      if (stdRes < goldStdRes)
      {
         goldIndex = z;
         goldStdRes = stdRes;
      }
   }
   return goldIndex;
}


double DoubleExponential::computeFirstPreParameter(const QVectorExtended& X,
                                                   const QVectorExtended& Y)
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

double DoubleExponential::computeSecondPreParameter(const QVectorExtended& X, const QVectorExtended& Y)
{
   double num;
   double denom;

   num = (mathOps::sum(Y) *
          mathOps::sum(Y * X * mathOps::vLn(Y))) -
         (mathOps::sum(X * Y) *
          mathOps::sum(Y * mathOps::vLn(Y)));

   denom = (mathOps::sum(Y) *
            mathOps::sum(mathOps::vPow(X, 2) * Y)) -
           qPow(mathOps::sum(X * Y), 2);

   return num / denom;
}
