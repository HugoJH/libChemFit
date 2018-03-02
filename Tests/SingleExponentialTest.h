#ifndef TST_SINGLEEXPONENTIALTEST_H
#define TST_SINGLEEXPONENTIALTEST_H

#include "suite.h"

class SingleExponentialTest : public TestSuite
{
      Q_OBJECT
   public:
      SingleExponentialTest();
      using TestSuite::TestSuite;
   private slots:
      void testComputeParameters();
      void testComputeSingleExponential();
      void testComputeExperimentalAreaUnderCurve();
      void testComputeTheoreticalAreaUnderCurve();
      void testComputeAreaUnderCurvePartials();
      void testComputeExperimentalVolumeOfDistribution();
      void testComputeTheoreticalVolumeOfDistribution();
      void testComputeExperimentalClearance();
      void testComputeTheoreticalClearance();
      void testComputeHalfLife();
      void testComputeResidualsSum();
      void testComputeMRT();
      void testComputeVRT();
};

#endif // TST_SINGLEEXPONENTIALTEST_H
