#include <iostream>
using namespace std;

// Definition of the matr class (Matrix class)
class matr {
public:
    int dim;          // Dimension of the matrix (number of rows and columns)
    double* a;        // Pointer to the dynamically allocated array that stores the matrix values
    int num;          // Unique identifier for each matrix (to track instances)
    static int count; // Static variable to keep track of the number of matrices created

    // Constructor to initialize the matrix
    matr(int d = 3) : dim(d) {
        a = new double[dim * dim];  // Allocate memory for the matrix (dim x dim)
        for (int i = 0; i < dim * dim; ++i) a[i] = 0; // Initialize all elements to 0
        num = ++count;  // Assign a unique number to this matrix instance
        cout << "Constructed matr #" << num << endl;
    }

    // Copy constructor to create a new matrix as a copy of an existing one
    matr(const matr& m) : dim(m.dim) {
        a = new double[dim * dim];  // Allocate memory for the new matrix
        for (int i = 0; i < dim * dim; ++i) a[i] = m.a[i];  // Copy data from the original matrix
        num = ++count;  // Assign a unique number to the copied matrix
        cout << "Copied matr #" << num << endl;
    }

    // Destructor to clean up dynamically allocated memory
    ~matr() {
        cout << "Destructed matr #" << num << endl;
        delete[] a;  // Free the allocated memory
    }

    // Assignment operator to assign the values of one matrix to another
    matr& operator=(const matr& m) {
        if (this != &m) {  // Check for self-assignment
            if (dim != m.dim) {  // If dimensions are different, reallocate memory
                delete[] a;  // Release the old memory
                dim = m.dim;  // Set the new dimension
                a = new double[dim * dim];  // Allocate new memory for the matrix
            }
            for (int i = 0; i < dim * dim; ++i) a[i] = m.a[i];  // Copy the data
        }
        cout << "Assigned matr #" << num << endl;
        return *this;
    }

    // Overload the addition operator to add two matrices
    matr operator+(const matr& m) const {
        matr res(dim);  // Create a new matrix to store the result
        for (int i = 0; i < dim * dim; ++i) res.a[i] = a[i] + m.a[i];  // Element-wise addition
        cout << "Added matr #" << num << " and #" << m.num << endl;
        return res;
    }

    // Overload the subtraction operator to subtract two matrices
    matr operator-(const matr& m) const {
        matr res(dim);  // Create a new matrix to store the result
        for (int i = 0; i < dim * dim; ++i) res.a[i] = a[i] - m.a[i];  // Element-wise subtraction
        cout << "Subtracted matr #" << num << " and #" << m.num << endl;
        return res;
    }

    // Overload the negation operator to negate the matrix (multiply each element by -1)
    matr operator-() const {
        matr res(dim);  // Create a new matrix to store the result
        for (int i = 0; i < dim * dim; ++i) res.a[i] = -a[i];  // Element-wise negation
        cout << "Negated matr #" << num << endl;
        return res;
    }

    // Overload the multiplication operator for matrix-matrix multiplication
    matr operator*(const matr& m) const {
        matr res(dim);  // Create a new matrix to store the result
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j) {
                res.a[i * dim + j] = 0;  // Initialize the result element to 0
                for (int k = 0; k < dim; ++k)
                    res.a[i * dim + j] += a[i * dim + k] * m.a[k * dim + j];  // Matrix multiplication logic
            }
        }
        cout << "Multiplied matr #" << num << " and #" << m.num << endl;
        return res;
    }

    // Friend function to overload the multiplication operator for scalar multiplication (multiplying a matrix by a scalar)
    friend matr operator*(double k, const matr& m) {
        matr res(m.dim);  // Create a new matrix to store the result
        for (int i = 0; i < m.dim * m.dim; ++i) res.a[i] = k * m.a[i];  // Element-wise scalar multiplication
        cout << "Scalar multiplied matr #" << m.num << " by " << k << endl;
        return res;
    }

    // Function to print the matrix to the console
    void print() const {
        cout << "matr #" << num << ":\n";
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j)
                cout << a[i * dim + j] << " ";  // Print each element of the matrix
            cout << endl;
        }
    }
};

// Initialize the static variable to count the number of matrices
int matr::count = 0;

// Main function where the program starts executing
int main() {
    matr m1(3), m2(3);  // Create two 3x3 matrices
    
    // Fill matrix m1 with values (1 to 9)
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            m1.a[i * 3 + j] = i * 3 + j + 1;
    
    // Fill matrix m2 with values (9 to 1 in reverse order)
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            m2.a[i * 3 + j] = 9 - (i * 3 + j);

    // Printing matrices before scalar multiplication
    cout << "Matrix m1 before scalar multiplication:" << endl;
    m1.print();
    cout << "Matrix m2 before scalar multiplication:" << endl;
    m2.print();
    
    // Scalar multiplication by 2
    matr m3 = 2.0 * m1;  // Multiply matrix m1 by 2
    m3.print();  // Print the result

    // Matrix addition
    matr m4 = m1 + m2;  // Add matrices m1 and m2
    m4.print();  // Print the result

    // Matrix multiplication
    matr m5 = m1 * m2;  // Multiply matrices m1 and m2
    m5.print();  // Print the result

    return 0;
}
