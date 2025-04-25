#include <iostream>  // Include library for input/output stream
#include <cmath>     // Include library for math functions (like sin, cos)
using namespace std; // Use the standard namespace to avoid prefixing std::

//
// Abstract base class "Point"
//
class Point {
protected:
    double x, y; // Coordinates of the point
public:
    // Constructor with default arguments
    Point(double x = 0, double y = 0) : x(x), y(y) {}

    // Pure virtual function to make the class abstract
    virtual void draw() const = 0;

    // Pure virtual function to define "erase" behavior
    virtual void erase() const = 0;

    // Virtual method to move the point
    virtual void move(double dx, double dy) {
        x += dx;
        y += dy;
        cout << "Moved to (" << x << ", " << y << ")" << endl;
    }

    // Pure virtual function to define rotation behavior
    virtual void rotate(double angle) = 0;

    // Virtual destructor
    virtual ~Point() {}
};

//
// Derived class "Line" inheriting from "Point"
//
class Line : public Point {
protected:
    double x2, y2; // Second endpoint of the line
public:
    // Constructor initializing both endpoints
    Line(double x1, double y1, double x2, double y2) : Point(x1, y1), x2(x2), y2(y2) {}

    // Draw the line
    void draw() const override {
        cout << "Drawing Line from (" << x << ", " << y << ") to (" << x2 << ", " << y2 << ")" << endl;
    }

    // Erase the line
    void erase() const override {
        cout << "Erasing Line" << endl;
    }

    // Move both endpoints
    void move(double dx, double dy) override {
        Point::move(dx, dy); // Move first endpoint
        x2 += dx;
        y2 += dy;
    }

    // Rotate second point around the first point
    void rotate(double angle) override {
        double rad = angle * M_PI / 180.0; // Convert angle to radians
        double dx = x2 - x;
        double dy = y2 - y;
        // Apply rotation formulas
        double newX = dx * cos(rad) - dy * sin(rad);
        double newY = dx * sin(rad) + dy * cos(rad);
        // Update second endpoint
        x2 = x + newX;
        y2 = y + newY;
        cout << "Rotated Line to new end point (" << x2 << ", " << y2 << ")" << endl;
    }
};

//
// Class "Parallelogram" with virtual inheritance from "Point"
//
class Parallelogram : virtual public Point {
protected:
    double width, height; // Width and height of the parallelogram
public:
    // Constructor
    Parallelogram(double x, double y, double w, double h) : Point(x, y), width(w), height(h) {}

    // Draw the parallelogram
    void draw() const override {
        cout << "Drawing Parallelogram at (" << x << ", " << y << ")" << endl;
    }

    // Erase the parallelogram
    void erase() const override {
        cout << "Erasing Parallelogram" << endl;
    }

    // Rotate the parallelogram
    void rotate(double angle) override {
        cout << "Rotating Parallelogram by " << angle << " degrees" << endl;
    }
};

//
// Class "Rectangle" inheriting from "Parallelogram"
//
class Rectangle : public Parallelogram {
public:
    // Constructor
    Rectangle(double x, double y, double w, double h) : Parallelogram(x, y, w, h) {}

    // Draw the rectangle
    void draw() const override {
        cout << "Drawing Rectangle at (" << x << ", " << y << ")" << endl;
    }

    // Erase the rectangle
    void erase() const override {
        cout << "Erasing Rectangle" << endl;
    }
};

//
// Class "Rhombus" inheriting from "Parallelogram"
//
class Rhombus : public Parallelogram {
public:
    // Constructor, takes diagonals as width and height
    Rhombus(double x, double y, double d1, double d2) : Parallelogram(x, y, d1, d2) {}

    // Draw the rhombus
    void draw() const override {
        cout << "Drawing Rhombus at (" << x << ", " << y << ")" << endl;
    }

    // Erase the rhombus
    void erase() const override {
        cout << "Erasing Rhombus" << endl;
    }
};

//
// Class "Square", using virtual inheritance to resolve "Diamond problem"
//
class Square : virtual public Parallelogram {
public:
    // Constructor: a square has equal width and height
    Square(double x, double y, double side) : Point(x, y), Parallelogram(x, y, side, side) {}

    // Draw the square
    void draw() const override {
        cout << "Drawing Square at (" << x << ", " << y << ")" << endl;
    }

    // Erase the square
    void erase() const override {
        cout << "Erasing Square" << endl;
    }
};

//
// Main function - testing polymorphism and virtual inheritance
//
int main() {
    Point* shapes[5]; // Array of pointers to Point (base class)

    // Instantiate various geometric shapes
    shapes[0] = new Line(0, 0, 3, 4);
    shapes[1] = new Rectangle(1, 1, 4, 2);
    shapes[2] = new Rhombus(2, 2, 5, 5);
    shapes[3] = new Square(0, 0, 3);
    shapes[4] = new Parallelogram(1, 1, 3, 4);

    // Loop through all shapes and perform actions
    for (int i = 0; i < 5; ++i) {
        shapes[i]->draw();         // Call draw function (demonstrates polymorphism)
        shapes[i]->move(1, 1);     // Move shape by (1,1)
        shapes[i]->rotate(45);     // Rotate shape by 45 degrees
        shapes[i]->erase();        // Erase shape
        cout << "-----------------------------" << endl;
    }

    // Clean up: delete all dynamically allocated shapes
    for (int i = 0; i < 5; ++i)
        delete shapes[i];

    return 0; // End of program
}
