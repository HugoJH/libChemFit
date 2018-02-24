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
      static double computeTheoreticalAreaUnderCurve(const QVectorExtended& X, const QVectorExtended& Y);
      static QVectorExtended computeAreaUnderCurvePartials(const QVectorExtended& X, const QVectorExtended& Y);
      static double computeExperimentalVolumeOfDistribution(const QVectorExtended& X, const QVectorExtended& Y, double doseInMicrograms);
      static double computeTheoreticalVolumeOfDistribution(const QVectorExtended& X, const QVectorExtended& Y, double doseInMicrograms);
      static double computeExperimentalClearance(const QVectorExtended& X, const QVectorExtended& Y, double doseInMicrograms);
      static double computeTheoreticalClearance(const QVectorExtended& X, const QVectorExtended& Y, double doseInMicrograms);
      static double computeHalfLife(const QVectorExtended& X, const QVectorExtended& Y, double doseInMicrograms);
   private:
      static double computeFirstPreParameter(const QVectorExtended & X, const QVectorExtended & Y);
      static double computeSecondPreParameter(const QVectorExtended & X, const QVectorExtended & Y);
      static QPair<double, double> computePreParameters(const QVectorExtended & X, const QVectorExtended & Y);
};

#endif // SINGLEEXPONENTIAL_H

