/* Double Matrix Class implementation
 * Author: Albert Mouhoubi
 */
#include <lab4/matrix.hpp>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

DoubleMatrix::DoubleMatrix(size_t n, size_t m) {
	this->dm = new double[n*m];
	if (dm == nullptr) {
		cerr << "Error creating Double Matrix" << endl;
	}
	this->n = n;
	this->m = m;
}

DoubleMatrix::DoubleMatrix(size_t n) : DoubleMatrix(n, n) {
}

DoubleMatrix::DoubleMatrix(std::string filePath) {
	ifstream file(filePath);
	if (!file.is_open()) {
		cerr << "Error opening file!" << endl;
		this->dm = new double[1];
		if (this->dm == nullptr) {
			cerr << "Error creating Double Matrix" << endl;
		}
		this->n = 1;
		this->m = 1;
	} else {
		size_t n, m;
		file >> n >> m;

		this->dm = new double[n*m];
		if (this->dm == nullptr) {
			cerr << "Error creating Double Matrix" << endl;
		}
		this->n = n;
		this->m = m;
		for (size_t i = 0; i < n; i++) {
			for (size_t j = 0; j < m; j++) {
				file >> this->dm[i*m+j];
			}
		}
	}
	file.close();
}

DoubleMatrix::DoubleMatrix(const DoubleMatrix & dm2) : DoubleMatrix(dm2.n, dm2.m) {
	memcpy(this->dm, dm2.dm, dm2.n*dm2.m * sizeof(double));
}

DoubleMatrix::~DoubleMatrix() {
	delete [] this->dm;
	cout << "DESTROYED!" << endl;
}

double DoubleMatrix::setElement(size_t n, size_t m, double val) {
	this->dm[n*this->m+m] = val;
	return val;
}

double DoubleMatrix::getElement(size_t n, size_t m) {
	return this->dm[n*this->m+m];
}

DoubleMatrix DoubleMatrix::addMatrices(DoubleMatrix & dm2) {
	if (this->n == dm2.n && this->m == dm2.m) {
		DoubleMatrix result(this->n, this->m);
		double currentElementsSum;
		for (size_t i = 0; i < result.rows(); i++) {
			for (size_t j = 0; j < result.cols(); j++) {
				currentElementsSum = this->getElement(i, j) + dm2.getElement(i, j);
				result.setElement(i, j, currentElementsSum);
			}
		}

		return result;
	}
	cerr << "Matrices not the same size!" << endl;
	return *this;
}

DoubleMatrix DoubleMatrix::subtractMatrices(DoubleMatrix & dm2) {
	if (this->n == dm2.n && this->m == dm2.m) {
		DoubleMatrix result(this->n, this->m);
		double currentElementsSub;
		for (size_t i = 0; i < result.rows(); i++) {
			for (size_t j = 0; j < result.cols(); j++) {
				currentElementsSub = this->getElement(i, j) - dm2.getElement(i, j);
				result.setElement(i, j, currentElementsSub);
			}
		}

		return result;
	}
	cerr << "Matrices not the same size!" << endl;
	return *this;
}

DoubleMatrix DoubleMatrix::multiplyMatrices(DoubleMatrix & dm2) {
	if (this->m == dm2.n) {
		DoubleMatrix result(this->n, dm2.m);
		double currentElementMult;
		for (size_t i = 0; i < result.rows(); i++) {
			for (size_t j = 0; j < result.cols(); j++) {
				currentElementMult = 0;
				for (size_t k = 0; k < this->m; k++) {
					currentElementMult += this->getElement(i, k) * dm2.getElement(k, j);
				}
				result.setElement(i, j, currentElementMult);
			} 
		}
		return result;
	}
	cerr << "Matrices not in proper sizes! \n";
	return *this;
}

size_t DoubleMatrix::cols() {
	return this->m;
}

size_t DoubleMatrix::rows() {
	return this->n;
}

void DoubleMatrix::print() {
	cout << "Double Matrix " << this->n << "x" << this->m << endl;
	for (size_t i = 0; i < this->n; i++) {
		for (size_t j = 0; j < this->m; j++) {
			cout << this->getElement(i, j) << " ";
		}
		cout << endl;
	}
}

bool DoubleMatrix::store(std::string fileName, std::string filePath) {
	ofstream file(fileName);
	if (!file.is_open()) {
		cerr << "Error creating file!" << endl;
		return false;
	}
	
	file << setprecision(6) << fixed;
	file << this->n << " " << this->m << endl;
	for (size_t i = 0; i < this->n; i++) {
		for (size_t j = 0; j < this->m; j++) {
			file << this->getElement(i, j) << " ";
		}
		file << endl;
	}

	file.close();
	return true;
}


