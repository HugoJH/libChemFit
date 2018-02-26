#ifndef DOUBLEEXPONENTIALTEST_H
#define DOUBLEEXPONENTIALTEST_H

#include "suite.h"

class DoubleExponentialTest : public TestSuite
{
      Q_OBJECT
   public:
      DoubleExponentialTest();
      using TestSuite::TestSuite;
   private slots:
      void testComputeParameters();
      void testComputeDoubleExponential();
      void testComputeExperimentalAreaUnderCurve();
      void testComputeTheoreticalAreaUnderCurve();
      void testComputeAreaUnderCurvePartials();
      void testComputeExperimentalVolumeOfDistribution();
      void testComputeTheoreticalVolumeOfDistribution();
      void testComputeExperimentalClearance();
      void testComputeTheoreticalClearance();
      void testComputeHalfLifeAlphaPhase();
      void testComputeHalfLifeBetaPhase();
      void testComputeResidualsSum();
};

#endif // DOUBLEEXPONENTIALTEST_H
