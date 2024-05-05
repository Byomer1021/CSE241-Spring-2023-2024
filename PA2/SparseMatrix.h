#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

class SparseMatrix
{
private:
    std::vector<std::vector<double>> data; // Vector of vectors to store matrix data

public:
    // Constructors
    SparseMatrix() {} // Default constructor
    SparseMatrix(const std::vector<std::vector<double>> &matrix); // Constructor with matrix data

    // Constructor to read data from file
    SparseMatrix(const std::string &filename);

    // Operator overloads
    SparseMatrix operator+(const SparseMatrix &other) const; // Addition operator
    SparseMatrix operator-(const SparseMatrix &other) const; // Subtraction operator
    SparseMatrix operator-() const; // Unary negation operator
    SparseMatrix &operator=(const SparseMatrix &other); // Assignment operator
    friend std::ostream &operator<<(std::ostream &os, const SparseMatrix &matrix); // Output stream operator
    SparseMatrix operator*(const SparseMatrix &other) const; // Matrix multiplication operator
    void writeToFile(const std::string &filename) const; // Write matrix data to file

    // Member function to compute the transpose of the matrix
    SparseMatrix transpose() const;
};

#endif // SPARSEMATRIX_H
