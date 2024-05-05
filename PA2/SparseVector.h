#ifndef SPARSEVECTOR_H
#define SPARSEVECTOR_H

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

class SparseVector
{
private:
    std::vector<double> values; // Vector to store non-zero values
    std::vector<int> indices;   // Vector to store corresponding indices

public:
    // Constructors
    SparseVector() {} // Default constructor
    SparseVector(const std::vector<int> &idx, const std::vector<double> &vals); // Constructor with indices and values

    // Constructor to read data from file
    SparseVector(const std::string &filename);

    // Operator overloads
    SparseVector operator+(const SparseVector &other) const; // Addition operator
    SparseVector operator-(const SparseVector &other) const; // Subtraction operator
    SparseVector operator-() const; // Unary negation operator
    SparseVector &operator=(const SparseVector &other); // Assignment operator
    friend std::ostream &operator<<(std::ostream &os, const SparseVector &vec); // Output stream operator
    void writeToFile(const std::string &filename) const; // Write vector data to file

    // Member function to calculate dot product
    double dot(const SparseVector &other) const;
};

#endif // SPARSEVECTOR_H
