
#include <iostream>


enum Kolory {
    Czarny,
    Rozowy,
    Niebieski
};

enum class Kolory2 {

    Bialy,
    Zielony,
    Czerwony

};



int main() {


    int x = Czarny;

    Kolory k = Czarny;


    // int y = Kolory2::Bialy; // blad kompilacji

    Kolory2 k2 = Kolory2::Czerwony;


    std::cout <<"Ahoj lab03\n";
}
