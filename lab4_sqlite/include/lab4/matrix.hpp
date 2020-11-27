/* Double Matrix Class header + sqlite store function
** Author: Albert Mouhoubi
*/
#ifndef DOUBLE_MATRIX
#define DOUBLE_MATRIX

#include <string>
#include <sqlite3/sqlite3.h>

#define SQLite 1
#define TXT 0

class DoubleMatrix {
private:
    size_t n, m;
    double * dm;
public:
    DoubleMatrix(size_t n, size_t m);
    DoubleMatrix(size_t n);
    DoubleMatrix(std::string fileName, int mode);
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

    // SQLite engine to store matrices
    bool storeSQLite(std::string fileName);
    friend int callbackGetNumCols(void *data, int argc, char **argv, char **azColName);
    friend int callbackGetNumRows(void *data, int argc, char **argv, char **azColName);
    friend int callbackAndWrite(void *data, int argc, char **argv, char **azColName);
};

#endif