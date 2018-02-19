#include "SingleExponential.h"

#include "mathOps.h"
#include "PythonInterface.h"
#include <QtMath>
#include <utility>

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

std::pair<double,double> SingleExponential::computeParameters(const QVector<double> &X,
                                                              const QVector<double> &Y,
                                                              double pre1,
                                                              double pre2)
{
   QVariantList arguments;

   arguments.push_back(prepareDataVector(X));
   arguments.push_back(prepareDataVector(Y));
   arguments.push_back(pre1);
   arguments.push_back(pre2);

   QString moduleName = "fit1comp";
   QString functionName = "LMPARAMS";
   PythonInterface pyInterface;
   QVariant output = pyInterface.callFunction(moduleName, functionName, arguments);
   std::pair<double,double> salida(output.toList()[0].toDouble(),
                                   output.toList()[1].toDouble());
   return salida;
}

QVector<double> SingleExponential::computeExponential(const QVector<double>& X, double P1, double P2)
{
   QVector <double> vector;
   for (int i = 0; i < X.size(); ++i)
   {
       vector.push_back(P1 * exp(-P2 * X[i]));
   }
   return vector;
}

QVariantList SingleExponential::prepareDataVector(const QVector<double>& X)
{
   QVariantList list;
   foreach( const double &item, X)
   {
      list << item;
   }
   return list;
}
