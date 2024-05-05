#include "SparseVector.h"

// Constructor with parameters to initialize the sparse vector with given indices and values
SparseVector::SparseVector(const std::vector<int> &idx, const std::vector<double> &vals)
    : indices(idx), values(vals) {}

// Constructor to read sparse vector data from a file
SparseVector::SparseVector(const std::string& filename) {
    // Open the file for reading
    std::ifstream file(filename);
    if (!file) {
        // Throw an exception if file cannot be opened
        throw std::invalid_argument("Error: Cannot open file.");
    }

    // Read data from the file
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int index;
        char delim;
        double value;
        while (iss >> index >> delim >> value) {
            if (index < 0 || value == 0.0) {
                // Throw an exception if index is negative or value is zero
                throw std::invalid_argument("Error: Invalid index or value.");
            }
            // Add data to the vectors
            indices.push_back(index);
            values.push_back(value);
        }
    }

    file.close(); // Close the file after reading
}

// Overloaded operator+ to add two sparse vectors
SparseVector SparseVector::operator+(const SparseVector &other) const
{
    // Initialize vectors to store the result
    std::vector<double> result_values;
    std::vector<int> result_indices;
    size_t i = 0, j = 0;
    // Merge the vectors while iterating through them
    while (i < indices.size() && j < other.indices.size())
    {
        if (indices[i] == other.indices[j])
        {
            // If indices match, add corresponding values
            result_indices.push_back(indices[i]);
            result_values.push_back(values[i] + other.values[j]);
            ++i;
            ++j;
        }
        else if (indices[i] < other.indices[j])
        {
            // Add current index-value pair from the first vector
            result_indices.push_back(indices[i]);
            result_values.push_back(values[i]);
            ++i;
        }
        else
        {
            // Add current index-value pair from the second vector
            result_indices.push_back(other.indices[j]);
            result_values.push_back(other.values[j]);
            ++j;
        }
    }
    // Add remaining elements from both vectors
    while (i < indices.size())
    {
        result_indices.push_back(indices[i]);
        result_values.push_back(values[i]);
        ++i;
    }
    while (j < other.indices.size())
    {
        result_indices.push_back(other.indices[j]);
        result_values.push_back(other.values[j]);
        ++j;
    }
    return SparseVector(result_indices, result_values);
}

// Overloaded operator- to subtract one sparse vector from another
SparseVector SparseVector::operator-(const SparseVector &other) const
{
    // Initialize vectors to store the result
    std::vector<double> result_values;
    std::vector<int> result_indices;
    size_t i = 0, j = 0;
    // Merge the vectors while iterating through them
    while (i < indices.size() && j < other.indices.size())
    {
        if (indices[i] == other.indices[j])
        {
            // If indices match, subtract corresponding values
            result_indices.push_back(indices[i]);
            result_values.push_back(values[i] - other.values[j]);
            ++i;
            ++j;
        }
        else if (indices[i] < other.indices[j])
        {
            // Add current index-value pair from the first vector
            result_indices.push_back(indices[i]);
            result_values.push_back(values[i]);
            ++i;
        }
        else
        {
            // Add negation of current index-value pair from the second vector
            result_indices.push_back(other.indices[j]);
            result_values.push_back(-other.values[j]);
            ++j;
        }
    }
    // Add remaining elements from both vectors
    while (i < indices.size())
    {
        result_indices.push_back(indices[i]);
        result_values.push_back(values[i]);
        ++i;
    }
    while (j < other.indices.size())
    {
        result_indices.push_back(other.indices[j]);
        result_values.push_back(-other.values[j]);
        ++j;
    }
    return SparseVector(result_indices, result_values);
}

// Overloaded unary operator- to negate elements of the vector
SparseVector SparseVector::operator-() const
{
    // Initialize vector to store the result
    std::vector<double> result_values;
    std::vector<int> result_indices = indices;
    // Negate each value of the vector
    for (size_t i = 0; i < values.size(); ++i)
    {
        result_values.push_back(-values[i]);
    }
    return SparseVector(result_indices, result_values);
}

// Overloaded assignment operator to assign one vector to another
SparseVector &SparseVector::operator=(const SparseVector &other)
{
    // Check for self-assignment
    if (this != &other)
    {
        // Assign indices and values from the other vector
        indices = other.indices;
        values = other.values;
    }
    return *this;
}

// Overloaded stream insertion operator to output the vector to a stream
std::ostream &operator<<(std::ostream &os, const SparseVector &vec)
{
    // Output each index-value pair of the vector
    for (size_t i = 0; i < vec.indices.size(); ++i)
    {
        os << vec.indices[i] << ":" << vec.values[i] << " ";
    }
    return os;
}

// Function to write vector data to a file
void SparseVector::writeToFile(const std::string& filename) const {
    // Open the file for writing
    std::ofstream file(filename);
    if (!file) {
        // Throw an exception if file cannot be opened for writing
        throw std::invalid_argument("Error: Cannot open file.");
    }

    // Write data to the file
    for (size_t i = 0; i < indices.size(); ++i) {
        file << indices[i] << ":" << values[i] << " ";
    }
    file << std::endl;

    file.close(); // Close the file after writing
}

// Function to calculate the dot product of two vectors
double SparseVector::dot(const SparseVector &other) const
{
    // Initialize the result
    double result = 0.0;
    size_t i = 0, j = 0;
    // Calculate dot product while iterating through both vectors
    while (i < indices.size() && j < other.indices.size())
    {
        if (indices[i] == other.indices[j])
        {
            // If indices match, add the product of values
            result += values[i] * other.values[j];
            ++i;
            ++j;
        }
        else if (indices[i] < other.indices[j])
        {
            // Increment index of the first vector
            ++i;
        }
        else
        {
            // Increment index of the second vector
            ++j;
        }
    }
    return result;
}
