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
      static double computeTheoreticalAreaUnderCurve(const QVectorExtended& X,
                                                     const QVectorExtended& Y);
      static QVectorExtended computeAreaUnderCurvePartials(const QVectorExtended& X,
                                                           const QVectorExtended& Y);
      static double computeExperimentalClearance(const QVectorExtended& X,
                                                          const QVectorExtended& Y,
                                                          double doseInMicrograms);
      static double computeTheoreticalClearance(const QVectorExtended& X,
                                                 const QVectorExtended& Y,
                                                 double doseInMicrograms);
      static double computeHalfLifeAlphaPhase(const QVectorExtended& X,
                                              const QVectorExtended& Y);
      static double computeHalfLifeBetaPhase(const QVectorExtended& X,
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
