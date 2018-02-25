#include "DoubleExponentialTest.h"
#include "DoubleExponential.h"
#include <QtTest/QtTest>

DoubleExponentialTest::DoubleExponentialTest()
{

}

void DoubleExponentialTest::testComputeParameters()
{
   QVectorExtended X = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
   QVectorExtended Y = {2,
                        1.2727168592074,
                        0.954066036314595,
                        0.790605289049582,
                        0.688635684924374,
                        0.613268606711719,
                        0.551290388270693,
                        0.497497185756964,
                        0.449664426745124,
                        0.406693069544686,
                        0.367924841101205};
   QVectorExtended parameterMocks = {0.9999999999999982, 1.000000000000003, 1.000000000000001, 0.1000000000000001};
   QVectorExtended parameters = DoubleExponential::computeParameters(X, Y);
   QVERIFY2(qFuzzyCompare(parameters[0], parameterMocks[0]), "First parameter calculation failed!");
   QVERIFY2(qFuzzyCompare(parameters[1], parameterMocks[1]), "Second parameter calculation failed!");
   QVERIFY2(qFuzzyCompare(parameters[2], parameterMocks[2]), "Third parameter calculation failed!");
   QVERIFY2(qFuzzyCompare(parameters[3], parameterMocks[3]), "Fourth parameter calculation failed!");
}

void DoubleExponentialTest::testComputeDoubleExponential()
{
   QVectorExtended mockX = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
   QVectorExtended mockY = {2,
                        1.2727168592074,
                        0.954066036314595,
                        0.790605289049582,
                        0.688635684924374,
                        0.613268606711719,
                        0.551290388270693,
                        0.497497185756964,
                        0.449664426745124,
                        0.406693069544686,
                        0.367924841101205};
   QVectorExtended mockParameters = {0.9999999999999982,
                                     1.000000000000003,
                                     1.000000000000001,
                                     0.1000000000000001};

   QVectorExtended EstY = DoubleExponential::computeExponential(mockX, mockParameters);

   for (int t = 0; t < EstY.size(); ++t)
   {
      QVERIFY2(qFuzzyCompare(EstY[t], mockY[t]), "Double exponential computation failed");
   }
}

void DoubleExponentialTest::testComputeExperimentalAreaUnderCurve()
{
   QVectorExtended X = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
   QVectorExtended Y = {2,
                        1.2727168592074,
                        0.954066036314595,
                        0.790605289049582,
                        0.688635684924374,
                        0.613268606711719,
                        0.551290388270693,
                        0.497497185756964,
                        0.449664426745124,
                        0.406693069544686,
                        0.367924841101205};
   const double mockEAUC = 11.087648378087785;
   double EAUC = DoubleExponential::computeExperimentalAreaUnderCurve(X, Y);
   QVERIFY2(qFuzzyCompare(EAUC, mockEAUC), "EAUC calculation failed!");
}

void DoubleExponentialTest::testComputeTheoreticalAreaUnderCurve()
{
   QVectorExtended X = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
   QVectorExtended Y = {2,
                        1.2727168592074,
                        0.954066036314595,
                        0.790605289049582,
                        0.688635684924374,
                        0.613268606711719,
                        0.551290388270693,
                        0.497497185756964,
                        0.449664426745124,
                        0.406693069544686,
                        0.367924841101205};
   const double mockTAUC = 8.469526780929929;
   double TAUC = DoubleExponential::computeTheoreticalAreaUnderCurve(X, Y);
   QVERIFY2(qFuzzyCompare(TAUC, mockTAUC), "TAUC calculation failed!");
}

static DoubleExponentialTest DETest;
