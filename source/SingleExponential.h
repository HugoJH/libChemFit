#ifndef SINGLEEXPONENTIAL_H
#define SINGLEEXPONENTIAL_H

#include <QVector>
#include <QVariantList>
#include <QPair>

class SingleExponential
{
   public:
      SingleExponential();
      static double computeFirstPreParameter(const QVector<double> & X, const QVector<double> & Y);
      static double computeSecondPreParameter(const QVector<double> & X, const QVector<double> & Y);
      static QPair<double, double> computeParameters(const QVector<double>& X, const QVector<double>& Y, double pre1, double pre2);
      static QVector<double> computeExponential(const QVector<double>& X, double P1, double P2);
   private:
      static QVariantList prepareDataVector(const QVector<double>& X);

};

#endif // SINGLEEXPONENTIAL_H

