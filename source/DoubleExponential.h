#ifndef DOUBLEEXPONENTIAL_H
#define DOUBLEEXPONENTIAL_H

#include "QVectorExtended.h"

class DoubleExponential
{
   public:
      DoubleExponential();
      static QVectorExtended computeParameters(const QVectorExtended& X,
                                               const QVectorExtended& Y);
   private:
      static QVectorExtended computePreParameters(const QVectorExtended& X,
                                                  const QVectorExtended& Y);
      static QPair<double,double> computeSingleExponentialPreParameters(const QVectorExtended& X,
                                                                        const QVectorExtended& Y);
      static QPair<double,double> computeSingleExponentialParameters(const QVectorExtended& X,
                                                                     const QVectorExtended& Y);
      static int findBestIndex(const QVectorExtended& X,
                                          const QVectorExtended& Y);
      static double computeFirstPreParameter(const QVectorExtended& X,
                                             const QVectorExtended& Y);
      static double computeSecondPreParameter(const QVectorExtended& X,
                                             const QVectorExtended& Y);
};

#endif // DOUBLEEXPONENTIAL_H
