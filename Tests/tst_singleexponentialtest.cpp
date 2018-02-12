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
};

SingleExponentialTest::SingleExponentialTest()
{

}

void SingleExponentialTest::testcomputeFirstPreParameter()
{
   QVector<double> X= {1, 2, 3, 4, 5};
   QVector<double> Y= {1, 3, 5, 7, 9};
   double P1 = SingleExponential::computeFirstPreParameter(X, Y);
   qDebug() << "Computation of single exponential first pre-parameter";
   QCOMPARE(P1, 5.3);
}

QTEST_APPLESS_MAIN(SingleExponentialTest)

#include "tst_singleexponentialtest.moc"
