// --------------------------
// Diseño de Algoritmos
// Manuel Montenegro Montes
// --------------------------

// Implementación de algoritmo de Karatsuba para multiplicar enteros grandes.

#include <cassert>
#include <iostream>
#include <vector>

// Descomentar la siguiente línea para utilizar el algoritmo DyV de coste
// cuadrático en lugar del algoritmo de Karatsuba

// #define CUADRATICA

using namespace std;

// Número de dígitos por debajo del cual se utilizará la multiplicación del tipo
// `int`
constexpr int UMBRAL = 4;

class BigInteger {
public:
  // Construye el número 0
  BigInteger() {}

  // Construye un BigInteger a partir de un valor n
  BigInteger(int n);

  // Construye un BigInteger a partir de una cadena de texto
  BigInteger(const string &str) {
    for (auto it = str.rbegin(); it != str.rend(); it++) {
      digits.push_back(*it - '0');
    }
  }

  // Devuelve el número de dígitos de un BigInteger
  int num_digits() const { return digits.size(); }

  // Operación de suma entre dos BigIntegers
  BigInteger operator+(const BigInteger &other) const;
  // Operación de resta entre dos BigIntegers
  BigInteger operator-(const BigInteger &other) const;
  // Dado un `m` devuelve un par (this div 10^m, this mod 10^m)
  pair<BigInteger, BigInteger> divRem10(int m) const;
  // Dado un `m` devuelve this * 10^m
  BigInteger mult10(int m) const;

  // Multiplica dos números
  BigInteger operator*(const BigInteger &other) const;

  // Convierte un BigInteger a `int`
  operator int() const;

  // Operación para mostrar BigInteger por pantalla
  friend ostream &operator<<(ostream &out, const BigInteger &bi);

private:
  vector<int> digits;
};

BigInteger::BigInteger(int n) {
  while (n > 0) {
    digits.push_back(n % 10);
    n /= 10;
  }
}

BigInteger BigInteger::operator+(const BigInteger &other) const {
  int carry = 0;
  int i = 0;

  BigInteger result;

  // Vamos recorriendo los dígitos de ambos números en paralelo
  while (i < num_digits() || i < other.num_digits() || carry == 1) {
    int digit1 = i >= num_digits() ? 0 : digits[i];
    int digit2 = i >= other.num_digits() ? 0 : other.digits[i];

    int digit = digit1 + digit2 + carry;
    if (digit >= 10) {
      digit -= 10;
      carry = 1;
    } else {
      carry = 0;
    }

    result.digits.push_back(digit);
    i++;
  }
  return result;
}

BigInteger BigInteger::operator-(const BigInteger &other) const {
  int carry = 0;
  int i = 0;
  BigInteger result;

  // Vamos recorriendo los dígitos de ambos números en paralelo
  while (i < num_digits() && i < other.num_digits()) {
    int digit = digits[i] - other.digits[i] - carry;
    if (digit < 0) {
      digit += 10;
      carry = 1;
    } else {
      carry = 0;
    }
    result.digits.push_back(digit);
    i++;
  }

  // Si quedan dígitos en this, vamos restándoles el acarreo
  // hasta que no se produzca más acarreo.
  while (i < num_digits()) {
    int digit = digits[i] - carry;
    if (digit < 0) {
      digit += 10;
      carry = 1;
    } else {
      carry = 0;
    }
    result.digits.push_back(digit);
    i++;
  }

  // Eliminamos los ceros que se hayan quedado al final del vector..
  // (Son 0's por la izquierda)
  while (!result.digits.empty() && result.digits.back() == 0) {
    result.digits.pop_back();
  }

  return result;
}

pair<BigInteger, BigInteger> BigInteger::divRem10(int m) const {
  BigInteger rem, div;
  int i = 0;
  while (i < num_digits() && i < m) {
    rem.digits.push_back(digits[i]);
    i++;
  }

  // El resto puede tener 0's por la izquierda. Se eliminan.
  while (!rem.digits.empty() && rem.digits.back() == 0) {
    rem.digits.pop_back();
  }

  div.digits = {digits.begin() + i, digits.end()};
  return {div, rem};
}

BigInteger BigInteger::mult10(int m) const {
  if (digits.empty())
    return 0;
  BigInteger result;
  for (int i = 0; i < m; i++) {
    result.digits.push_back(0);
  }
  for (auto x : digits) {
    result.digits.push_back(x);
  }
  return result;
}

#ifdef CUADRATICA
BigInteger BigInteger::operator*(const BigInteger &other) const {
  if (num_digits() == 0 || other.num_digits() == 0) {
    return 0;
  }

  int n = max(num_digits(), other.num_digits());
  if (n <= UMBRAL) {
    return BigInteger((int)(*this) * (int)other);
  } else {
    int m = n / 2;
    auto [x1, x2] = this->divRem10(m);
    auto [y1, y2] = other.divRem10(m);

    BigInteger x1y1 = x1 * y1;
    BigInteger x1y2 = x1 * y2;
    BigInteger x2y1 = x2 * y1;
    BigInteger x2y2 = x2 * y2;

    BigInteger result = x1y1.mult10(2 * m) + (x1y2 + x2y1).mult10(m) + x2y2;
    return result;
  }
}

#else

BigInteger BigInteger::operator*(const BigInteger &other) const {
  if (num_digits() == 0 || other.num_digits() == 0) {
    return {};
  }

  int n = max(num_digits(), other.num_digits());
  if (n <= UMBRAL) {
    return BigInteger((int)*this * (int)other);
  } else {
    int m = n / 2;
    auto [x1, x2] = this->divRem10(m);
    auto [y1, y2] = other.divRem10(m);

    BigInteger x1y1 = x1 * y1;
    BigInteger x2y2 = x2 * y2;
    BigInteger r = (x1 + x2) * (y1 + y2);

    return x1y1.mult10(2 * m) + (r - x1y1 - x2y2).mult10(m) + x2y2;
  }
}

#endif

BigInteger::operator int() const {
  int result = 0;
  int pot = 1;
  for (int x : digits) {
    result += pot * x;
    pot *= 10;
  }
  return result;
}

ostream &operator<<(ostream &out, const BigInteger &bi) {
  if (bi.digits.empty()) {
    out << '0';
    return out;
  }
  for (auto it = bi.digits.rbegin(); it != bi.digits.rend(); it++) {
    out << *it;
  }
  return out;
}

int main() {
  BigInteger b1 = string("2318907138912");
  for (int i = 0; i < 9; i++) {
    b1 = b1 * b1;
  }
  cout << b1.num_digits() << "\n";
}
