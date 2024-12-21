#include <iostream>
#include <vector>

class Vector {
private:
    std::vector<double> elements; // Vector elements

public:
    // Constructor with size
    Vector(int size) : elements(size) {}

    // Input operator (>>): Reads elements into the vector
    friend std::istream& operator>>(std::istream& is, Vector& v) {
        std::cout << "Enter " << v.elements.size() << " elements:\n";
        for (double& elem : v.elements) {
            is >> elem;
        }
        return is;
    }

    // Output operator (<<): Prints vector elements
    friend std::ostream& operator<<(std::ostream& os, const Vector& v) {
        for (double elem : v.elements) {
            os << elem << " ";
        }
        return os;
    }

    // Add two vectors (sizes must match)
    Vector add(const Vector& other) const {
        if (elements.size() != other.elements.size()) {
            std::cerr << "Error: Vectors must be the same size for addition.\n";
            return *this;
        }
        Vector result(elements.size());
        for (size_t i = 0; i < elements.size(); i++) {
            result.elements[i] = elements[i] + other.elements[i];
        }
        return result;
    }

    // Subtract two vectors (sizes must match)
    Vector subtract(const Vector& other) const {
        if (elements.size() != other.elements.size()) {
            std::cerr << "Error: Vectors must be the same size for subtraction.\n";
            return *this;
        }
        Vector result(elements.size());
        for (size_t i = 0; i < elements.size(); i++) {
            result.elements[i] = elements[i] - other.elements[i];
        }
        return result;
    }

    // Scalar product (dot product)
    double dotProduct(const Vector& other) const {
        if (elements.size() != other.elements.size()) {
            std::cerr << "Error: Vectors must be the same size for dot product.\n";
            return 0.0;
        }
        double result = 0;
        for (size_t i = 0; i < elements.size(); i++) {
            result += elements[i] * other.elements[i];
        }
        return result;
    }

    // Multiply vector by a scalar
    Vector multiplyByScalar(double scalar) const {
        Vector result(elements.size());
        for (size_t i = 0; i < elements.size(); i++) {
            result.elements[i] = elements[i] * scalar;
        }
        return result;
    }
};

int main() {
    int size1, size2;

    // Input size of Vector 1
    std::cout << "Enter the size of Vector 1:\n";
    std::cin >> size1;
    Vector v1(size1);
    std::cin >> v1;

    // Input size of Vector 2
    std::cout << "Enter the size of Vector 2:\n";
    std::cin >> size2;
    Vector v2(size2);
    std::cin >> v2;

    // Check sizes and perform operations
    if (size1 == size2) {
        Vector sum = v1.add(v2);           // Add vectors
        Vector diff = v1.subtract(v2);     // Subtract vectors
        double dot = v1.dotProduct(v2);    // Dot product
        Vector scaled = v1.multiplyByScalar(2.0); // Multiply by scalar

        // Display results
        std::cout << "Vector 1 + Vector 2: " << sum << "\n";
        std::cout << "Vector 1 - Vector 2: " << diff << "\n";
        std::cout << "Scalar Product: " << dot << "\n";
        std::cout << "Vector 1 * 2: " << scaled << "\n";
    } else {
        std::cout << "Error: Vector sizes must match for addition, subtraction, and dot product.\n";
    }

    return 0;
}
