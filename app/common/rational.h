//Copyright 2015 Adam Quintero
//This program is distributed under the terms of the GNU General Public License.

// Adapted by MattKC for the Olive Video Editor (2019)

#ifndef RATIONAL_H
#define RATIONAL_H
#include <iostream>

#include <QMetaType>

extern "C" {
#include <libavformat/avformat.h>
}

using namespace std;

typedef int64_t intType;
/*
 * Zero Handling
 * 0/0        = 0
 * 0/non-zero = 0
 * non-zero/0 = 0
*/
class rational
{
public:
  //constructors
  rational(const intType &numerator = 0)
    :numer(numerator), denom(1)
  {
    activeInstances++;
    if(numer == 0)
      denom = 0;
  }

  rational(const intType &numerator, const intType &denominator)
    :numer(numerator), denom(denominator)
  {
    activeInstances++;
    if(denom != intType(0))
      {
        if(numer != intType(0))
          {
            fixSigns();
            reduce();
          }
        else
          denom = intType(0);
      }
    else
      numer = intType(0);
  }

  rational(const rational &rhs)
    :numer(rhs.numer), denom(rhs.denom)
  {
    activeInstances++;
  }

  rational(const AVRational& r);

  //destructor
  ~rational();

  //Assignment Operators
  const rational& operator=(const rational &rhs);
  const rational& operator+=(const rational &rhs);
  const rational& operator-=(const rational &rhs);
  const rational& operator/=(const rational &rhs);
  const rational& operator*=(const rational &rhs);

  //Binary math operators
  rational operator+(const rational &rhs) const;
  rational operator-(const rational &rhs) const;
  rational operator/(const rational &rhs) const;
  rational operator*(const rational &rhs) const;

  //Relational and equality operators
  bool operator<(const rational &rhs) const;
  bool operator<=(const rational &rhs) const;
  bool operator>(const rational &rhs) const;
  bool operator>=(const rational &rhs) const;
  bool operator==(const rational &rhs) const;
  bool operator!=(const rational &rhs) const;

  //Unary operators
  const rational& operator++(); //prefix
  rational operator++(int);     //postfix
  const rational& operator--(); //prefix
  rational operator--(int);     //postfix
  const rational& operator+() const;
  rational operator-() const;
  bool operator!() const;

  //Function: convert to double
  double toDouble() const;

  // Produce "flipped" version
  rational flipped() const;

  // Returns whether the rational is null or not
  bool isNull() const;

  //Function: print number to cout
  void print(ostream &out = cout) const;

  //Function: get active instances
  int getActiveInstances();

  //IO
  friend ostream& operator<<(ostream &out, const rational &value);
  friend istream& operator>>(istream &in, rational &value);

  const intType& numerator() const;
  const intType& denominator() const;

private:
  //number of active instances
  static int activeInstances;

  //numerator and denominator
  intType numer;
  intType denom;

  //Function: ensures denom >= 0
  void fixSigns();
  //Function: ensures lowest form
  void reduce();
  //Function: finds greatest common denominator
  intType gcd(intType &x, intType &y);
};

#define RATIONAL_MIN rational(INT32_MIN, 1)
#define RATIONAL_MAX rational(INT32_MAX, 1)

Q_DECLARE_METATYPE(rational)

#endif // RATIONAL_H
