#include <iostream>

using namespace std;

// Base class/struct
struct Shape {
        public:
                void setWidth(int w);
                void setHeight(int h) {
                        height = h;
                }

        protected:
                int width;
                int height;
};

void Shape::setWidth(int w) {
        width = w;
};

struct Fed {
        public:
                int what;
                void setWidth(int w) {
                        what = w;
                }
};

// Derived class/struct
struct Rectangle: public Shape {
        public:
                int getArea();
};

int Rectangle::getArea() {
        return (width * height);
}

struct Square: public Shape {
        public:
                int getArea() { 
                        return (width * height); 
                }
};

int main(void) {
        Square square;
        Rectangle Rect;
        Fed fed;

        Rect.setWidth(5);
        Rect.setHeight(7);

        square.setWidth(23);
        square.setHeight(23);

        fed.setWidth(23);

        // Print the area of the object.
        cout << "Total area of rectangle: " << Rect.getArea() << endl;
        cout << "Total area of square: " << square.getArea() << endl;

        cout << "Show what: " << fed.what << endl;

        return 0;
}