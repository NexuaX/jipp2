/* Double Matrix Class header
 * Author: Albert Mouhoubi
 */
#ifndef DOUBLE_MATRIX
#define DOUBLE_MATRIX

#include <string>

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
    double getElement(size_t n, size_t m);

    DoubleMatrix addMatrices(DoubleMatrix & dm2);
    DoubleMatrix subtractMatrices(DoubleMatrix & dm2);
    DoubleMatrix multiplyMatrices(DoubleMatrix & dm2);

    size_t cols();
    size_t rows();
    void print();
    bool store(std::string fileName, std::string filePath);
};

#endif