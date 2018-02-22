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
      int goldIndex = 2;
      double goldStdRes = 888888888;

      for (int z = 2; z < X.size(); ++z)
      {
         /*----------Segunda---exponencial-----------------*/
         QPair<double, double> Comp2PreParameters;
         Comp2PreParameters = computeSingleExponentialPreParameters(
                                 X.mid(X.size() - z),
                                 Y.mid(Y.size() - z));

         QPair<double,double> parametersSEComp2;
         QPair<double,double> parametersSEComp1;

         //check for NaNs
         if (!(std::isnan(Comp2PreParameters.first) ||
               std::isnan(Comp2PreParameters.second)))
         {

            parametersSEComp2 = SingleExponential::computeParameters(
                                   X.mid(X.size() - z),
                                   Y.mid(Y.size() - z),
                                   Comp2PreParameters.first,
                                   abs(Comp2PreParameters.second));
            //check for NaNs
            if ((std::isnan(parametersSEComp2.first) ||
                 std::isnan(parametersSEComp2.second)))
            {

               continue;
            }

         }
         else
         {
            continue;
         }

         QVectorExtended exponentialComp2;
         exponentialComp2 = SingleExponential::computeExponential(
                               X,
                               parametersSEComp2.first,
                               parametersSEComp2.second);

         QVectorExtended lny2 = mathOps::vAbs(Y - exponentialComp2);
         QPair<double, double> Comp1PreParameters;
         Comp1PreParameters = computeSingleExponentialPreParameters(
                                 X.mid(0, X.size() - z),
                                 lny2.mid(0, lny2.size() - z));

         if (!(std::isnan(Comp1PreParameters.first) ||
               std::isnan(Comp1PreParameters.second)))
         {
            parametersSEComp1 = SingleExponential::computeParameters(
                                   X.mid(0, X.size() - z),
                                   lny2.mid(0, lny2.size() - z),
                                   Comp1PreParameters.first,
                                   abs(Comp1PreParameters.second));

            if ((std::isnan(parametersSEComp1.first) ||
                 std::isnan(parametersSEComp1.second)))
            {
               continue;
            }
         }
         else
         {
            continue;
         }

         /*----------Primera---exponencial-----------------*/
         QVectorExtended exponentialComp1 = SingleExponential::computeExponential(
                                               X,
                                               parametersSEComp1.first,
                                               parametersSEComp1.second);
         //Check on the operator overloading clashing between qvector.h and mathOps
         double stdRes = mathOps::stdResidualsSum(exponentialComp2 + exponentialComp1,
                                                  Y);
         if (stdRes < goldStdRes)
         {
            goldIndex = z;
            goldStdRes = stdRes;
         }
      }

      //residualsSum_ = goldStdRes;

      QPair<double, double> Comp2PreParametersDefinitive;
      Comp2PreParametersDefinitive = computeSingleExponentialPreParameters(X.mid(X.size() - goldIndex),
                                                                           Y.mid(Y.size() - goldIndex));

      QPair<double,double> Comp2ParametersDefinitive;
      Comp2ParametersDefinitive = SingleExponential::computeParameters(X.mid(X.size() - goldIndex),
                                                                       Y.mid(Y.size() - goldIndex),
                                                                       Comp2PreParametersDefinitive.first,
                                                                       Comp2PreParametersDefinitive.second);

      QVector <double> Comp2ExponentialDefinitive = SingleExponential::computeExponential(
                                                       X,
                                                       Comp2ParametersDefinitive.first,
                                                       Comp2ParametersDefinitive.second);


      QVectorExtended lny2 = mathOps::vAbs(Y - Comp2ExponentialDefinitive);
      QPair<double, double> Comp1PreParametersDefinitive;
      Comp1PreParametersDefinitive = computeSingleExponentialPreParameters(X.mid(0, X.size()- goldIndex),
                                                                           lny2.mid(0, lny2.size() - goldIndex));

      QPair<double, double> Comp1ParametersDefinitive ;

      Comp1ParametersDefinitive = SingleExponential::computeParameters(
                                     X.mid(0, X.size() - goldIndex),
                                     lny2.mid(0, lny2.size() - goldIndex),
                                     Comp1PreParametersDefinitive.first, abs(Comp1PreParametersDefinitive.second));

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

QPair<double, double> DoubleExponential::computeSingleExponentialPreParameters(const QVectorExtended& X, const QVectorExtended& Y)
{
   QPair<double, double> preParameters;
   preParameters.first = exp(computeFirstPreParameter(X,Y));
   preParameters.second = computeSecondPreParameter(X,Y);
   return preParameters;
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
