#ifndef QVECTOREXTENDED_H
#define QVECTOREXTENDED_H

#include <QVector>

class QVectorExtended : public QVector<double>
{
   public:
      using QVector::QVector;
      QVectorExtended();
      QVectorExtended(const QVector<double>& vect);

      QVectorExtended operator+(const QVectorExtended & X) const;

      QVectorExtended operator-(const QVectorExtended & X) const;

      QVectorExtended operator+( double n) const;

      QVectorExtended operator*(const QVectorExtended & X) const;

      QVectorExtended operator/(double n) const;
};


#endif // QVECTOREXTENDED_H
