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
   QVectorExtended preParameterMocks = {5.091755654710844,
                                        0.4440122241613212,
                                        3.572062983850337,
                                        -0.1775673740401609};
   QVectorExtended preParameters = DoubleExponential::computePreParameters(X, Y);
   QVERIFY2(qFuzzyCompare(preParameters[0], preParameterMocks[0]), "First pre-parameter calculation failed!");
   QVERIFY2(qFuzzyCompare(preParameters[1], preParameterMocks[1]), "Second pre-parameter calculation failed!");
   QVERIFY2(qFuzzyCompare(preParameters[2], preParameterMocks[2]), "Third pre-parameter calculation failed!");
   QVERIFY2(qFuzzyCompare(preParameters[3], preParameterMocks[3]), "Fourth pre-parameter calculation failed!");
}

void DoubleExponentialTest::testComputeParameters()
{
   QVectorExtended X = {1, 2, 3, 4, 5, 6, 7, 8, 9};
   QVectorExtended Y = {1, 3, 5, 7, 9, 11, 13, 15, 17};
   QVectorExtended parameterMocks = {0.5, 0.5, 0.5, 0.5};
   QVectorExtended parameters = DoubleExponential::computeParameters(X, Y);
   QVERIFY2(qFuzzyCompare(parameters[0], parameterMocks[0]), "First parameter calculation failed!");
   QVERIFY2(qFuzzyCompare(parameters[1], parameterMocks[1]), "Second parameter calculation failed!");
   QVERIFY2(qFuzzyCompare(parameters[2], parameterMocks[2]), "Third parameter calculation failed!");
   QVERIFY2(qFuzzyCompare(parameters[3], parameterMocks[3]), "Fourth parameter calculation failed!");
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
