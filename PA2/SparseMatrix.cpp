#include "SparseMatrix.h"

// Constructor with parameter to initialize the matrix with given data
SparseMatrix::SparseMatrix(const std::vector<std::vector<double>> &matrix)
    : data(matrix) {}

// Overloaded operator+ to add two sparse matrices
SparseMatrix SparseMatrix::operator+(const SparseMatrix &other) const
{
    // Check if matrices have the same dimensions
    if (data.size() != other.data.size() || data[0].size() != other.data[0].size())
    {
        // Throw an exception if dimensions don't match
        throw std::invalid_argument("Matrices must have the same dimensions for addition.");
    }

    // Initialize a matrix to store the result of addition
    std::vector<std::vector<double>> result_data(data.size(), std::vector<double>(data[0].size(), 0.0));

    // Perform element-wise addition
    for (size_t i = 0; i < data.size(); ++i)
    {
        for (size_t j = 0; j < data[0].size(); ++j)
        {
            result_data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return SparseMatrix(result_data);
}

// Overloaded operator- to subtract one sparse matrix from another
SparseMatrix SparseMatrix::operator-(const SparseMatrix &other) const
{
    // Check if matrices have the same dimensions
    if (data.size() != other.data.size() || data[0].size() != other.data[0].size())
    {
        // Throw an exception if dimensions don't match
        throw std::invalid_argument("Matrices must have the same dimensions for subtraction.");
    }

    // Initialize a matrix to store the result of subtraction
    std::vector<std::vector<double>> result_data(data.size(), std::vector<double>(data[0].size(), 0.0));

    // Perform element-wise subtraction
    for (size_t i = 0; i < data.size(); ++i)
    {
        for (size_t j = 0; j < data[0].size(); ++j)
        {
            result_data[i][j] = data[i][j] - other.data[i][j];
        }
    }
    return SparseMatrix(result_data);
}

// Overloaded unary operator- to negate elements of the matrix
SparseMatrix SparseMatrix::operator-() const
{
    // Initialize a matrix to store the result of negation
    std::vector<std::vector<double>> result_data(data.size(), std::vector<double>(data[0].size(), 0.0));

    // Perform element-wise negation
    for (size_t i = 0; i < data.size(); ++i)
    {
        for (size_t j = 0; j < data[0].size(); ++j)
        {
            result_data[i][j] = -data[i][j];
        }
    }
    return SparseMatrix(result_data);
}

// Overloaded assignment operator to assign one matrix to another
SparseMatrix &SparseMatrix::operator=(const SparseMatrix &other)
{
    // Check for self-assignment
    if (this != &other)
    {
        // Assign data of the other matrix to this matrix
        data = other.data;
    }
    return *this;
}

// Overloaded stream insertion operator to output the matrix to a stream
std::ostream &operator<<(std::ostream &os, const SparseMatrix &matrix)
{
    // Output each element of the matrix
    for (const auto &row : matrix.data)
    {
        for (const auto &val : row)
        {
            os << val << " ";
        }
        os << std::endl;
    }
    return os;
}

// Function to perform matrix multiplication with another matrix
SparseMatrix SparseMatrix::operator*(const SparseMatrix &other) const
{
    // Check if the matrices have compatible dimensions for multiplication
    if (data[0].size() != other.data.size())
    {
        // Throw an exception if dimensions are incompatible
        throw std::invalid_argument("Invalid matrix dimensions for multiplication.");
    }

    // Initialize a matrix to store the result of multiplication
    size_t rows = data.size();
    size_t cols = other.data[0].size();
    size_t common = other.data.size();
    std::vector<std::vector<double>> result_data(rows, std::vector<double>(cols, 0.0));

    // Perform matrix multiplication
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            for (size_t k = 0; k < common; ++k)
            {
                result_data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    return SparseMatrix(result_data);
}

// Constructor to read matrix data from a file
SparseMatrix::SparseMatrix(const std::string &filename)
{
    // Open the file for reading
    std::ifstream file(filename);
    if (!file.is_open())
    {
        // Throw an exception if file cannot be opened
        throw std::invalid_argument("Cannot open file: " + filename);
    }

    // Read data from the file
    std::string line;
    while (std::getline(file, line))
    {
        std::vector<double> row;
        std::istringstream iss(line);
        double val;
        while (iss >> val)
        {
            row.push_back(val);
        }
        data.push_back(row);
    }
    file.close(); // Close the file after reading
}

// Function to write matrix data to a file
void SparseMatrix::writeToFile(const std::string &filename) const
{
    // Open the file for writing
    std::ofstream file(filename);
    if (!file.is_open())
    {
        // Throw an exception if file cannot be opened for writing
        throw std::invalid_argument("Cannot open file for writing: " + filename);
    }

    // Write data to the file
    for (const auto &row : data)
    {
        for (const auto &val : row)
        {
            file << val << " ";
        }
        file << std::endl;
    }
    file.close(); // Close the file after writing
}

// Function to transpose the matrix
SparseMatrix SparseMatrix::transpose() const
{
    // Check if the matrix is empty
    if (data.empty())
        return SparseMatrix();

    // Calculate the number of rows and columns after transposition
    const size_t rows = data.size();
    const size_t cols = data[0].size();

    // Initialize a matrix to store the transposed data
    std::vector<std::vector<double>> transposed(cols, std::vector<double>(rows));

    // Perform transposition
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            transposed[j][i] = data[i][j];
        }
    }
    return SparseMatrix(transposed);
}
