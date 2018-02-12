#include <QString>
#include <QtTest>

#include "SingleExponential.h"


class SingleExponentialTest : public QObject
{
      Q_OBJECT

   public:
      SingleExponentialTest();
   private Q_SLOTS:
      void testcomputeFirstPreParameter();
      void testcomputeSecondPreParameter();
};

SingleExponentialTest::SingleExponentialTest()
{

}

void SingleExponentialTest::testcomputeFirstPreParameter()
{
   const double mock = -0.20228711901914495;
   QVector<double> X= {1, 2, 3, 4, 5};
   QVector<double> Y= {1, 3, 5, 7, 9};
   double P1 = SingleExponential::computeFirstPreParameter(X, Y);
   qDebug() << "Computation of single exponential first pre-parameter";
   QVERIFY2(qFuzzyCompare(P1, mock), "Parameter calculation failed");
}

void SingleExponentialTest::testcomputeSecondPreParameter()
{
   const double mock = -0.20228711901914495;
   QVector<double> X= {1, 2, 3, 4, 5};
   QVector<double> Y= {1, 3, 5, 7, 9};
   double P1 = SingleExponential::computeSecondPreParameter(X, Y);
   qDebug() << "Computation of single exponential second pre-parameter";
   QVERIFY2(qFuzzyCompare(P1, mock), "Pre-Parameter calculation failed");
}



QTEST_APPLESS_MAIN(SingleExponentialTest)

#include "tst_singleexponentialtest.moc"
