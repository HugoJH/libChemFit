#include "DoubleExponentialTest.h"
#include "DoubleExponential.h"
#include <QtTest/QtTest>

DoubleExponentialTest::DoubleExponentialTest()
{

}

void DoubleExponentialTest::testComputeParameters()
{
   QVectorExtended X = {17, 33, 47, 60, 93, 120, 181, 240, 298, 420};
   QVectorExtended Y = {140.82, 110.01, 89.35, 76.89, 67.53, 51.57, 38.8, 28.88, 21.9, 12.7};
   QVectorExtended parameterMocks = {108.7353857611015, 0.03890904159800317, 91.61079628914057, 0.004747428794664105};
   QVectorExtended parameters = DoubleExponential::computeParameters(X, Y);
   QVERIFY2(qFuzzyCompare(parameters[0], parameterMocks[0]), "First parameter calculation failed!");
   QVERIFY2(qFuzzyCompare(parameters[1], parameterMocks[1]), "Second parameter calculation failed!");
   QVERIFY2(qFuzzyCompare(parameters[2], parameterMocks[2]), "Third parameter calculation failed!");
   QVERIFY2(qFuzzyCompare(parameters[3], parameterMocks[3]), "Fourth parameter calculation failed!");
}

void DoubleExponentialTest::testComputeDoubleExponential()
{
   QVectorExtended mockX = {17, 33, 47, 60, 93, 120, 181, 240, 298, 420};
   QVectorExtended mockY = {140.6260635110445,
                            108.4382119807584,
                            90.75460129565573,
                            79.4348144190113,
                            61.82809050720405,
                            52.84424546416403,
                            38.8889740749087,
                            29.32652546500952,
                            22.26153540252217,
                            12.47379383493526};
   QVectorExtended mockParameters = {108.7351890397201, 0.03890892572801488, 91.61073751661439, 0.004747426745796754};

   QVectorExtended EstY = DoubleExponential::computeExponential(mockX, mockParameters);

   for (int t = 0; t < EstY.size(); ++t)
   {
      QVERIFY2(qFuzzyCompare(EstY[t], mockY[t]), "Double exponential computation failed");
   }
}

void DoubleExponentialTest::testComputeExperimentalAreaUnderCurve()
{
   QVectorExtended X = {17, 33, 47, 60, 93, 120, 181, 240, 298, 420};
   QVectorExtended Y = {140.82, 110.01, 89.35, 76.89, 67.53, 51.57, 38.8, 28.88, 21.9, 12.7};
   const double mockEAUC = 22384.6098241395;
   double EAUC = DoubleExponential::computeExperimentalAreaUnderCurve(X, Y);
   QVERIFY2(qFuzzyCompare(EAUC, mockEAUC), "EAUC calculation failed!");
}

void DoubleExponentialTest::testComputeTheoreticalAreaUnderCurve()
{
   QVectorExtended X = {17, 33, 47, 60, 93, 120, 181, 240, 298, 420};
   QVectorExtended Y = {140.82, 110.01, 89.35, 76.89, 67.53, 51.57, 38.8, 28.88, 21.9, 12.7};
   const double mockTAUC = 22091.533557822877;
   double TAUC = DoubleExponential::computeTheoreticalAreaUnderCurve(X, Y);
   QVERIFY2(qFuzzyCompare(TAUC, mockTAUC), "TAUC calculation failed!");
}

void DoubleExponentialTest::testComputeAreaUnderCurvePartials()
{
   QVectorExtended X = {17, 33, 47, 60, 93, 120, 181, 240, 298, 420};
   QVectorExtended Y = {140.82, 110.01, 89.35, 76.89, 67.53, 51.57, 38.8, 28.88, 21.9, 12.7};
   QVectorExtended mockAUCPartials = {2899.912547427058,
                                      2006.64,
                                      1395.52,
                                      1080.56,
                                      2382.93,
                                      1607.85,
                                      2756.285,
                                      1996.56,
                                      1472.62,
                                      2110.6,
                                      2675.132276712443};

   QVectorExtended AUCPArtials = DoubleExponential::computeAreaUnderCurvePartials(X, Y);
   for(int i = 0; i < AUCPArtials.size(); ++i)
   {
      QVERIFY2(qFuzzyCompare(mockAUCPartials[i], AUCPArtials[i]), "AUC partials calculation failed!");
   }
}

void DoubleExponentialTest::testComputeExperimentalVolumeOfDistribution()
{
   QVectorExtended X = {17, 33, 47, 60, 93, 120, 181, 240, 298, 420};
   QVectorExtended Y = {140.82, 110.01, 89.35, 76.89, 67.53, 51.57, 38.8, 28.88, 21.9, 12.7};
   const double mockEVoD = 3310.3669385811736;
   double mockDose = 3.235e6;
   double EVoD = DoubleExponential::computeExperimentalVolumeOfDistribution(X, Y, mockDose);
   QVERIFY2(qFuzzyCompare(EVoD, mockEVoD), "EVoD calculation failed!");
}

void DoubleExponentialTest::testComputeTheoreticalVolumeOfDistribution()
{
   QVectorExtended X = {17, 33, 47, 60, 93, 120, 181, 240, 298, 420};
   QVectorExtended Y = {140.82, 110.01, 89.35, 76.89, 67.53, 51.57, 38.8, 28.88, 21.9, 12.7};
   const double mockTVoD = 3354.283762189547;
   double mockDose = 3.235e6;
   double TVoD = DoubleExponential::computeTheoreticalVolumeOfDistribution(X, Y, mockDose);
   QVERIFY2(qFuzzyCompare(TVoD, mockTVoD), "TVoD calculation failed!");
}

void DoubleExponentialTest::testComputeExperimentalClearance()
{
   QVectorExtended X = {17, 33, 47, 60, 93, 120, 181, 240, 298, 420};
   QVectorExtended Y = {140.82, 110.01, 89.35, 76.89, 67.53, 51.57, 38.8, 28.88, 21.9, 12.7};
   const double mockECL = 144.5189362430336;
   double mockDose = 3.235e6;
   double ECL = DoubleExponential::computeExperimentalClearance(X, Y, mockDose);
   QVERIFY2(qFuzzyCompare(ECL, mockECL), "ECL calculation failed!");
}

void DoubleExponentialTest::testComputeTheoreticalClearance()
{
   QVectorExtended X = {17, 33, 47, 60, 93, 120, 181, 240, 298, 420};
   QVectorExtended Y = {140.82, 110.01, 89.35, 76.89, 67.53, 51.57, 38.8, 28.88, 21.9, 12.7};
   const double mockTCL = 146.436189752632527;
   double mockDose = 3.235e6;
   double TCL = DoubleExponential::computeTheoreticalClearance(X, Y, mockDose);
   QVERIFY2(qFuzzyCompare(TCL, mockTCL), "TCL calculation failed!");
}

void DoubleExponentialTest::testComputeHalfLifeAlphaPhase()
{
   QVectorExtended X = {17, 33, 47, 60, 93, 120, 181, 240, 298, 420};
   QVectorExtended Y = {140.82, 110.01, 89.35, 76.89, 67.53, 51.57, 38.8, 28.88, 21.9, 12.7};
   const double mockHLAP = 17.814552918607944;
   double HLAP = DoubleExponential::computeHalfLifeAlphaPhase(X, Y);
   QVERIFY2(qFuzzyCompare(HLAP, mockHLAP), "Half Life Alpha Phase calculation failed!");
}

void DoubleExponentialTest::testComputeHalfLifeBetaPhase()
{
   QVectorExtended X = {17, 33, 47, 60, 93, 120, 181, 240, 298, 420};
   QVectorExtended Y = {140.82, 110.01, 89.35, 76.89, 67.53, 51.57, 38.8, 28.88, 21.9, 12.7};
   const double mockHLBP = 146.00475552977463;
   double HLBP = DoubleExponential::computeHalfLifeBetaPhase(X, Y);
   QVERIFY2(qFuzzyCompare(HLBP, mockHLBP), "Half Life Beta Phase calculation failed!");
}

void DoubleExponentialTest::testComputeResidualsSum()
{
   QVectorExtended X = {17, 33, 47, 60, 93, 120, 181, 240, 298, 420};
   QVectorExtended Y = {140.82, 110.01, 89.35, 76.89, 67.53, 51.57, 38.8, 28.88, 21.9, 12.7};
   const double mockResidualsSum = 3.913766636134053;
   double residualsSum = DoubleExponential::computeResidualsSum(X, Y);
   QVERIFY2(qFuzzyCompare(residualsSum, mockResidualsSum), "Residuals sum calculation failed!");
}

void DoubleExponentialTest::testComputeMRT()
{
   QVectorExtended X = {17, 33, 47, 60, 93, 120, 181, 240, 298, 420};
   QVectorExtended Y = {140.82, 110.01, 89.35, 76.89, 67.53, 51.57, 38.8, 28.88, 21.9, 12.7};
   const double mockMRT = 217.32328798142538;
   double MRT = DoubleExponential::computeMRT(X, Y);
   QVERIFY2(qFuzzyCompare(MRT, mockMRT), "MRT calculation failed!");
}


static DoubleExponentialTest DETest;
