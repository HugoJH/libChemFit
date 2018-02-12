#include <QString>
#include <QtTest>

class SingleExponentialTest : public QObject
{
      Q_OBJECT

   public:
      SingleExponentialTest();
   private Q_SLOTS:
      void testgetFirstPreParameter();
};

SingleExponentialTest::SingleExponentialTest()
{

}

void SingleExponentialTest::testgetFirstPreParameter()
{
   QVector<double> X= {1,2,3,4,5};
   QVector<double> Y= {1,3,5,7,9};
   double P1 = getFirstParameter(X,Y);
   QVERIFY2(P1 == 5.3, "Computation of single exponential first pre-parameter failed");
}

QTEST_APPLESS_MAIN(SingleExponentialTest)

#include "tst_singleexponentialtest.moc"
