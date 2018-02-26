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
      void testComputeExperimentalClearance();
      void testComputeTheoreticalClearance();
};

#endif // DOUBLEEXPONENTIALTEST_H
