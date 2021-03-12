#include <iostream>
#include <vector>

#include <cmath>
//#include <math.h>



void foo(int *input, std::size_t n) {
    std::cout << "Size: " << n << '\n';

    std::sqrt(5.0f);

}

#if 0
void print(const std::vector<int> &input) {
    std::cout << "Size: " << input.size() << '\n';

    for (auto x : input) {
        std::cout << x << '\n';
    }
}
void print(const std::vector<float> &input) {
    std::cout << "Size: " << input.size() << '\n';

    for (auto x : input) {
        std::cout << x << '\n';
    }
}
#endif

template <typename T>
void print(const std::vector<T> &input) {
    std::cout << "Size: " << input.size() << '\n';
    for (auto x : input) {
        std::cout << x << '\n';
    }
}
/*
 * std::vector<int> vint;
 * print(vint); T <- int
 *
 * std::vector<float> vfloat;
 * print(vfloat); T <- float
 */

/*
 * signed/unsigned
 * char - 1B   (signed -127 ; 128) (unsigned 0; 255)
 * short - 2B  (signed -32768 - 32767) (unsigned 0; 65535)
 * int - 4B  - 32bit (signed - 2mld z hakiem; + 2 mld z hakiem) (unsigned 0; 4 mld z hakiem)
 * long  - 4B
 * long long - 8B - 64bit (signed -baaaardzo dużo; baaaaardzo duzo) (unsigned 0; baaaaaaaaaaaaaaaaaaaaaardzo dużo)
 * float - 4B
 * double - 8B
 * long double - 10B/16B
 *
 * 8086
 * 80286 - 286 - 16bit
 * 386,486 - 16bit?
 * 586 - Intel Pentium - 32bit
 * 686 - Pentium 2? 4?
 * x86
 * x86 std::size_t - unsigned int
 * x86-amd64 = x64 - 64bit
 * x64 std::size_t - unsigned long long
 * 16bit - unsigned short
 */

void print2(const std::vector<int> &input) {
    std::cout << "Size: " << input.size() << '\n';

    //size_t size; unsigned long long

    // input.size() == 7 mld (64bitowy)
    // 1. index (-2mld z hakiem; + 2mld z hakiem)
    // 2. index (0; + 4mld z hakiem)
    for (std::size_t index = 0; index < input.size(); ++index) {
        std::cout << input[index] << '\n';
    }
}

/*************************************************************/
/* Przekazywanie argumentow do funkcji:
*/
// - stała referencja - const&
// * nie robimy kopii
// * nie mozemy edytowac
// * do wgladu
// * przetwarzac/czytac/etc...
void  bar_cref(const std::vector<int>& input) {
    std::cout << input.size();

}
// Wyjatek:
// int, float, bool, short,
void bar_value(const int input) {
}




// - referencje
// * nie robimy kopii
// * mozemy modyfikowac
// * do wgladu
// * przetwarzac/czytac/etc...
void  bar_ref(std::vector<int> &input) {
    std::cout << input.size();

}

// - wartosc
// * mamy kopię
// * mozemy robic co chcemy, modyfikowac, usuwac, dodawac
// * oryginal nie jest zmieniony
void  bar_value(std::vector<int> input) {
    std::cout << input.size();

    input[2] /= 4;
    // do sth
}
// - wskaznik
void  bar_ptr(const std::vector<int> *input) {
    std::cout << input->size();
}




void bar() {

    std::vector<int> vec{1,2,3,4,5};
    bar_value(vec);
    bar_cref(vec);
    bar_ref(vec);
    bar_ptr(&vec);

}



/*************************************************************/

void Lab01() {
    std::cout << "Ahoj przygodo!!!" << std::endl;


    const std::size_t N = 5;
    int tab[N] = {1,2,3,4,5}; // tablica w stylu C
    foo(tab,N);


    std::size_t newN;
    std::cout << "Podaj rozmiar tablicy: ";
    std::cin >> newN;

    int defaultValue;
    std::cout << "Podaj domyślną wartość:";
    std::cin >> defaultValue;

//  int tabNew[newN]; // Błąd

//    int *tabNew = new int[newN];
//    tabNew[0] = 0;
//    delete[] tabNew;

    std::vector<int> vec(N);
    std::vector<int> vec2 = {1,2,3,4,5};
    std::vector<float> vec3(newN, std::sqrt(defaultValue));

    std::cout << "Vec3:\n";
    print(vec3);

    print(vec2);
    vec2.push_back(1337);
    print(vec2);

    vec2.emplace_back(2888);
    print(vec2);

    vec2.resize(10);
    print(vec2);
    vec2.resize(3);
    print(vec2);

    vec2.clear();
    print(vec2);

    std::cout << "Operator indeksowania:"<< vec2[3] << '\n';

}



void Lab02() {

    int x = 5;

    // C++ jest jezykiem statycznie typowanym
//    x = "Napis"; // blad kompilacji, nie mozna dokonac konwersji typow



    /*
    std::variant<int, std::string> y;
    std::any z;
    */

    int decision;
    std::cout << "podaj wybor:";
    std::cin >> decision;

    if (decision > 1337) {
        std::vector<float> vec(20, decision);
        print(vec);

    } else {
        std::vector<int> vec = {1,2,3,4,5};
        print(vec);
    }

}


int main()
{
   // Lab01();

    Lab02();

    return 0;
}
