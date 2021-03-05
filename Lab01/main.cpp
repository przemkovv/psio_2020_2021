#include <iostream>
#include <vector>

void foo(int *input, std::size_t n) {
    std::cout << "Size: " << n << '\n';

}

void print(const std::vector<int> &input) {
    std::cout << "Size: " << input.size() << '\n';

    for (auto x : input) {
        std::cout << x << '\n';
    }
}

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

/* Przekazywanie parametrów do funkcji:
 - stała referencja - const&
 -
*/

int main()
{
    std::cout << "Ahoj przygodo!!!" << std::endl;


    const std::size_t N = 5;
    int tab[N] = {1,2,3,4,5}; // tablica w stylu C
    foo(tab,N);


    std::size_t newN;
    std::cout << "Podaj rozmiar tablicy: ";
    std::cin >> newN;

    int tabNew[newN]; // Błąd

//    int *tabNew = new int[newN];
//    tabNew[0] = 0;
//    delete[] tabNew;

    std::vector<int> vec(N);
    std::vector<int> vec2 = {1,2,3,4,5};
//    std::vector<int> vec3(newN);

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







    return 0;
}
