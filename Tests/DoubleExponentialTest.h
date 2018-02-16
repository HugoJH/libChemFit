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
      void testComputePreParameters();
      void testComputeFirstPreParameter();
};

#endif // DOUBLEEXPONENTIALTEST_H