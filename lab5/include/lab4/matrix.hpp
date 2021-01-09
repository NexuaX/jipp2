/* Double Matrix Class header
 * Author: Albert Mouhoubi
 */
#ifndef DOUBLE_MATRIX
#define DOUBLE_MATRIX

#include <string>
#include <iostream>

class DoubleMatrix {
private:
    size_t n, m;
    double * dm;
public:
    DoubleMatrix(size_t n, size_t m);
    DoubleMatrix(size_t n);
    DoubleMatrix(std::string filePath);
    DoubleMatrix(const DoubleMatrix & dm2);
    ~DoubleMatrix();

    double setElement(size_t n, size_t m, double val);
    double getElement(size_t n, size_t m) const;

    DoubleMatrix addMatrices(DoubleMatrix & dm2);
    DoubleMatrix subtractMatrices(DoubleMatrix & dm2);
    DoubleMatrix multiplyMatrices(DoubleMatrix & dm2);

    size_t cols() const;
    size_t rows() const;
    void print();
    bool store(std::string fileName, std::string filePath);

    DoubleMatrix operator+(const DoubleMatrix & dm2);
    DoubleMatrix operator-(const DoubleMatrix & dm2);
    DoubleMatrix operator*(const DoubleMatrix & dm2);
    friend std::ostream & operator<<(std::ostream & output, const DoubleMatrix & dm);

};

#endif