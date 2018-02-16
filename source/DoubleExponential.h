#ifndef DOUBLEEXPONENTIAL_H
#define DOUBLEEXPONENTIAL_H

#include <QVector>

class DoubleExponential
{
   public:
      DoubleExponential();
      static QVector<double> computePreParameters(const QVector<double>& X,
                                                  const QVector<double>& Y);
      static double computeFirstPreParameter(const QVector<double>& X,
                                                      const QVector<double>& Y);
};

#endif // DOUBLEEXPONENTIAL_H
