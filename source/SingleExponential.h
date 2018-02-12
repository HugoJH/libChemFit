#ifndef SINGLEEXPONENTIAL_H
#define SINGLEEXPONENTIAL_H

#include <QVector>

class SingleExponential
{
   public:
      SingleExponential();

      static double computeFirstPreParameter(const QVector<double> & X, const QVector<double> & Y);
};

#endif // SINGLEEXPONENTIAL_H
