#include <iostream>  // For console input/output
#include <cmath>     // For math functions like sin() and cos()
using namespace std; // So we don't need to type std:: everywhere

/*
* The base Point class - abstract since it contains pure virtual methods
* Represents a basic point in 2D space
*/
class Point {
protected:
    double x, y; // The point coordinates
public:
    // Sets up the point at given coordinates (default is origin)
    Point(double x = 0, double y = 0) : x(x), y(y) {}

    // These must be implemented by any class that inherits from Point
    virtual void draw() const = 0;   // How to draw this shape
    virtual void erase() const = 0;  // How to erase this shape

    // Moves the point by the given amounts
    virtual void move(double dx, double dy) {
        x += dx;
        y += dy;
        cout << "Moved shape to (" << x << ", " << y << ")" << endl;
    }

    // How to rotate the shape (must be implemented by child classes)
    virtual void rotate(double angle) = 0;

    // Virtual destructor ensures proper cleanup
    virtual ~Point() {}
};

/*
* Line class - represents a line segment between two points
* Inherits from Point (first endpoint) and stores second endpoint
*/
class Line : public Point {
protected:
    double x2, y2; // The second endpoint
public:
    // Creates a line from (x1,y1) to (x2,y2)
    Line(double x1, double y1, double x2, double y2) 
        : Point(x1, y1), x2(x2), y2(y2) {}

    // Shows the line on screen
    void draw() const override {
        cout << "Drawing line from (" << x << "," << y 
             << ") to (" << x2 << "," << y2 << ")" << endl;
    }

    // Clears the line from screen
    void erase() const override {
        cout << "Clearing line from (" << x << "," << y 
             << ") to (" << x2 << "," << y2 << ")" << endl;
    }

    // Shifts the entire line by (dx,dy)
    void move(double dx, double dy) override {
        Point::move(dx, dy); // Move first point
        x2 += dx; // Move second point
        y2 += dy;
    }

    // Rotates the second point around the first point
    void rotate(double angle) override {
        // Convert angle to radians for math functions
        double radians = angle * M_PI / 180.0;
        
        // Calculate offset from rotation center
        double dx = x2 - x;
        double dy = y2 - y;
        
        // Apply rotation formulas
        double newX = dx * cos(radians) - dy * sin(radians);
        double newY = dx * sin(radians) + dy * cos(radians);
        
        // Update second point position
        x2 = x + newX;
        y2 = y + newY;
        
        cout << "Rotated line to new endpoint (" << x2 << "," << y2 << ")" << endl;
    }
};

/*
* Parallelogram class - base for several quadrilateral shapes
* Uses virtual inheritance to prevent issues with multiple inheritance
*/
class Parallelogram : virtual public Point {
protected:
    double width, height; // The base and height measurements
public:
    // Creates parallelogram at (x,y) with given dimensions
    Parallelogram(double x, double y, double w, double h) 
        : Point(x, y), width(w), height(h) {}

    // Displays the parallelogram
    void draw() const override {
        cout << "Drawing parallelogram at (" << x << "," << y 
             << ") with width " << width << " and height " << height << endl;
    }

    // Removes the parallelogram from display
    void erase() const override {
        cout << "Removing parallelogram" << endl;
    }

    // Rotates the shape (simplified for this example)
    void rotate(double angle) override {
        cout << "Rotating parallelogram by " << angle << " degrees" << endl;
    }
};

/*
* Rectangle class - special case of parallelogram
* Inherits all functionality but can have its own specific behaviors
*/
class Rectangle : public Parallelogram {
public:
    // Creates rectangle with given position and dimensions
    Rectangle(double x, double y, double w, double h) 
        : Parallelogram(x, y, w, h) {}

    // Rectangle-specific drawing
    void draw() const override {
        cout << "Drawing rectangle at (" << x << "," << y 
             << ") sized " << width << "x" << height << endl;
    }

    // Rectangle-specific erase
    void erase() const override {
        cout << "Clearing rectangle from screen" << endl;
    }
};

/*
* Rhombus class - another parallelogram specialization
* Both pairs of sides equal length
*/
class Rhombus : public Parallelogram {
public:
    // Creates rhombus with given diagonals
    Rhombus(double x, double y, double d1, double d2) 
        : Parallelogram(x, y, d1, d2) {}

    // Rhombus display
    void draw() const override {
        cout << "Drawing rhombus at (" << x << "," << y 
             << ") with diagonals " << width << " and " << height << endl;
    }

    // Rhombus removal
    void erase() const override {
        cout << "Erasing rhombus from display" << endl;
    }
};

/*
* Square class - special case of both rectangle and rhombus
* Uses virtual inheritance to avoid "diamond problem"
*/
class Square : virtual public Parallelogram {
public:
    // Creates square with equal sides
    Square(double x, double y, double side) 
        : Point(x, y), Parallelogram(x, y, side, side) {}

    // Square rendering
    void draw() const override {
        cout << "Drawing square at (" << x << "," << y 
             << ") with side length " << width << endl;
    }

    // Square clearing
    void erase() const override {
        cout << "Removing square from view" << endl;
    }
};

// Main program to test our geometry classes
int main() {
    // Array to hold different shapes (all treated as Points)
    Point* shapes[5];

    // Create one of each shape type
    shapes[0] = new Line(0, 0, 3, 4);          // Simple line
    shapes[1] = new Rectangle(1, 1, 4, 2);     // 4x2 rectangle
    shapes[2] = new Rhombus(2, 2, 5, 5);       // Rhombus with equal diagonals
    shapes[3] = new Square(0, 0, 3);           // 3x3 square
    shapes[4] = new Parallelogram(1, 1, 3, 4); // Generic parallelogram

    // Demonstrate each shape's capabilities
    for (int i = 0; i < 5; ++i) {
        shapes[i]->draw();    // Show the shape
        shapes[i]->move(1, 1); // Move it right and up
        shapes[i]->rotate(45); // Give it a 45 degree turn
        shapes[i]->erase();    // Clear it from screen
        cout << "------------------------------------" << endl;
    }

    // Clean up all allocated memory
    for (int i = 0; i < 5; ++i) {
        delete shapes[i];
    }

    return 0;
}
