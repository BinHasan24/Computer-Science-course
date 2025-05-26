#include <iostream> // For basic input/output - std::cout
#include <memory>   // For smart pointers  - std::unique_ptr

// ---------- Matrix class template with fixed size N x M

template <size_t N, size_t M>
class Matrix {
private:
    std::unique_ptr<double[]> data;

public:
    // Default constructor
    Matrix() {
        data = std::make_unique<double[]>(N * M);
        for (size_t i = 0; i < N * M; ++i)
            data[i] = 0;
    }

    // Copy constructor
    Matrix(const Matrix& other) {
        data = std::make_unique<double[]>(N * M);
        for (size_t i = 0; i < N * M; ++i)
            data[i] = other.data[i];
    }

    // Move constructor
    Matrix(Matrix&& other) {
        data = std::move(other.data);
    }

    // Copy assignment
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            data = std::make_unique<double[]>(N * M);
            for (size_t i = 0; i < N * M; ++i)
                data[i] = other.data[i];
        }
        return *this;
    }

    // Move assignment
    Matrix& operator=(Matrix&& other) {
        if (this != &other) {
            data = std::move(other.data);
        }
        return *this;
    }

    // Destructor
    ~Matrix() {}

    // Element access
    double& at(size_t i, size_t j) {
        return data[i * M + j]; // without bounds check
    }

    const double& at(size_t i, size_t j) const {
        return data[i * M + j];
    }

    // Addition
    Matrix operator+(const Matrix& other) const {
        Matrix result;
        for (size_t i = 0; i < N * M; ++i)
            result.data[i] = data[i] + other.data[i];
        return result;
    }

    // Subtraction
    Matrix operator-(const Matrix& other) const {
        Matrix result;
        for (size_t i = 0; i < N * M; ++i)
            result.data[i] = data[i] - other.data[i];
        return result;
    }

    // Multiplication (if dimensions match: this[N x M] by other[M x P] = result[N x P])
    template <size_t P>
    Matrix<N, P> operator*(const Matrix<M, P>& other) const {
        Matrix<N, P> result;
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < P; ++j) {
                double sum = 0;
                for (size_t k = 0; k < M; ++k)
                    sum += at(i, k) * other.at(k, j);
                result.at(i, j) = sum;
            }
        }
        return result;
    }

    // Print the matrix
    void print() const {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j)
                std::cout << at(i, j) << " ";
            std::cout << "\n";
        }
    }
};

// Transpose function 
template <typename T, size_t N, size_t M>
Matrix<M, N> transpose(T&& mat) {
    Matrix<M, N> result;
    for (size_t i = 0; i < N; ++i)
        for (size_t j = 0; j < M; ++j)
            result.at(j, i) = mat.at(i, j);
    return result;
}

//  ------- Example 
int main() {
    Matrix<3, 3> A;

    // Fill A with sample values
    int val = 1;
    for (size_t i = 0; i < 3; ++i)
        for (size_t j = 0; j < 3; ++j)
            A.at(i, j) = val++;

    std::cout << "Matrix A:\n";
    A.print();

    // Transpose
    auto B = transpose(A);
    std::cout << "\nTransposed A:\n";
    B.print();

    // Lambda for trace of square matrix
    auto trace = [](const Matrix<3, 3>& mat) {
        double sum = 0;
        for (size_t i = 0; i < 3; ++i)
            sum += mat.at(i, i);
        return sum;
    };

    std::cout << "\nTrace of A: " << trace(A) << "\n";

    return 0;
}