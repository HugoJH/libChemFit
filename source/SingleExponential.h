#ifndef SINGLEEXPONENTIAL_H
#define SINGLEEXPONENTIAL_H

#include "QVectorExtended.h"
#include <QVariantList>
#include <QPair>

class SingleExponential
{
   public:
      SingleExponential();
      static QPair<double, double> computeParameters(const QVectorExtended& X, const QVectorExtended& Y);
      static QVectorExtended computeExponential(const QVectorExtended& X, double P1, double P2);
      static double computeExperimentalAreaUnderCurve(const QVectorExtended& X, const QVectorExtended& Y);

   private:
      static double computeFirstPreParameter(const QVectorExtended & X, const QVectorExtended & Y);
      static double computeSecondPreParameter(const QVectorExtended & X, const QVectorExtended & Y);
      static QPair<double, double> computePreParameters(const QVectorExtended & X, const QVectorExtended & Y);
};

#endif // SINGLEEXPONENTIAL_H

