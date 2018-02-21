#include "QVectorExtended.h"

QVectorExtended::QVectorExtended()
{

}

QVectorExtended::QVectorExtended(const QVector<double>& vect):
   QVector<double>(vect)
{

}

QVectorExtended QVectorExtended::operator+(const QVectorExtended& X)  const
{
   QVectorExtended result;

   for (int i = 0; i < X.count(); ++i)
   {
      result << (*this)[i] + X[i];
   }

   return result;
}

QVectorExtended QVectorExtended::operator+(double n)  const
{
   QVectorExtended result;

   for (int i = 0; i < this->count(); ++i)
   {
      result << (*this)[i] + n;
   }

   return result;
}

QVectorExtended QVectorExtended::operator-(const QVectorExtended& X) const
{
   QVectorExtended result;

   for (int i = 0; i < this->count(); ++i)
   {
      result << (*this)[i] - X[i];
   }

   return result;
}

QVectorExtended QVectorExtended::operator*(const QVectorExtended& X) const
{
   QVectorExtended result;

   for (int i = 0; i < X.count(); ++i)
   {
      result << (*this)[i] * X[i] ;
   }
   return result;
}


QVectorExtended QVectorExtended::operator/(double n) const
{
   QVectorExtended result;

   for (int i = 0; i < this->count(); ++i)
   {
      result << (*this)[i] / n;
   }
   return result;
}



