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
      void testcomputeFirstPreParameter();
      void testcomputeSecondPreParameter();
};

#endif // TST_SINGLEEXPONENTIALTEST_H
