#include <iostream>

#include "Rectangle.h"

struct VehicleStruct {
    int v;// pole publiczne

public:
    int x;

    void foo() {
        y = 3;
        std::cout << y << '\n';
        z = 4;
        std::cout << z << '\n';
    }

protected:
    int y;

private:
    int z;
};


class Vehicle {
    int v; // pole prywatne
private:
    int z;
public:
    int x;

    void foo() {
        y = 3;
        std::cout << y << '\n';
        z = 4;
        std::cout << z << '\n';

//        bar(); // blad kompilacji, rodzic nie ma dostepu do pol/atrybutów/funkcji klas podrzednych
    }

protected:
    int y;

};


class Car : public Vehicle {
public:
    int car_x;
    int bar() {
        car_x = 3;
        car_y = 2;
        car_z = 13;

        x = 39;
//        z = 3; // blad kompilacji, z jest prywatne w Vehicle
        y = 3;

        baz();

    }
protected:
    int car_y;

    void baz() {
        y = x;
    }
private:
    int car_z;
};

class Truck : public Car {
//class Truck : protected Car {
//class Truck : private Car {
public:
    void refill() {
        baz();
    }
};

class BigTruck : Car { // rownowazne class BigTruck : private Car

};

struct BigTruck2 : Car { // rownowazne struct BigTrucke2 : public Car

public:
protected:
private:
};


class Foo {
public:
    void foofoo() {}

    void bar() { std::cout << "inna\n";}
};

class BigTruck3 : public Car, public Foo {

};


int main() {

    Rectangle r;
    Square<int> s;

    r.foo();


    BigTruck3 t3;
    t3.foofoo();
//    t3.bar(); // blad kompilacji, wywolanie niejednoznaczne
    t3.Foo::bar(); // wywolanie bar z Foo
    t3.Car::bar();// wywolanie bar z Car



    Vehicle vehicle1; // Vehicle - klasa, vehicle1 - obiekt (instancja klasy)

    vehicle1.x = 5;
    std::cout << vehicle1.x << '\n';

    vehicle1.foo();

    Car car1;
    car1.x = 2;
    car1.car_x = 9;
    car1.bar();



//    vehicle1.y = 3; // blad kompilacji, pole chronione
//    vehicle1.z = 3; // blad kompilacji, pole prywatne


}
