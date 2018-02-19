#include "SingleExponentialTest.h"

#include <QString>
#include <QtTest/QtTest>

#include "SingleExponential.h"

SingleExponentialTest::SingleExponentialTest()
{

}

void SingleExponentialTest::testComputeFirstPreParameter()
{
   const double mock = -0.20228711901914495;
   QVector<double> X = {1, 2, 3, 4, 5};
   QVector<double> Y = {1, 3, 5, 7, 9};
   double P1 = SingleExponential::computeFirstPreParameter(X, Y);
   QVERIFY2(qFuzzyCompare(P1, mock), "Parameter calculation failed!");
}

void SingleExponentialTest::testComputeSecondPreParameter()
{
   const double mock = 0.5241747015059647;
   QVector<double> X = {1, 2, 3, 4, 5};
   QVector<double> Y = {1, 3, 5, 7, 9};
   double P2 = SingleExponential::computeSecondPreParameter(X, Y);
   QVERIFY2(qFuzzyCompare(P2, mock), "Pre-Parameter calculation failed!");
}

void SingleExponentialTest::testComputeParameters()
{
   const double mockP1 = 1.4078409462923063;
   const double mockP2 = -0.3802344472200062;
   QVector<double> X = {1, 2, 3, 4, 5};
   QVector<double> Y = {1, 3, 5, 7, 9};
   double Pre1 = 0.5;
   double Pre2 = 0.5;
   std::pair<double, double> parameters = SingleExponential::computeParameters(X, Y, Pre1, Pre2);
   QVERIFY2(qFuzzyCompare(parameters.first, mockP1), "First Parameter calculation failed!");
   QVERIFY2(qFuzzyCompare(parameters.second, mockP2), "Second Parameter calculation failed!");
}

void SingleExponentialTest::testComputeSingleExponential()
{
   QVector<double> X = {1, 2, 3, 4, 5};
   QVector<double> mockY = {2.0591468247998,
                            3.011764686380091,
                            4.405089727881871,
                            6.443005191754693,
                            9.423716306668418};
   const double mockP1 = 1.4078409462923063;
   const double mockP2 = -0.3802344472200062;
   QVector<double> EstY = SingleExponential::computeExponential(X, mockP1, mockP2);
   for (int t = 0; t < EstY.size(); ++t)
   {
      QVERIFY2(qFuzzyCompare(EstY[t], mockY[t]), "Single exponential computation failed");
   }
}

static SingleExponentialTest SETest;
