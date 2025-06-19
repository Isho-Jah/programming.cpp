#include <iostream>   // Include library for input/output operations (cout, cin)
#include <cmath>      // Include math functions like sin, cos for rotation calculations

// Start of user-defined namespace to avoid name collisions
namespace usernamespace {

const double PI = 3.1415926535; // Define constant Pi for angle calculations

// Abstract base class representing a vertex (a point or similar element)
class Vertex {
public:
    virtual void draw() const = 0;          // Draw the vertex - must be implemented by derived classes
    virtual void erase() const = 0;         // Erase the vertex - must be implemented by derived classes
    virtual void move(double dx, double dy) = 0; // Move the vertex by dx and dy - must be implemented
    virtual void rotate(double angleDegrees) = 0; // Rotate the vertex around origin by angleDegrees - must be implemented
    virtual ~Vertex() {}                     // Virtual destructor for proper cleanup of derived classes
};

// Concrete class representing a point in 2D space, inherits from Vertex
class Point : public Vertex {
private:
    double x, y;                            // Coordinates of the point

public:
    // Constructor with default coordinates (0,0)
    Point(double x = 0, double y = 0) : x(x), y(y) {}

    double getX() const { return x; }      // Accessor for x coordinate
    double getY() const { return y; }      // Accessor for y coordinate

    // Print the point's coordinates to the console
    void draw() const override {
        std::cout << "Point: (" << x << ", " << y << ")\n";
    }

    // Print message that point is erased
    void erase() const override {
        std::cout << "Point erased\n";
    }

    // Move the point by dx and dy (translate coordinates)
    void move(double dx, double dy) override {
        x += dx;
        y += dy;
    }

    // Rotate the point around origin (0,0) by given angle in degrees
    void rotate(double angleDegrees) override {
        double rad = angleDegrees * PI / 180.0;  // Convert angle to radians for trig functions
        double newX = x * cos(rad) - y * sin(rad); // Apply 2D rotation formula for x
        double newY = x * sin(rad) + y * cos(rad); // Apply 2D rotation formula for y
        x = newX;                               // Update x coordinate
        y = newY;                               // Update y coordinate
    }
};

// Abstract base class for shapes (polygons, lines, etc.)
class Shape {
public:
    virtual void draw() const = 0;          // Draw the shape - must be implemented by derived classes
    virtual void erase() const = 0;         // Erase the shape - must be implemented
    virtual void move(double dx, double dy) = 0;  // Move shape by dx, dy - must be implemented
    virtual void rotate(double angle) = 0;  // Rotate shape by angle - must be implemented
    virtual ~Shape() {}                      // Virtual destructor for cleanup
};

// Class representing a line, derived from Shape
class Line : public Shape {
private:
    Point a, b;                             // Two endpoints of the line

public:
    // Constructor initializes the line with two points a and b
    Line(Point a, Point b) : a(a), b(b) {}

    // Draw line by drawing its endpoints (simplified)
    void draw() const override {
        std::cout << "Line from "; a.draw();
        std::cout << " to "; b.draw();
    }

    // Erase line by printing a message
    void erase() const override {
        std::cout << "Line erased\n";
    }

    // Move both endpoints by dx and dy
    void move(double dx, double dy) override {
        a.move(dx, dy);
        b.move(dx, dy);
    }

    // Rotate both endpoints by given angle around origin
    void rotate(double angle) override {
        a.rotate(angle);
        b.rotate(angle);
    }
};

// Class for quadrilaterals, inherits from Shape
class Quadrilateral : public Shape {
protected:
    Point p1, p2, p3, p4;                   // Four vertices of the quadrilateral

public:
    // Constructor initializes four points of the quadrilateral
    Quadrilateral(Point a, Point b, Point c, Point d)
        : p1(a), p2(b), p3(c), p4(d) {}

    // Draw all four vertices
    void draw() const override {
        std::cout << "Figure with vertices:\n";
        p1.draw(); p2.draw(); p3.draw(); p4.draw();
    }

    // Erase figure by printing a message
    void erase() const override {
        std::cout << "Figure erased\n";
    }

    // Move all four points by dx and dy
    void move(double dx, double dy) override {
        p1.move(dx, dy);
        p2.move(dx, dy);
        p3.move(dx, dy);
        p4.move(dx, dy);
    }

    // Rotate all four points around origin by angle degrees
    void rotate(double angle) override {
        p1.rotate(angle);
        p2.rotate(angle);
        p3.rotate(angle);
        p4.rotate(angle);
    }
};

// Square class inherits from Quadrilateral virtually to support multiple inheritance
class Square : virtual public Quadrilateral {
public:
    // Constructor creates square from origin point and size (length of side)
    Square(Point origin, double size)
        : Quadrilateral(
            origin,
            Point(origin.getX() + size, origin.getY()),
            Point(origin.getX() + size, origin.getY() + size),
            Point(origin.getX(), origin.getY() + size)) {}
};

// Rectangle class derived from Quadrilateral
class Rectangle : public Quadrilateral {
public:
    // Constructor creates rectangle from origin point, width, and height
    Rectangle(Point origin, double width, double height)
        : Quadrilateral(
            origin,
            Point(origin.getX() + width, origin.getY()),
            Point(origin.getX() + width, origin.getY() + height),
            Point(origin.getX(), origin.getY() + height)) {}
};

// Parallelogram class inherits Square virtually and redefines vertices
class Parallelogram : public Square {
public:
    // Constructor creates parallelogram with base, height, and horizontal offset for slant
    Parallelogram(Point origin, double base, double height, double offset)
        : Square(origin, base), // Initialize base square with base length
          Quadrilateral(
              origin,
              Point(origin.getX() + base, origin.getY()),
              Point(origin.getX() + base + offset, origin.getY() + height),
              Point(origin.getX() + offset, origin.getY() + height)) {}
};

} // end namespace usernamespace


int main() {
    setlocale(LC_ALL,"RU"); // Set locale for Russian output (not essential for logic)

    // Create a line using Point class within usernamespace
    usernamespace::Line l(usernamespace::Point(0, 0), usernamespace::Point(2, 2));
    l.draw();                      // Draw the line
    l.move(1, 1);                  // Move line by (1,1)
    l.rotate(45);                  // Rotate line 45 degrees around origin
    std::cout << "\nAfter move and rotation:\n";
    l.draw();                      // Draw the transformed line

    std::cout << "\n";

    // Create and draw a rectangle at origin (0,0) with width 4 and height 2
    usernamespace::Rectangle r(usernamespace::Point(0, 0), 4, 2);
    r.draw();

    std::cout << "\n";

    // Create and draw a parallelogram at origin with base=3, height=2, and offset=1
    usernamespace::Parallelogram p(usernamespace::Point(0, 0), 3, 2, 1);
    p.draw();

    return 0; // Exit the program
}

