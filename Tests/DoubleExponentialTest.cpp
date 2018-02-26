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
   const double mockTAUC = 10.999999999999995;
   double TAUC = DoubleExponential::computeTheoreticalAreaUnderCurve(X, Y);
   QVERIFY2(qFuzzyCompare(TAUC, mockTAUC), "TAUC calculation failed!");
}

void DoubleExponentialTest::testComputeAreaUnderCurvePartials()
{
   QVectorExtended X = {125, 180, 255, 300, 450, 480};
   QVectorExtended Y = {210.52,
                        192.47,
                        172.51,
                        162.61,
                        125.91,
                        120.73};
   QVectorExtended mockAUCPartials = {27916.06208529732,
                                      11082.225,
                                      13686.75,
                                      7540.200000000001,
                                      21639,
                                      3699.6,
                                      76831.9058466466};

   QVectorExtended AUCPArtials = DoubleExponential::computeAreaUnderCurvePartials(X, Y);
   for(int i = 0; i < AUCPArtials.size(); ++i)
   {
      QVERIFY2(qFuzzyCompare(mockAUCPartials[i], AUCPArtials[i]), "AUC partials calculation failed!");
   }
}

void DoubleExponentialTest::testComputeExperimentalVolumeOfDistribution()
{
   QVectorExtended X = {125, 180, 255, 300, 450, 480};
   QVectorExtended Y = {210.52,
                        192.47,
                        172.51,
                        162.61,
                        125.91,
                        120.73};
   const double mockEVoD = 6338.828898133474;
   double mockDose = 3.235e6;
   double EVoD = DoubleExponential::computeExperimentalVolumeOfDistribution(X, Y, mockDose);
   QVERIFY2(qFuzzyCompare(EVoD, mockEVoD), "EVoD calculation failed!");
}

void DoubleExponentialTest::testComputeTheoreticalVolumeOfDistribution()
{
   QVectorExtended X = {125, 180, 255, 300, 450, 480};
   QVectorExtended Y = {210.52,
                        192.47,
                        172.51,
                        162.61,
                        125.91,
                        120.73};
   const double mockTVoD = 6295.564985629097;
   double mockDose = 3.235e6;
   double TVoD = DoubleExponential::computeTheoreticalVolumeOfDistribution(X, Y, mockDose);
   QVERIFY2(qFuzzyCompare(TVoD, mockTVoD), "TVoD calculation failed!");
}

void DoubleExponentialTest::testComputeExperimentalClearance()
{
   QVectorExtended X = {125, 180, 255, 300, 450, 480};
   QVectorExtended Y = {210.52,
                        192.47,
                        172.51,
                        162.61,
                        125.91,
                        120.73};
   const double mockECL = 19.920472923700405;
   double mockDose = 3.235e6;
   double ECL = DoubleExponential::computeExperimentalClearance(X, Y, mockDose);
   QVERIFY2(qFuzzyCompare(ECL, mockECL), "ECL calculation failed!");
}

void DoubleExponentialTest::testComputeTheoreticalClearance()
{
   QVectorExtended X = {125, 180, 255, 300, 450, 480};
   QVectorExtended Y = {210.52,
                        192.47,
                        172.51,
                        162.61,
                        125.91,
                        120.73};
   const double mockTCL = 19.784511279764796;
   double mockDose = 3.235e6;
   double TCL = DoubleExponential::computeTheoreticalClearance(X, Y, mockDose);
   QVERIFY2(qFuzzyCompare(TCL, mockTCL), "TCL calculation failed!");
}

void DoubleExponentialTest::testComputeHalfLifeAlphaPhase()
{
   QVectorExtended X = {125, 180, 255, 300, 450, 480};
   QVectorExtended Y = {210.52,
                        192.47,
                        172.51,
                        162.61,
                        125.91,
                        120.73};
   const double mockHLAP = 441.1413991832305;
   double HLAP = DoubleExponential::computeHalfLifeAlphaPhase(X, Y);
   QVERIFY2(qFuzzyCompare(HLAP, mockHLAP), "Half Life Alpha Phase calculation failed!");
}

void DoubleExponentialTest::testComputeHalfLifeBetaPhase()
{
   QVectorExtended X = {125, 180, 255, 300, 450, 480};
   QVectorExtended Y = {210.52,
                        192.47,
                        172.51,
                        162.61,
                        125.91,
                        120.73};
   const double mockHLBP = 441.11504112192716;
   double HLBP = DoubleExponential::computeHalfLifeBetaPhase(X, Y);
   QVERIFY2(qFuzzyCompare(HLBP, mockHLBP), "Half Life Beta Phase calculation failed!");
}

void DoubleExponentialTest::testComputeResidualsSum()
{
   QVectorExtended X = {125, 180, 255, 300, 450, 480};
   QVectorExtended Y = {210.52,
                        192.47,
                        172.51,
                        162.61,
                        125.91,
                        120.73};
   const double mockResidualsSum = 14.390762973888604;
   double residualsSum = DoubleExponential::computeResidualsSum(X, Y);
   QVERIFY2(qFuzzyCompare(residualsSum, mockResidualsSum), "Residuals sum calculation failed!");
}


static DoubleExponentialTest DETest;
