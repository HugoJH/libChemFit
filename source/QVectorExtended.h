#ifndef QVECTOREXTENDED_H
#define QVECTOREXTENDED_H

#include <QVector>
#include <QVariantList>

class QVectorExtended : public QVector<double>
{
   public:
      using QVector::QVector;
      QVectorExtended();
      QVectorExtended(const QVector<double>& vect);

      QVectorExtended operator+(const QVectorExtended & X) const;

      QVectorExtended operator-(const QVectorExtended & X) const;

      QVectorExtended operator-(double d) const;

      QVectorExtended operator+( double n) const;

      QVectorExtended operator*(const QVectorExtended & X) const;

      QVectorExtended operator*(double d) const;
      QVectorExtended operator/(double n) const;

      QVariantList toQVariantList() const;
};


#endif // QVECTOREXTENDED_H
