#include <iostream>

// a shape is a thing that has an area
class Shape {
public:
    virtual float area() = 0;
};

// A circle is a shape
class Circle : public Shape {
public:
    Circle(float radius) {
        r = radius;
    }
    virtual float area() {
        return 3.14 * r * r;
    }
private:
    float r;
};

// A square is also a shape
class Square : public Shape {
public:
    Square(float side) {
        s = side;
    }
    virtual float area() {
        return s * s;
    }
private:
    float s;
};

// Polymorphism
// Poly - many
// Morph - shape
// ism - just cause
int main () {
    // Declared type differs from the instantiated type
//    Shape * shape = new Shape();
    Shape * square = new Square(5);
    Shape * circle = new Circle(3);
//    std::cout << shape->area() << std::endl;
    std::cout << square->area() << std::endl;
    std::cout << circle->area() << std::endl;
    return 0;
}