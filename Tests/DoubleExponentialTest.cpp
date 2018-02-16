#include "DoubleExponentialTest.h"

#include <QtTest/QtTest>

DoubleExponentialTest::DoubleExponentialTest()
{

}

void DoubleExponentialTest::testComputePreParameters()
{
   QVector<double> X = {1, 2, 3, 4, 5, 6, 7, 8, 9};
   QVector<double> Y = {1, 3, 5, 7, 9, 11, 13, 15, 17};
   QVector<double> preParameterMocks = {0.5, 0.5, 0.5, 0.5};
   QVector<double> preParameters = DoubleExponential::computePreParameters(X,Y);
   QVERIFY2(qFuzzyCompare(preParameters[0], preParameterMocks[0]), "First Pre-Parameter calculation failed!");
   QVERIFY2(qFuzzyCompare(preParameters[1], preParameterMocks[1]), "Second Pre-Parameter calculation failed!");
   QVERIFY2(qFuzzyCompare(preParameters[2], preParameterMocks[2]), "Third Pre-Parameter calculation failed!");
   QVERIFY2(qFuzzyCompare(preParameters[3], preParameterMocks[3]), "Fourth Pre-Parameter calculation failed!");
}

static DoubleExponentialTest DETest;
