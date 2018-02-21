#ifndef SINGLEEXPONENTIAL_H
#define SINGLEEXPONENTIAL_H

#include "QVectorExtended.h"
#include <QVariantList>
#include <QPair>

class SingleExponential
{
   public:
      SingleExponential();
      static double computeFirstPreParameter(const QVectorExtended & X, const QVectorExtended & Y);
      static double computeSecondPreParameter(const QVectorExtended & X, const QVectorExtended & Y);
      static QPair<double, double> computeParameters(const QVectorExtended& X, const QVectorExtended& Y, double pre1, double pre2);
      static QVectorExtended computeExponential(const QVectorExtended& X, double P1, double P2);
   private:
      static QVariantList prepareDataVector(const QVectorExtended& X);
};

#endif // SINGLEEXPONENTIAL_H

