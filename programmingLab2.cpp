#include <iostream>             // Include the iostream library for input/output
using namespace std;            // Use the standard namespace

class matr {
public:
    int dim;                    // Matrix dimension (assumes square matrix)
    double** a;                 // Pointer to dynamically allocated 2D array (matrix)
    int num;                    // Unique ID number for each matrix object
    static int count;           // Static counter to keep track of matrix objects

    // Constructor
    matr(int d = 3) : dim(d) {  // Constructor with default dimension 3
        a = new double*[dim];   // Allocate array of row pointers
        for (int i = 0; i < dim; ++i)
            a[i] = new double[dim]; // Allocate each row

        for (int i = 0; i < dim; ++i)
            for (int j = 0; j < dim; ++j)
                a[i][j] = 0;    // Initialize all elements to 0

        num = ++count;         // Assign a unique matrix number
        cout << "Constructed matr #" << num << endl; // Message when constructed
    }

    // Copy Constructor
    matr(const matr& m) : dim(m.dim) { // Copy constructor
        a = new double*[dim];   // Allocate memory for new matrix
        for (int i = 0; i < dim; ++i) {
            a[i] = new double[dim]; // Allocate each row
            for (int j = 0; j < dim; ++j)
                a[i][j] = m.a[i][j]; // Copy each element from source
        }
        num = ++count;         // Assign a new unique number
        cout << "Copied matr #" << num << endl; // Message when copied
    }

    // Destructor
    ~matr() {
        for (int i = 0; i < dim; ++i)
            delete[] a[i];     // Delete each row
        delete[] a;            // Delete row pointers
        cout << "Destructed matr #" << num << endl; // Message on destruction
    }

    // Assignment Operator
    matr& operator=(const matr& m) {
        if (this != &m) {      // Avoid self-assignment
            for (int i = 0; i < dim; ++i)
                delete[] a[i]; // Free current matrix memory
            delete[] a;

            dim = m.dim;       // Copy dimension
            a = new double*[dim]; // Allocate new matrix
            for (int i = 0; i < dim; ++i) {
                a[i] = new double[dim];
                for (int j = 0; j < dim; ++j)
                    a[i][j] = m.a[i][j]; // Copy elements
            }
        }
        cout << "Assigned matr #" << num << endl; // Message on assignment
        return *this;           // Return reference to current object
    }

    // Addition Operator Overload
    matr operator+(const matr& m) const {
        matr res(dim);         // Create result matrix
        for (int i = 0; i < dim; ++i)
            for (int j = 0; j < dim; ++j)
                res.a[i][j] = a[i][j] + m.a[i][j]; // Element-wise addition
        cout << "Added matr #" << num << " and #" << m.num << endl;
        return res;            // Return result matrix
    }

    // Subtraction Operator Overload
    matr operator-(const matr& m) const {
        matr res(dim);         // Create result matrix
        for (int i = 0; i < dim; ++i)
            for (int j = 0; j < dim; ++j)
                res.a[i][j] = a[i][j] - m.a[i][j]; // Element-wise subtraction
        cout << "Subtracted matr #" << num << " and #" << m.num << endl;
        return res;            // Return result matrix
    }

    // Unary Negation Operator Overload
    matr operator-() const {
        matr res(dim);         // Create result matrix
        for (int i = 0; i < dim; ++i)
            for (int j = 0; j < dim; ++j)
                res.a[i][j] = -a[i][j]; // Negate each element
        cout << "Negated matr #" << num << endl;
        return res;            // Return result matrix
    }

    // Multiplication Operator Overload (Matrix * Matrix)
    matr operator*(const matr& m) const {
        matr res(dim);         // Create result matrix
        for (int i = 0; i < dim; ++i)
            for (int j = 0; j < dim; ++j) {
                res.a[i][j] = 0; // Initialize result element
                for (int k = 0; k < dim; ++k)
                    res.a[i][j] += a[i][k] * m.a[k][j]; // Matrix multiplication
            }
        cout << "Multiplied matr #" << num << " and #" << m.num << endl;
        return res;            // Return result matrix
    }

    // Scalar Multiplication Friend Function
    friend matr operator*(double k, const matr& m) {
        matr res(m.dim);       // Create result matrix
        for (int i = 0; i < m.dim; ++i)
            for (int j = 0; j < m.dim; ++j)
                res.a[i][j] = k * m.a[i][j]; // Multiply each element by scalar
        cout << "Scalar multiplied matr #" << m.num << " by " << k << endl;
        return res;            // Return result matrix
    }

    // Print the matrix to console
    void print() const {
        cout << "matr #" << num << ":\n"; // Header
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j)
                cout << a[i][j] << " ";   // Print each element
            cout << endl;                // New line per row
        }
    }
};

// Initialize static variable count to 0
int matr::count = 0;

// Main function to test matrix operations
int main() {
    matr m1(3), m2(3);          // Create two 3x3 matrices

    // Fill m1 with values from 1 to 9
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            m1.a[i][j] = i * 3 + j + 1;

    // Fill m2 with values from 9 to 1
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            m2.a[i][j] = 9 - (i * 3 + j);

    // Print matrix m1
    cout << "Matrix m1:" << endl;
    m1.print();

    // Print matrix m2
    cout << "Matrix m2:" << endl;
    m2.print();

    // Scalar multiplication: m3 = 2 * m1
    matr m3 = 2.0 * m1;
    cout << "Matrix m3 (2 * m1):" << endl;
    m3.print();

    // Addition: m4 = m1 + m2
    matr m4 = m1 + m2;
    cout << "Matrix m4 (m1 + m2):" << endl;
    m4.print();

    // Multiplication: m5 = m1 * m2
    matr m5 = m1 * m2;
    cout << "Matrix m5 (m1 * m2):" << endl;
    m5.print();

    return 0;                   // Program completed successfully
}
