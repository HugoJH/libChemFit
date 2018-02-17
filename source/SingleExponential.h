#ifndef SINGLEEXPONENTIAL_H
#define SINGLEEXPONENTIAL_H

#include <QVector>
#include <QVariantList>

class SingleExponential
{
   public:
      SingleExponential();

      static double computeFirstPreParameter(const QVector<double> & X, const QVector<double> & Y);
      static double computeSecondPreParameter(const QVector<double> & X, const QVector<double> & Y);
      static std::pair<double,double> computeParameters(const QVector<double>& X, const QVector<double>& Y, double pre1, double pre2);
   private:
      static QVariantList prepareDataVector(const QVector<double>& X);

};

#endif // SINGLEEXPONENTIAL_H

