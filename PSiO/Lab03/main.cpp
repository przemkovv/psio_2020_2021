
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <iterator>

/*
 * (((\w+),? ?)+\.)   - zdania
 * (( ?(\w+)[ ,]?)+\.)  - wyrazy
 */

enum Kolory {
    Czarny,
    Rozowy,
    Niebieski
};

enum class Kolory2 {

    Bialy,
    Zielony,
    Czerwony,
    Pomaranczowy

};

enum class SwordType { Bastard, Great, Short, Katana };
struct Sword {
    SwordType type;
    float length;
};

std::ostream& operator<<(std::ostream& out, const Sword& sword){
    return out << "sword type: " << static_cast<int>(sword.type) << ", length: " << sword.length << '\n';
}

template <typename T>
void print(const std::vector<T> &input) {
    std::cout << "Size: " << input.size() << '\n';
    for (auto x : input) {
        std::cout << x << '\n';
    }
}

void intro_enum(){
    int x = Czarny;

    Kolory k = Czarny;


    // int y = Kolory2::Bialy; // blad kompilacji

    Kolory2 k2 = Kolory2::Czerwony;

}

bool compare_swords(const Sword& s1, const Sword& s2){
    return s1.length < s2.length;
}


void intro_lambda() {

    /*
     *    [<capture list>](<parametry>){<blok instrukcji>}
     */

    [](){}; // rownowazne empty_function

    [](Kolory2 kolor) {
        return kolor == Kolory2::Pomaranczowy || kolor == Kolory2::Czerwony;
    };  // rownowazne funkcji favourite_colors

    [](Kolory2 kolor) -> bool {
        return kolor == Kolory2::Pomaranczowy || kolor == Kolory2::Czerwony;
    };  // rownowazne funkcji favourite_colors

    auto favourite_colors2 = [](Kolory2 kolor) -> bool {
        return kolor == Kolory2::Pomaranczowy || kolor == Kolory2::Czerwony;
    };  // rownowazne funkcji favourite_colors
    if (favourite_colors2(Kolory2::Pomaranczowy)) {
        std::cout << "Pomaranczowy to jest moj ulubiony kolor\n";
    }

    bool favourite_colors3 = [](Kolory2 kolor) -> bool {
        return kolor == Kolory2::Pomaranczowy || kolor == Kolory2::Czerwony;
    };  // niejawne rzutowanie wskaznika na funkcje na wartosc boolowska <- w 99.999999% niepoprawne

    /* nie kompiluje, gdyz favourite_colors3 jest typu bool a nie typu funkcyjnego
    if (favourite_colors3(Kolory2::Pomaranczowy)) {
        std::cout << "Pomaranczowy to jest moj ulubiony kolor\n";
    }
    */


    std::vector<int> vec {182, 12, 1,2,3,4,1, 127};
    print(vec);

    std::sort(vec.begin(), vec.end());
    std::cout << "Posortowany\n";
    print(vec);
    std::sort(vec.begin(), vec.end(),
      [](int x1, int x2){
        return x2 < x1;
    });
    std::cout << "Posortowany inaczej\n";
    print(vec);


    std::vector<Sword> swords {
        { SwordType::Bastard, 10},
        { SwordType::Great, 15},
        { SwordType::Short, 5},
        { SwordType::Katana, 12},
        { SwordType::Short, 6},
    };

    print(swords);

    std::sort(swords.begin(), swords.end(),
      [](const Sword& s1, const Sword& s2){
         return s1.length < s2.length;
      }
    );
    print(swords);
    std::sort(swords.begin(), swords.end(), compare_swords); // rownowazne wersji wyzej
    print(swords);


    std::list<Sword> swords_list {
        { SwordType::Bastard, 10},
        { SwordType::Great, 15},
        { SwordType::Short, 5},
        { SwordType::Katana, 12},
        { SwordType::Short, 6},
    };
    // swords[0]; // blad -> uzytkownik moglby blednie zalozyc ze jest to operacja efektywna o zlozonosci O(1), gdzie jest O(n)

}

void empty_function(){

}

bool favourite_colors(Kolory2 kolor) {
        return kolor == Kolory2::Pomaranczowy || kolor == Kolory2::Czerwony;
}


void algorithms() {
    std::vector<Sword> swords {
        { SwordType::Bastard, 10},
        { SwordType::Great, 15},
        { SwordType::Short, 5},
        { SwordType::Katana, 12},
        { SwordType::Short, 6},
    };

    print(swords);


    if (std::any_of(swords.begin(), swords.end(), [](const Sword& sword) {
                return sword.type == SwordType::Short;
        })) {
        std::cout << "Mamy miecz krotki\n";
    }

    {
        bool found = false;
        for (auto swordIt = swords.begin(); swordIt != swords.end(); ++swordIt) {
            if (swordIt->type == SwordType::Short) {
                found = true;
                break;
            }
        }
        if (found) {
            std::cout << "Mamy miecz krotki\n";
        }
    }


    // wykorzystanie operatora indeksowania
    for (std::size_t index = 0; index < swords.size(); ++index) {
        std::cout << swords[index] <<'\n';
    }

    // wykorzystanie iteratorow
    for (auto swordIt = swords.begin(); swordIt	 != swords.end(); ++swordIt) {
        std::cout << *swordIt << '\n';
    }

    std::cout << "Copy\n";
    std::copy_if(swords.begin(), swords.end(),
              std::ostream_iterator<Sword>(std::cout, "\n"),
              [](const Sword& sword) {
                return sword.type == SwordType::Short;
            });




}

int main() {

    intro_enum();
    intro_lambda();

    algorithms();




    std::cout <<"Ahoj lab03\n";
}
