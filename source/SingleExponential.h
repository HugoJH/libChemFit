#ifndef SINGLEEXPONENTIAL_H
#define SINGLEEXPONENTIAL_H

#include <QVector>

class SingleExponential
{
   public:
      SingleExponential();

      static double computeFirstPreParameter(const QVector<double> & X, const QVector<double> & Y);
      static double computeSecondPreParameter(const QVector<double> & X, const QVector<double> & Y);

};

QVector<double> operator+(const QVector<double> & X, const QVector<double> & Y)
{
   QVector<double> temp;

   for (int i = 0; i < X.count(); ++i)
   {
        temp << Y[i] + X[i];
   }
   return temp;
}

QVector<double> operator+(const QVector<double> & X, double n)
{
   QVector<double> temp;

   for (int i = 0; i < X.count(); ++i)
   {
        temp << X[i] + n;
   }
   return temp;
}

QVector<double> operator+(double n, const QVector<double> & X)
{
   return operator +(X, n);
}

QVector<double> operator*(const QVector<double> & X, const QVector<double> & Y)
{
   QVector<double> temp;

   for (int i = 0; i < X.count(); ++i)
   {
        temp << X[i] * Y[i];
   }
   return temp;
}

#endif // SINGLEEXPONENTIAL_H
