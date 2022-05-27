
#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle {
public:
    int foo();
};

template <typename T>
class Square {
public:
    T x;
    int foo();// { std::cout << "square T foo\n";}
};

#endif // RECTANGLE_H
