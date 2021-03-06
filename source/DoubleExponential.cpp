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

      parameters.push_back(Comp1ParametersDefinitive.first);
      parameters.push_back(Comp1ParametersDefinitive.second);
      parameters.push_back(Comp2ParametersDefinitive.first);
      parameters.push_back(Comp2ParametersDefinitive.second);
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
      exponential << (parameters[0] * exp(-parameters[1] * d)) + parameters[2] * exp(-parameters[3] * d);
   }
   return exponential;
}

double DoubleExponential::computeExperimentalAreaUnderCurve(const QVectorExtended& X, const QVectorExtended& Y)
{
   return mathOps::sum(computeAreaUnderCurvePartials(X, Y));
}

double DoubleExponential::computeTheoreticalAreaUnderCurve(const QVectorExtended& X, const QVectorExtended& Y)
{
   QVectorExtended parameters = computeParameters(X, Y);
   return ((parameters[0] / parameters[1]) + (parameters[2] / parameters[3]));
}

QVectorExtended DoubleExponential::computeAreaUnderCurvePartials(const QVectorExtended& X, const QVectorExtended& Y)
{
   QVectorExtended vEAUC;
   QVectorExtended parameters = computeParameters(X, Y);

   double temp = (parameters[0] + parameters[2] + Y[0]) / 2;
   temp = temp * X[0];
   vEAUC << temp;

   for (int i = 0; i < (X.size() - 1); ++i)
   {
      int a = X[i + 1] - X[i];

      vEAUC << (a * Y[i]) - (a * ((Y[i] - Y[i + 1]) / 2));
   }

   vEAUC << ((Y.last() / parameters.last()));
   return vEAUC;
}

double DoubleExponential::computeExperimentalVolumeOfDistribution(const QVectorExtended& X, const QVectorExtended& Y, double doseInMicrograms)
{
   double EAUC = computeExperimentalAreaUnderCurve(X, Y);
   QVectorExtended parameters = computeParameters(X, Y);
   return doseInMicrograms / ((parameters[1]+parameters[3]) * EAUC);
}

double DoubleExponential::computeTheoreticalVolumeOfDistribution(const QVectorExtended& X, const QVectorExtended& Y, double doseInMicrograms)
{
   double TAUC = computeTheoreticalAreaUnderCurve(X, Y);
   QVectorExtended parameters = computeParameters(X, Y);
   return doseInMicrograms / ((parameters[1] + parameters[3]) * TAUC);
}

double DoubleExponential::computeExperimentalClearance(const QVectorExtended& X, const QVectorExtended& Y, double doseInMicrograms)
{
   return doseInMicrograms / computeExperimentalAreaUnderCurve(X, Y);
}

double DoubleExponential::computeTheoreticalClearance(const QVectorExtended& X, const QVectorExtended& Y, double doseInMicrograms)
{
   return doseInMicrograms / computeTheoreticalAreaUnderCurve(X, Y);
}

double DoubleExponential::computeHalfLifeAlphaPhase(const QVectorExtended& X, const QVectorExtended& Y)
{
   QVectorExtended parameters = computeParameters(X, Y);
   return qLn(2) / parameters[1];
}

double DoubleExponential::computeHalfLifeBetaPhase(const QVectorExtended& X, const QVectorExtended& Y)
{
   QVectorExtended parameters = computeParameters(X, Y);
   return qLn(2) / parameters[3];
}

double DoubleExponential::computeResidualsSum(const QVectorExtended& X, const QVectorExtended& Y)
{
   int index = findBestCombinationsofPreParametersIndex(X,Y);
   QVectorExtended compoundExponential = compoundExponentialFromTwoSingleExponentials(X, Y, index);
   double stdRes = mathOps::stdResidualsSum(compoundExponential, Y);
   return stdRes;
}

double DoubleExponential::computeMRT(const QVectorExtended& X, const QVectorExtended& Y)
{
   double EAUMC = DoubleExponential::computeExperimentalAreaUnderCurve(X, X * Y);
   double EAUC = DoubleExponential::computeExperimentalAreaUnderCurve(X, Y);

   return EAUMC/EAUC;
}

double DoubleExponential::computeVRT(const QVectorExtended& X, const QVectorExtended& Y)
{
   double MRT = computeMRT(X, Y);
   double VRT_numerator = DoubleExponential::computeTheoreticalAreaUnderCurve(X, Y * mathOps::vPow(X - MRT, 2));
   double VRT_denominator = DoubleExponential::computeTheoreticalAreaUnderCurve(X, Y);

   return VRT_numerator / VRT_denominator;
}

int DoubleExponential::findBestCombinationsofPreParametersIndex(const QVectorExtended& X, const QVectorExtended& Y)
{
   int goldIndex = 2;
   double goldStdRes = 888888888;

   for (int z = 2; z < X.size(); ++z)
   {
      QVectorExtended compoundExponential = compoundExponentialFromTwoSingleExponentials(X, Y, z);
      if (compoundExponential.isEmpty())
      {
         continue;
      }
      double stdRes = mathOps::stdResidualsSum(compoundExponential, Y);
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

QVectorExtended DoubleExponential::compoundExponentialFromTwoSingleExponentials(const QVectorExtended& X, const QVectorExtended& Y, int index)
{
   /*----------Segunda---exponencial-----------------*/
   QPair<double,double> parametersSEComp2;
   parametersSEComp2 = SingleExponential::computeParameters(X.mid(X.size() - index),
                                                            Y.mid(Y.size() - index));
   if ((std::isnan(parametersSEComp2.first) ||
        std::isnan(parametersSEComp2.second)))
   {
      return QVectorExtended();
   }

   QVectorExtended exponentialComp2;
   exponentialComp2 = SingleExponential::computeExponential(X,
                                                            parametersSEComp2.first,
                                                            parametersSEComp2.second);

   QVectorExtended lny2 = mathOps::vAbs(Y - exponentialComp2);

   /*----------Primera---exponencial-----------------*/
   QPair<double, double> parametersSEComp1;
   parametersSEComp1 = SingleExponential::computeParameters(X.mid(0, X.size() - index),
                                                            lny2.mid(0, lny2.size() - index));

   if ((std::isnan(parametersSEComp1.first) ||
        std::isnan(parametersSEComp1.second)))
   {
      return QVectorExtended();
   }

   QVectorExtended exponentialComp1;
   exponentialComp1 = SingleExponential::computeExponential(X,
                                                            parametersSEComp1.first,
                                                            parametersSEComp1.second);
   return (exponentialComp1 + exponentialComp2);
}
