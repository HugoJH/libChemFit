#include "SingleExponentialTest.h"

#include <QString>
#include <QtTest/QtTest>

#include "SingleExponential.h"

SingleExponentialTest::SingleExponentialTest()
{

}

void SingleExponentialTest::testComputeParameters()
{
   const double mockP1 = 256.9204958141705;
   const double mockP2 = 0.0015712664939343268;
   QVector<double> X = {125, 180, 255, 300, 450, 480};
   QVector<double> Y = {210.52, 192.47, 172.51, 162.61, 125.91, 120.73};
   QPair<double, double> parameters = SingleExponential::computeParameters(X, Y);
   QVERIFY2(qFuzzyCompare(parameters.first, mockP1), "First Parameter calculation failed!");
   QVERIFY2(qFuzzyCompare(parameters.second, mockP2), "Second Parameter calculation failed!");
}

void SingleExponentialTest::testComputeSingleExponential()
{
   QVector<double> X = {125, 180, 255, 300, 450, 480};
   QVector<double> Y = {210.52, 192.47, 172.51, 162.61, 125.91, 120.73};
   QVector<double> mockY = {211.1055764132313,
                            193.6279846713009,
                            172.1031017958427,
                            160.3544590598879,
                            126.6841220170798,
                            120.8510463224405};
   QPair<double, double> parameters = SingleExponential::computeParameters(X, Y);
   const double mockP1 = parameters.first;
   const double mockP2 = parameters.second;
   QVectorExtended EstY = SingleExponential::computeExponential(X, mockP1, mockP2);
   for (int t = 0; t < EstY.size(); ++t)
   {
      QVERIFY2(qFuzzyCompare(EstY[t], mockY[t]), "Single exponential computation failed");
   }
}

void SingleExponentialTest::testComputeExperimentalAreaUnderCurve()
{
   QVector<double> X = {125, 180, 255, 300, 450, 480};
   QVector<double> Y = {210.52, 192.47, 172.51, 162.61, 125.91, 120.73};
   const double mockEAUC = 163698.91269979504;
   double EAUC = SingleExponential::computeExperimentalAreaUnderCurve(X,Y);
   QVERIFY2(qFuzzyCompare(EAUC, mockEAUC), "EAUC calculation failed!");
}

void SingleExponentialTest::testComputeTheoreticalAreaUnderCurve()
{
   QVector<double> X = {125, 180, 255, 300, 450, 480};
   QVector<double> Y = {210.52, 192.47, 172.51, 162.61, 125.91, 120.73};
   const double mockTAUC = 163511.72560859614;
   double TAUC = SingleExponential::computeTheoreticalAreaUnderCurve(X,Y);
   QVERIFY2(qFuzzyCompare(TAUC, mockTAUC), "TAUC calculation failed!");
}

void SingleExponentialTest::testComputeAreaUnderCurvePartials()
{
   QVector<double> X = {125, 180, 255, 300, 450, 480};
   QVector<double> Y = {210.52, 192.47, 172.51, 162.61, 125.91, 120.73};
   QVectorExtended mockAUCPartials = {29215.03098838566,
                                      11082.225,
                                      13686.75,
                                      7540.200000000001,
                                      21639,
                                      3699.6,
                                      76836.10671140937};

   QVectorExtended AUCPArtials = SingleExponential::computeAreaUnderCurvePartials(X, Y);
   for(int i = 0; i < AUCPArtials.size(); ++i)
   {
      QVERIFY2(qFuzzyCompare(mockAUCPartials[i], AUCPArtials[i]), "AUC partials calculation failed!");
   }
}

void SingleExponentialTest::testComputeExperimentalVolumeOfDistribution()
{
   QVector<double> X = {125, 180, 255, 300, 450, 480};
   QVector<double> Y = {210.52, 192.47, 172.51, 162.61, 125.91, 120.73};
   const double mockEVoD = 12577.045746960894;
   double mockDose = 3.235e6;
   double EVoD = SingleExponential::computeExperimentalVolumeOfDistribution(X, Y, mockDose);
   QVERIFY2(qFuzzyCompare(EVoD, mockEVoD), "EVoD calculation failed!");
}

void SingleExponentialTest::testComputeTheoreticalVolumeOfDistribution()
{
   QVector<double> X = {125, 180, 255, 300, 450, 480};
   QVector<double> Y = {210.52, 192.47, 172.51, 162.61, 125.91, 120.73};
   const double mockTVoD = 12591.443861839118;
   double mockDose = 3.235e6;
   double TVoD = SingleExponential::computeTheoreticalVolumeOfDistribution(X, Y, mockDose);
   QVERIFY2(qFuzzyCompare(TVoD, mockTVoD), "TVoD calculation failed!");
}

void SingleExponentialTest::testComputeExperimentalClearance()
{
   QVector<double> X = {125, 180, 255, 300, 450, 480};
   QVector<double> Y = {210.52, 192.47, 172.51, 162.61, 125.91, 120.73};
   const double mockECL = 19.76189057487888;
   double mockDose = 3.235e6;
   double ECL = SingleExponential::computeExperimentalClearance(X, Y, mockDose);
   QVERIFY2(qFuzzyCompare(ECL, mockECL), "ECL calculation failed!");
}

void SingleExponentialTest::testComputeTheoreticalClearance()
{
   QVector<double> X = {125, 180, 255, 300, 450, 480};
   QVector<double> Y = {210.52, 192.47, 172.51, 162.61, 125.91, 120.73};
   const double mockTCL = 19.78451385036285;
   double mockDose = 3.235e6;
   double TCL = SingleExponential::computeTheoreticalClearance(X, Y, mockDose);
   QVERIFY2(qFuzzyCompare(TCL, mockTCL), "TCL calculation failed!");
}

void SingleExponentialTest::testComputeHalfLife()
{
   QVector<double> X = {125, 180, 255, 300, 450, 480};
   QVector<double> Y = {210.52, 192.47, 172.51, 162.61, 125.91, 120.73};
   const double mockHL = 441.1391595478878;
   double mockDose = 3.235e6;
   double HL = SingleExponential::computeHalfLife(X, Y, mockDose);
   QVERIFY2(qFuzzyCompare(HL, mockHL), "HL calculation failed!");
}

void SingleExponentialTest::testComputeResidualsSum()
{
   QVector<double> X = {125, 180, 255, 300, 450, 480};
   QVector<double> Y = {210.52, 192.47, 172.51, 162.61, 125.91, 120.73};
   const double mockResidualsSum = 3.9062581265964833;
   double residualsSum = SingleExponential::computeResidualsSum(X, Y);
   QVERIFY2(qFuzzyCompare(residualsSum, mockResidualsSum), "Residuals sum calculation failed!");
}

void SingleExponentialTest::testComputeMRT()
{
   QVector<double> X = {125, 180, 255, 300, 450, 480};
   QVector<double> Y = {210.52, 192.47, 172.51, 162.61, 125.91, 120.73};
   const double mockMRT = 3.9062581265964833;
   double MRT = SingleExponential::computeMRT(X, Y);
   QVERIFY2(qFuzzyCompare(MRT, mockMRT), "MRT calculation failed!");
}

static SingleExponentialTest SETest;
