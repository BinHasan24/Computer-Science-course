#include <iostream>

class Fraction {
private:
    int numerator, denominator;

    int gcd(int a, int b) const {
        return b == 0 ? a : gcd(b, a % b);
    }

    void simplify() {
        int g = gcd(numerator, denominator);
        numerator /= g;
        denominator /= g;
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

public:
    // Constructors
    Fraction(int num = 0, int den = 1) : numerator(num), denominator(den) {
        if (den == 0) throw std::invalid_argument("Denominator cannot be zero.");
        simplify();
    }

    Fraction(const Fraction& other) = default; // Copy Constructor
    Fraction& operator=(const Fraction& other) = default; // Assignment Operator

    // Getters and Setters
    int getNumerator() const { return numerator; }
    int getDenominator() const { return denominator; }
    void setNumerator(int num) { numerator = num; simplify(); }
    void setDenominator(int den) {
        if (den == 0) throw std::invalid_argument("Denominator cannot be zero.");
        denominator = den; simplify();
    }

    // Conversion to double
    double toDouble() const {
        return static_cast<double>(numerator) / denominator;
    }

    // Arithmetic operators
    Fraction operator+(const Fraction& other) const {
        return Fraction(numerator * other.denominator + other.numerator * denominator, denominator * other.denominator);
    }

    Fraction operator-(const Fraction& other) const {
        return Fraction(numerator * other.denominator - other.numerator * denominator, denominator * other.denominator);
    }

    Fraction operator*(const Fraction& other) const {
        return Fraction(numerator * other.numerator, denominator * other.denominator);
    }

    Fraction operator/(const Fraction& other) const {
        if (other.numerator == 0) throw std::invalid_argument("Cannot divide by zero fraction.");
        return Fraction(numerator * other.denominator, denominator * other.numerator);
    }

    // Compound assignment operators
    Fraction& operator+=(const Fraction& other) {
        *this = *this + other;
        return *this;
    }

    Fraction& operator-=(const Fraction& other) {
        *this = *this - other;
        return *this;
    }

    Fraction& operator*=(const Fraction& other) {
        *this = *this * other;
        return *this;
    }

    Fraction& operator/=(const Fraction& other) {
        *this = *this / other;
        return *this;
    }

    // Overload << and >> operators
    friend std::ostream& operator<<(std::ostream& os, const Fraction& f) {
        os << f.numerator << (f.denominator != 1 ? "/" + std::to_string(f.denominator) : "");
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Fraction& f) {
        char slash;
        is >> f.numerator >> slash >> f.denominator;
        if (slash != '/' || f.denominator == 0) is.setstate(std::ios::failbit);
        else f.simplify();
        return is;
    }
};

int main() {
    Fraction a, b;
    std::cout << "Enter first fraction (N/D): ";
    std::cin >> a;
    std::cout << "Enter second fraction (N/D): ";
    std::cin >> b;

    std::cout << "a: " << a << ", b: " << b << "\n";
    std::cout << "a + b: " << a + b << "\n";
    std::cout << "a - b: " << a - b << "\n";
    std::cout << "a * b: " << a * b << "\n";
    std::cout << "a / b: " << a / b << "\n";

    a += b;
    std::cout << "a += b: " << a << "\n";
    a -= b;
    std::cout << "a -= b: " << a << "\n";
    a *= b;
    std::cout << "a *= b: " << a << "\n";
    a /= b;
    std::cout << "a /= b: " << a << "\n";

    std::cout << "a as double: " << a.toDouble() << "\n";
    std::cout << "b as double: " << b.toDouble() << "\n";

    return 0;
}
