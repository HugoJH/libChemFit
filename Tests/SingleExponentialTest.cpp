#include "SingleExponentialTest.h"

#include <QString>
#include <QtTest/QtTest>

#include "SingleExponential.h"

SingleExponentialTest::SingleExponentialTest()
{

}

void SingleExponentialTest::testComputeParameters()
{
   const double mockP1 = -13.012171317394735;
   const double mockP2 = 69.75789628400081;
   QVectorExtended X = {1, 2, 3, 4, 5};
   QVectorExtended Y = {1, 3, 5, 7, 9};
   QPair<double, double> parameters = SingleExponential::computeParameters(X, Y);
   QVERIFY2(qFuzzyCompare(parameters.first, mockP1), "First Parameter calculation failed!");
   QVERIFY2(qFuzzyCompare(parameters.second, mockP2), "Second Parameter calculation failed!");
}

void SingleExponentialTest::testComputeSingleExponential()
{
   QVectorExtended X = {1, 2, 3, 4, 5};
   QVectorExtended mockY = {2.0591468247998,
                            3.011764686380091,
                            4.405089727881871,
                            6.443005191754693,
                            9.423716306668418};
   const double mockP1 = 1.4078409462923063;
   const double mockP2 = -0.3802344472200062;
   QVectorExtended EstY = SingleExponential::computeExponential(X, mockP1, mockP2);
   for (int t = 0; t < EstY.size(); ++t)
   {
      QVERIFY2(qFuzzyCompare(EstY[t], mockY[t]), "Single exponential computation failed");
   }
}

static SingleExponentialTest SETest;
