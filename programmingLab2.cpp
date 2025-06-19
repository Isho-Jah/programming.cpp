#include <iostream>
using namespace std;

// Vector class for mathematical vector operations
class vect {
private:
    int dim;        // Stores the dimension (size) of the vector
    double* b;      // Pointer to dynamically allocated array storing vector elements
    int num;        // Unique identifier for each vector instance
    static int count; // Static counter to track total number of vector objects created

public:
    // Default constructor - creates empty vector
    vect() : dim(0), b(nullptr) {
        num = ++count;  // Assigns unique ID by incrementing static counter
        cout << "Created vector #" << num << " (default)" << endl; // Creation message
    }

    // Parameterized constructor - creates vector of given dimension
    vect(int n) : dim(n) {
        b = new double[dim];  // Allocates memory for vector elements
        for (int i = 0; i < dim; i++) b[i] = 0; // Initializes all elements to zero
        num = ++count;  // Assigns unique ID
        cout << "Created vector #" << num << " (dimension " << dim << ")" << endl;
    }

    // Copy constructor - creates copy of existing vector
    vect(const vect& v) : dim(v.dim) {
        b = new double[dim];  // Allocates new memory
        for (int i = 0; i < dim; i++) b[i] = v.b[i]; // Copies all elements
        num = ++count;  // New unique ID for the copy
        cout << "Created vector #" << num << " (copy of vector #" << v.num << ")" << endl;
    }

    // Destructor - cleans up dynamically allocated memory
    ~vect() {
        delete[] b;  // Frees the allocated array
        cout << "Destroyed vector #" << num << endl; // Destruction message
    }

    // Assignment operator - copies contents from one vector to another
    vect& operator=(const vect& v) {
        cout << "Assignment: vector #" << num << " = vector #" << v.num << endl;
        if (this != &v) {  // Check for self-assignment
            delete[] b;  // Free existing memory
            dim = v.dim;  // Copy dimension
            b = new double[dim];  // Allocate new memory
            for (int i = 0; i < dim; i++) b[i] = v.b[i]; // Copy elements
        }
        return *this;  // Return reference to current object
    }

    // Vector addition operator
    vect operator+(const vect& v) {
        cout << "Addition: vector #" << num << " + vector #" << v.num << endl;
        if (dim != v.dim) {  // Check for compatible dimensions
            cerr << "Error: different dimensions!" << endl;
            return vect();  // Return empty vector if incompatible
        }
        vect res(dim);  // Create result vector
        for (int i = 0; i < dim; i++) res.b[i] = b[i] + v.b[i]; // Element-wise addition
        return res;  // Return result
    }

    // Vector subtraction operator
    vect operator-(const vect& v) {
        cout << "Subtraction: vector #" << num << " - vector #" << v.num << endl;
        if (dim != v.dim) {  // Dimension check
            cerr << "Error: different dimensions!" << endl;
            return vect();
        }
        vect res(dim);
        for (int i = 0; i < dim; i++) res.b[i] = b[i] - v.b[i]; // Element-wise subtraction
        return res;
    }

    // Unary minus operator (negation)
    vect operator-() {
        cout << "Unary minus: -vector #" << num << endl;
        vect res(dim);  // Create result vector
        for (int i = 0; i < dim; i++) res.b[i] = -b[i]; // Negate each element
        return res;
    }

    // Dot product operator
    double operator*(const vect& v) {
        cout << "Dot product: vector #" << num << " * vector #" << v.num << endl;
        if (dim != v.dim) {  // Dimension check
            cerr << "Error: different dimensions!" << endl;
            return 0.0;  // Return zero if incompatible
        }
        double res = 0;  // Initialize result
        for (int i = 0; i < dim; i++) res += b[i] * v.b[i]; // Sum of products
        return res;
    }

    // Friend function for scalar multiplication (allows commutative operation)
    friend vect operator*(double k, const vect& v);

    // Print vector contents
    void print() {
        cout << "Vector #" << num << " [";
        for (int i = 0; i < dim; i++) cout << b[i] << (i < dim - 1 ? ", " : "");
        cout << "]" << endl;
    }

    // Getter methods
    int get_dim() const { return dim; }  // Returns vector dimension
    int get_num() const { return num; }  // Returns vector ID
    double get(int i) const { return (i >= 0 && i < dim) ? b[i] : 0.0; } // Safe element access
    void set(int i, double val) { if (i >= 0 && i < dim) b[i] = val; } // Safe element modification
};

// Initialize static counter
int vect::count = 0;

// Scalar multiplication (friend function implementation)
vect operator*(double k, const vect& v) {
    cout << "Multiplication: " << k << " * vector #" << v.num << endl;
    vect res(v.dim);  // Create result vector
    for (int i = 0; i < v.dim; i++) res.set(i, k * v.get(i)); // Multiply each element
    return res;
}

// Matrix class for mathematical matrix operations
class matr {
private:
    int n, m;       // Dimensions (rows, columns)
    double** a;     // 2D array for matrix elements
    int num;        // Unique identifier
    static int count; // Static counter for matrix instances

public:
    // Default constructor - creates empty matrix
    matr() : n(0), m(0), a(nullptr) {
        num = ++count;
        cout << "Created matrix #" << num << " (default)" << endl;
    }

    // Parameterized constructor - creates matrix of given dimensions
    matr(int rows, int cols) : n(rows), m(cols) {
        a = new double*[n];  // Allocate row pointers
        for (int i = 0; i < n; i++) {
            a[i] = new double[m];  // Allocate each row
            for (int j = 0; j < m; j++) a[i][j] = 0; // Initialize to zero
        }
        num = ++count;
        cout << "Created matrix #" << num << " (" << n << "x" << m << ")" << endl;
    }

    // Copy constructor - creates copy of existing matrix
    matr(const matr& mat) : n(mat.n), m(mat.m) {
        a = new double*[n];  // Allocate row pointers
        for (int i = 0; i < n; i++) {
            a[i] = new double[m];  // Allocate each row
            for (int j = 0; j < m; j++) a[i][j] = mat.a[i][j]; // Copy elements
        }
        num = ++count;
        cout << "Created matrix #" << num << " (copy of matrix #" << mat.num << ")" << endl;
    }

    // Destructor - cleans up dynamically allocated memory
    ~matr() {
        if (a != nullptr) {  // Check if memory was allocated
            for (int i = 0; i < n; i++) delete[] a[i]; // Free each row
            delete[] a;  // Free row pointers
        }
        cout << "Destroyed matrix #" << num << endl;
    }

    // Assignment operator - copies matrix contents
    matr& operator=(const matr& mat) {
        cout << "Assignment: matrix #" << num << " = matrix #" << mat.num << endl;
        if (this != &mat) {  // Check for self-assignment
            // Free existing memory
            for (int i = 0; i < n; i++) delete[] a[i];
            delete[] a;

            // Copy dimensions and allocate new memory
            n = mat.n;
            m = mat.m;
            a = new double*[n];
            for (int i = 0; i < n; i++) {
                a[i] = new double[m];
                for (int j = 0; j < m; j++) a[i][j] = mat.a[i][j]; // Copy elements
            }
        }
        return *this;
    }

    // Matrix addition operator
    matr operator+(const matr& mat) {
        cout << "Addition: matrix #" << num << " + matrix #" << mat.num << endl;
        if (n != mat.n || m != mat.m) {  // Dimension check
            cerr << "Error: different matrix dimensions!" << endl;
            return matr();  // Return empty matrix if incompatible
        }
        matr res(n, m);  // Create result matrix
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                res.a[i][j] = a[i][j] + mat.a[i][j]; // Element-wise addition
        return res;
    }

    // Matrix subtraction operator
    matr operator-(const matr& mat) {
        cout << "Subtraction: matrix #" << num << " - matrix #" << mat.num << endl;
        if (n != mat.n || m != mat.m) {  // Dimension check
            cerr << "Error: different matrix dimensions!" << endl;
            return matr();
        }
        matr res(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                res.a[i][j] = a[i][j] - mat.a[i][j]; // Element-wise subtraction
        return res;
    }

    // Unary minus operator (matrix negation)
    matr operator-() {
        cout << "Unary minus: -matrix #" << num << endl;
        matr res(n, m);  // Create result matrix
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                res.a[i][j] = -a[i][j]; // Negate each element
        return res;
    }

    // Matrix multiplication operator
    matr operator*(const matr& mat) {
        cout << "Multiplication: matrix #" << num << " * matrix #" << mat.num << endl;
        if (m != mat.n) {  // Check for compatible dimensions
            cerr << "Error: incompatible matrix dimensions!" << endl;
            return matr();
        }
        matr res(n, mat.m);  // Result has rows of first, columns of second
        for (int i = 0; i < n; i++)
            for (int j = 0; j < mat.m; j++)
                for (int k = 0; k < m; k++)
                    res.a[i][j] += a[i][k] * mat.a[k][j]; // Dot product of row and column
        return res;
    }

    // Matrix-vector multiplication operator
    vect operator*(const vect& v) {
        cout << "Multiplication: matrix #" << num << " * vector #" << v.get_num() << endl;
        if (m != v.get_dim()) {  // Check for compatible dimensions
            cerr << "Error: incompatible dimensions!" << endl;
            return vect();
        }
        vect res(n);  // Result vector has size equal to matrix rows
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                res.set(i, res.get(i) + a[i][j] * v.get(j)); // Matrix-vector product
        return res;
    }

    // Friend function for scalar multiplication
    friend matr operator*(double k, const matr& mat);

    // Print matrix contents
    void print() {
        cout << "Matrix #" << num << " (" << n << "x" << m << "):" << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) cout << a[i][j] << " "; // Print each element
            cout << endl;
        }
    }

    // Getter methods
    int get_n() const { return n; }  // Returns number of rows
    int get_m() const { return m; }  // Returns number of columns
    int get_num() const { return num; }  // Returns matrix ID
    double get(int i, int j) const { return (i >= 0 && i < n && j >= 0 && j < m) ? a[i][j] : 0.0; } // Safe element access
    void set(int i, int j, double val) { if (i >= 0 && i < n && j >= 0 && j < m) a[i][j] = val; } // Safe element modification
};

// Initialize static counter
int matr::count = 0;

// Scalar multiplication for matrices (friend function implementation)
matr operator*(double k, const matr& mat) {
    cout << "Multiplication: " << k << " * matrix #" << mat.num << endl;
    matr res(mat.n, mat.m);  // Create result matrix
    for (int i = 0; i < mat.n; i++)
        for (int j = 0; j < mat.m; j++)
            res.set(i, j, k * mat.get(i, j)); // Multiply each element by scalar
    return res;
}

// Main function demonstrating vector and matrix operations
int main() {
    cout << "=== Vector demonstration ===" << endl;
    // Create two 3D vectors
    vect v1(3), v2(3);
    // Set vector elements
    v1.set(0, 1); v1.set(1, 2); v1.set(2, 3);
    v2.set(0, 4); v2.set(1, 5); v2.set(2, 6);

    cout << "\nInitial vectors:" << endl;
    v1.print();  // Print first vector
    v2.print();  // Print second vector

    cout << "\nVector operations:" << endl;
    vect v3 = v1 + v2;  // Vector addition
    v3.print();

    vect v4 = v1 - v2;  // Vector subtraction
    v4.print();

    vect v5 = -v1;  // Vector negation
    v5.print();

    double dot = v1 * v2;  // Dot product
    cout << "Dot product: " << dot << endl;

    vect v6 = 2.5 * v1;  // Scalar multiplication
    v6.print();

    cout << "\n=== Matrix demonstration ===" << endl;
    // Create 2x3 and 3x2 matrices
    matr m1(2, 3), m2(3, 2);
    // Set matrix elements
    m1.set(0, 0, 1); m1.set(0, 1, 2); m1.set(0, 2, 3);
    m1.set(1, 0, 4); m1.set(1, 1, 5); m1.set(1, 2, 6);

    m2.set(0, 0, 7); m2.set(0, 1, 8);
    m2.set(1, 0, 9); m2.set(1, 1, 10);
    m2.set(2, 0, 11); m2.set(2, 1, 12);

    cout << "\nInitial matrices:" << endl;
    m1.print();  // Print first matrix
    m2.print();  // Print second matrix

    cout << "\nMatrix operations:" << endl;
    matr m3 = m1 * m2;  // Matrix multiplication
    m3.print();

    matr m4 = -m1;  // Matrix negation
    m4.print();

    matr m5 = 0.5 * m2;  // Scalar multiplication
    m5.print();

    cout << "\nMatrix-vector multiplication:" << endl;
    vect v7 = m1 * v1;  // Matrix-vector product
    v7.print();

    return 0;
}
