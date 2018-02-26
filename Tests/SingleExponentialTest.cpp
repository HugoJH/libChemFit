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
   QVector<double> X = {125, 180, 255, 300, 450, 480};
   QVector<double> Y = {210.52,
                        192.47,
                        172.51,
                        162.61,
                        125.91,
                        120.73};
   QVector<double> mockY = {210.7761853607157,
                            193.4451581468218,
                            172.0852946676328,
                            160.4188125663006,
                            126.9483583244129,
                            121.1438711325513};
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
   const double mockEAUC = 9.206594219667835;
   double EAUC = SingleExponential::computeExperimentalAreaUnderCurve(X,Y);
   QVERIFY2(qFuzzyCompare(EAUC, mockEAUC), "EAUC calculation failed!");
}

void SingleExponentialTest::testComputeTheoreticalAreaUnderCurve()
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
   double TAUC = SingleExponential::computeTheoreticalAreaUnderCurve(X,Y);
   QVERIFY2(qFuzzyCompare(TAUC, mockTAUC), "TAUC calculation failed!");
}

void SingleExponentialTest::testComputeAreaUnderCurvePartials()
{
   QVectorExtended X = {125, 180, 255, 300, 450, 480};
   QVectorExtended Y = {210.52,
                        192.47,
                        172.51,
                        162.61,
                        125.91,
                        120.73};
   QVectorExtended mockAUCPartials = {29167.5147228347,
                                      11082.225,
                                      13686.75,
                                      7540.200000000001,
                                      21639,
                                      3699.6,
                                      77388.51299982953};


   QVectorExtended AUCPArtials = SingleExponential::computeAreaUnderCurvePartials(X, Y);
   for(int i = 0; i < AUCPArtials.size(); ++i)
   {
      QVERIFY2(qFuzzyCompare(mockAUCPartials[i], AUCPArtials[i]), "AUC partials calculation failed!");
   }
}

void SingleExponentialTest::testComputeExperimentalVolumeOfDistribution()
{
   QVectorExtended X = {125, 180, 255, 300, 450, 480};
   QVectorExtended Y = {210.52,
                        192.47,
                        172.51,
                        162.61,
                        125.91,
                        120.73};
   const double mockEVoD = 12628.51765482094;
   double mockDose = 3.235e6;
   double EVoD = SingleExponential::computeExperimentalVolumeOfDistribution(X, Y, mockDose);
   QVERIFY2(qFuzzyCompare(EVoD, mockEVoD), "EVoD calculation failed!");
}

void SingleExponentialTest::testComputeTheoreticalVolumeOfDistribution()
{
   QVectorExtended X = {125, 180, 255, 300, 450, 480};
   QVectorExtended Y = {210.52,
                        192.47,
                        172.51,
                        162.61,
                        125.91,
                        120.73};
   const double mockTVoD = 12628.81412042831;
   double mockDose = 3.235e6;
   double TVoD = SingleExponential::computeTheoreticalVolumeOfDistribution(X, Y, mockDose);
   QVERIFY2(qFuzzyCompare(TVoD, mockTVoD), "TVoD calculation failed!");
}

void SingleExponentialTest::testComputeExperimentalClearance()
{
   QVectorExtended X = {125, 180, 255, 300, 450, 480};
   QVectorExtended Y = {210.52,
                        192.47,
                        172.51,
                        162.61,
                        125.91,
                        120.73};
   const double mockECL = 19.701127174647876;
   double mockDose = 3.235e6;
   double ECL = SingleExponential::computeExperimentalClearance(X, Y, mockDose);
   QVERIFY2(qFuzzyCompare(ECL, mockECL), "ECL calculation failed!");
}

void SingleExponentialTest::testComputeTheoreticalClearance()
{
   QVectorExtended X = {125, 180, 255, 300, 450, 480};
   QVectorExtended Y = {210.52,
                        192.47,
                        172.51,
                        162.61,
                        125.91,
                        120.73};
   const double mockTCL = 19.701589676011327;
   double mockDose = 3.235e6;
   double TCL = SingleExponential::computeTheoreticalClearance(X, Y, mockDose);
   QVERIFY2(qFuzzyCompare(TCL, mockTCL), "TCL calculation failed!");
}

void SingleExponentialTest::testComputeHalfLife()
{
   QVectorExtended X = {125, 180, 255, 300, 450, 480};
   QVectorExtended Y = {210.52,
                        192.47,
                        172.51,
                        162.61,
                        125.91,
                        120.73};
   const double mockHL = 444.31068991599864;
   double mockDose = 3.235e6;
   double HL = SingleExponential::computeHalfLife(X, Y, mockDose);
   QVERIFY2(qFuzzyCompare(HL, mockHL), "HL calculation failed!");
}

void SingleExponentialTest::testComputeResidualsSum()
{
   QVectorExtended X = {125, 180, 255, 300, 450, 480};
   QVectorExtended Y = {210.52,
                        192.47,
                        172.51,
                        162.61,
                        125.91,
                        120.73};
   const double mockResidualsSum = 3.9981614450915957;
   double residualsSum = SingleExponential::computeResidualsSum(X, Y);
   QVERIFY2(qFuzzyCompare(residualsSum, mockResidualsSum), "Residuals sum calculation failed!");
}

static SingleExponentialTest SETest;
