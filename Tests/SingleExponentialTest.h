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
      void testComputeFirstPreParameter();
      void testComputeSecondPreParameter();
      void testComputeParameters();
      void testComputeSingleExponential();
};

#endif // TST_SINGLEEXPONENTIALTEST_H
