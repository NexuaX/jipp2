/* Double Matrix Class implementation + sqlite engine
** Author: Albert Mouhoubi
*/
#include <lab4/matrix.hpp>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

DoubleMatrix::DoubleMatrix(size_t n, size_t m) {
	try {
		this->dm = new double[n*m];
		this->n = n;
		this->m = m;
	} catch (exception & e) {
		cerr << "Error creating Double Matrix" << endl;
		cerr << e.what() << endl;
	}
}

DoubleMatrix::DoubleMatrix(size_t n) : DoubleMatrix(n, n) {
}

DoubleMatrix::DoubleMatrix(std::string fileName, int mode) {
	if (mode == SQLite) {

		sqlite3 * db;
		std::string stmn;

		int result = sqlite3_open((fileName + ".db").c_str(), &db);

		if (result) {
			cout << "Database open error! " << sqlite3_errmsg(db) << endl;
		} else {
			cout << "Database opened successfully!" << endl;
		}

		int callbackGetNumCols(void *data, int argc, char **argv, char **azColName);
		int callbackGetNumRows(void *data, int argc, char **argv, char **azColName);
		int callbackAndWrite(void *data, int argc, char **argv, char **azColName);

		stmn = "SELECT * FROM " + fileName + " limit 1;";
		result = sqlite3_exec(db, stmn.c_str(), callbackGetNumCols, this, 0);

		stmn = "SELECT COUNT(*) FROM " + fileName + " limit 1;";
		result = sqlite3_exec(db, stmn.c_str(), callbackGetNumRows, this, 0);

		this->dm = new double[this->n*this->m];

		stmn = "SELECT * FROM " + fileName + ";";
		result = sqlite3_exec(db, stmn.c_str(), callbackAndWrite, this, 0);

		if (result != SQLITE_OK) {
			cout << "Table read errors!" << endl;
		} else {
			cout << "Reading data from table successful!" << endl;
		}

	} else if (mode == TXT) {
		ifstream file(fileName + ".txt");
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
	} else {
		cout << "Bad mode!" << endl;
	}
	

}

DoubleMatrix::DoubleMatrix(const DoubleMatrix & dm2) : DoubleMatrix(dm2.n, dm2.m) {
	memcpy(this->dm, dm2.dm, dm2.n*dm2.m * sizeof(double));
}

DoubleMatrix::~DoubleMatrix() {
	delete [] this->dm;
	cout << "DESTROYED!" << endl;
}

double DoubleMatrix::setElement(size_t n, size_t m, double val) {
	try {
		this->dm[n*this->m+m] = val;
	} catch (exception & e) {
		cerr << "Exception!" << endl;
		cerr << e.what() << endl;
	}
	return val;
}

double DoubleMatrix::getElement(size_t n, size_t m) {
	try {
		return this->dm[n*this->m+m];
	} catch (exception & e) {
		cerr << "Exception!" << endl;
		cerr << e.what() << endl;
	}
}

DoubleMatrix DoubleMatrix::addMatrices(DoubleMatrix & dm2) {
	try {
		if (this->n != dm2.n || this->m != dm2.m) {
			throw "Operation requires identical matrices dimentions!";
		}
		DoubleMatrix result(this->n, this->m);
		double currentElementsSum;
		for (size_t i = 0; i < result.rows(); i++) {
			for (size_t j = 0; j < result.cols(); j++) {
				currentElementsSum = this->getElement(i, j) + dm2.getElement(i, j);
				result.setElement(i, j, currentElementsSum);
			}
		}
		return result;
	} catch (char * message) {
		cerr << "Exception! (addMatrices)" << endl;
		cerr << message << endl;
	}
	return *this;
}

DoubleMatrix DoubleMatrix::subtractMatrices(DoubleMatrix & dm2) {
	try {
		if (this->n != dm2.n || this->m != dm2.m) {
			throw "Operation requires identical matrices dimentions!";
		}
		DoubleMatrix result(this->n, this->m);
		double currentElementsSub;
		for (size_t i = 0; i < result.rows(); i++) {
			for (size_t j = 0; j < result.cols(); j++) {
				currentElementsSub = this->getElement(i, j) - dm2.getElement(i, j);
				result.setElement(i, j, currentElementsSub);
			}
		}
		return result;
	} catch (char * message) {
		cerr << "Exception! (subMatrices)" << endl;
		cerr << message << endl;
	}
	return *this;
}

DoubleMatrix DoubleMatrix::multiplyMatrices(DoubleMatrix & dm2) {
	try {
		if (this->m == dm2.n) {
			throw "Operation requires matrices in proper dimentions!";
		}
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
	} catch (char * message) {
		cerr << "Exception! (multiplyMatrices)" << endl;
		cerr << message << endl;
	}
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

bool DoubleMatrix::storeSQLite(std::string fileName) {

	sqlite3 * db;
	std::string stmn;

	int result = sqlite3_open((fileName + ".db").c_str(), &db);

	if (result) {
		cout << "Database open error! " << sqlite3_errmsg(db) << endl;
	} else {
		cout << "Database opened successfully!" << endl;
	}

	std::stringstream builder;

	builder << "CREATE TABLE IF NOT EXISTS " << fileName << "(row_id int primary key not null";

	for (size_t	i = 0; i < this->m; i++) {
		builder << ", col" << i << " real not null";
	}
	builder << ");";
	stmn = builder.str();

	cout << stmn << endl;

	result = sqlite3_exec(db, stmn.c_str(), 0, 0, 0);
	if (result != SQLITE_OK) {
    	cout << "Database exec error!" << endl;
   	} else {
    	cout <<  "Table created successfully" << endl;
   	}

	builder.str("");

	builder << "INSERT INTO " << fileName << " VALUES";

	for (size_t	i = 0; i < this->n; i++) {
		builder << "(" << i;
		for (size_t j = 0; j < this->m; j++) {
			builder << ", " << this->dm[i*this->m+j];
		}
		builder << "),";
	}
	builder.seekp(-1, builder.cur);
	builder << ";";
	stmn = builder.str();

	cout << stmn << endl;

	result = sqlite3_exec(db, stmn.c_str(), 0, 0, 0);
	if (result != SQLITE_OK) {
    	cout << "Database exec error!" << endl;
   	} else {
    	cout <<  "Data inserted successfully" << endl;
	}

	stmn = "SELECT * FROM " + fileName + ";";
	builder.str("");
	builder << "row_id |";
	for (size_t i = 0; i < this->m; i++) {
		builder << "   col" << i << "   | ";
	}
	cout << builder.str() << endl;

	int callback(void *data, int argc, char **argv, char **azColName);
	
	result = sqlite3_exec(db, stmn.c_str(), callback, 0, 0);
	if (result != SQLITE_OK) {
    	cout << "Database exec error!" << endl;
   	} else {
    	cout <<  "Data selected successfully" << endl;
   	}


	sqlite3_close(db);

	return 0;

}

int callback(void *data, int argc, char **argv, char **azColName) {
	
	cout << setw(7) << argv[0] << " ";
	for(int i = 1; i < argc; i++) {
		cout << setw(10) << argv[i] << "  ";
	}

	cout << endl;
	return 0;
}

int callbackGetNumCols(void *data, int argc, char **argv, char **azColName) {

	DoubleMatrix * dm = (DoubleMatrix *)data;
	dm->m = argc - 1;

	return 0;

}

int callbackGetNumRows(void *data, int argc, char **argv, char **azColName) {

	DoubleMatrix * dm = (DoubleMatrix *)data;
	dm->n = atoi(argv[0]);

	return 0;

}

int callbackAndWrite(void *data, int argc, char **argv, char **azColName) {

	DoubleMatrix * dm = (DoubleMatrix *)data;

	int row = atoi(argv[0]);
	
	for (size_t i = 0; i < argc-1; i++) {
		dm->dm[row*dm->m+i] = atof(argv[i+1]);
	}

	return 0;

}
