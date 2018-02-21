#include "DoubleExponentialTest.h"
#include "DoubleExponential.h"
#include <QtTest/QtTest>

DoubleExponentialTest::DoubleExponentialTest()
{

}

void DoubleExponentialTest::testComputePreParameters()
{
   QVectorExtended X = {1, 2, 3, 4, 5, 6, 7, 8, 9};
   QVectorExtended Y = {1, 3, 5, 7, 9, 11, 13, 15, 17};
   QVectorExtended preParameterMocks = {0.5, 0.5, 0.5, 0.5};
   QVectorExtended preParameters = DoubleExponential::computePreParameters(X, Y);
   QVERIFY2(qFuzzyCompare(preParameters[0], preParameterMocks[0]), "First Pre-Parameter calculation failed!");
   QVERIFY2(qFuzzyCompare(preParameters[1], preParameterMocks[1]), "Second Pre-Parameter calculation failed!");
   QVERIFY2(qFuzzyCompare(preParameters[2], preParameterMocks[2]), "Third Pre-Parameter calculation failed!");
   QVERIFY2(qFuzzyCompare(preParameters[3], preParameterMocks[3]), "Fourth Pre-Parameter calculation failed!");
}

void DoubleExponentialTest::testComputeFirstPreParameter()
{
   QVectorExtended X = {1, 2, 3, 4, 5, 6, 7, 8, 9};
   QVectorExtended Y = {1, 3, 5, 7, 9, 11, 13, 15, 17};
   double mockParameter = 0.9239717830465624;
   double parameter = DoubleExponential::computeFirstPreParameter(X, Y);
   QVERIFY2(qFuzzyCompare(parameter, mockParameter), "First Pre-Parameter calculation failed!");
}

void DoubleExponentialTest::testComputeSecondPreParameter()
{
   QVectorExtended X = {1, 2, 3, 4, 5, 6, 7, 8, 9};
   QVectorExtended Y = {1, 3, 5, 7, 9, 11, 13, 15, 17};
   double mockParameter = 0.2255319500077855;
   double parameter = DoubleExponential::computeSecondPreParameter(X, Y);
   QVERIFY2(qFuzzyCompare(parameter, mockParameter), "Second Pre-Parameter calculation failed!");
}

void DoubleExponentialTest::testComputeSingleExponentialPreParameters()
{
   QVectorExtended X = {1, 2, 3, 4, 5, 6, 7, 8, 9};
   QVectorExtended Y = {1, 3, 5, 7, 9, 11, 13, 15, 17};
   QPair<double, double> mockPreParameters({2.5192765652992453, 0.2255319500077855});
   QPair<double, double> PreParameters;
   PreParameters = DoubleExponential::computeSingleExponentialPreParameters(X, Y);
   QVERIFY2(qFuzzyCompare(PreParameters.first, mockPreParameters.first), "Single Exponential First Pre-Parameter calculation failed!");
   QVERIFY2(qFuzzyCompare(PreParameters.second, mockPreParameters.second), "Single Exponential Second Pre-Parameter calculation failed!");
}

static DoubleExponentialTest DETest;
