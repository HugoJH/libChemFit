#include "tst_singleexponentialtest.h"

#include <QString>
#include <QtTest/QtTest>

#include "SingleExponential.h"

SingleExponentialTest::SingleExponentialTest()
{

}

void SingleExponentialTest::testcomputeFirstPreParameter()
{
   const double mock = -0.20228711901914495;
   QVector<double> X = {1, 2, 3, 4, 5};
   QVector<double> Y = {1, 3, 5, 7, 9};
   double P1 = SingleExponential::computeFirstPreParameter(X, Y);
   QVERIFY2(qFuzzyCompare(P1, mock), "Parameter calculation failed!");
}

void SingleExponentialTest::testcomputeSecondPreParameter()
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

static SingleExponentialTest SETest;
