#ifndef DOUBLEEXPONENTIAL_H
#define DOUBLEEXPONENTIAL_H

#include "QVectorExtended.h"

class DoubleExponential
{
   public:
      DoubleExponential();
      static QVectorExtended computeParameters(const QVectorExtended& X,
                                               const QVectorExtended& Y);
      static QVectorExtended computeExponential(const QVectorExtended& X,
                                                const QVectorExtended& parameters);
      static double computeExperimentalAreaUnderCurve(const QVectorExtended& X,
                                                      const QVectorExtended& Y);

   private:
      static QVectorExtended computePreParameters(const QVectorExtended& X,
                                                  const QVectorExtended& Y);
      static int findBestCombinationsofPreParametersIndex(const QVectorExtended& X,
                                                          const QVectorExtended& Y);
      static double computeFirstPreParameter(const QVectorExtended& X,
                                             const QVectorExtended& Y);
      static double computeSecondPreParameter(const QVectorExtended& X,
                                              const QVectorExtended& Y);
};

#endif // DOUBLEEXPONENTIAL_H
