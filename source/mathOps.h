#ifndef MATHOPS_H
#define MATHOPS_H

#include "QVectorExtended.h"

class mathOps
{
   public:

      static QVectorExtended vLn(const QVectorExtended& X);
      static QVectorExtended vPow(const QVectorExtended& X, double power);
      static QVectorExtended vAbs(const QVectorExtended& X);
      static QVectorExtended vAdd(const QVectorExtended& X, const QVectorExtended& Y);
      static double mean(const QVectorExtended& X);
      static double stdDev(const QVectorExtended& X);
      static double sum(const QVectorExtended& X);
      static double stdResidualsSum(const QVectorExtended &sumOfComponents,
                                    const QVectorExtended &Y);
      static double var(const QVectorExtended& X);
};


#endif // MATHOPS_H
