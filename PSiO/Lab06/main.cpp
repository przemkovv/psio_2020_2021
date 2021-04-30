
#include "histogram.h"

#include <vector>
#include <iostream>
#include <fstream>

int main () {

    Histogram hist; //Konstruktor domyślny

    Histogram hist_2(std::vector<int>({10,15,6,9,10,12})); // definiuje obiekt wywołując konstruktor inicjujący go listą wyników w punktach
    Histogram hist_3;


    hist.emplace(10); //dodaje ocenę 20pkt

    hist.emplace(std::vector<int>({10, 15, 6, 9, 10, 12}));

    hist << 10 << 12 << 20 << 21; // kolejne elementy zawierają punktację poszczególnych studentów

    // hist.operator<<(10).operator<<(12); // rownowazne powyzszemu


    std::cout << hist; // zapis histogramu do strumienia tekstowego

    std::cout << "Wypelnij histogram nowymi danymi\n";
//    std::cin >> hist; // pobiera dane od użytkownika (pobierając najpierw liczbę wyników, które chce wprowadzić)
    std::cout << hist; // zapis histogramu do strumienia tekstowego


    std::ofstream file("histogram.txt");
    file << hist; // zapis histogramu do pliku (identycznie jak dla wyświetlenia go na konsoli)
    file.close();

    /* Potencjalne wczytywanie z pliku danych w odpowiednim formacie
     */
    std::cout << "Wczytywanie ponowne\n";
    std::ifstream input_file("histogram.txt");
    if (input_file) {
        input_file >> hist_3;
        std::cout << "Kopia hist\n";
        std::cout << hist_3;
    }
    else {
        std::cout <<"Blad otwarcia pliku\n";
    }

    hist.clear(); //usuwa wszystkie dane z histogramu // jeśli dane nie zostaną usunięte kolejne wywołania operatora zapisu do strumienia lub

    std::cout << "<po czyszczeniu>\n";
    std::cout << hist; // zapis histogramu do strumienia tekstowego
    std::cout << "</po czyszczeniu>\n";

    hist_3.range();


#if 0
    hist.from_csv(R"(../wyniki.csv)", ',', 4); //wczytuje plik csv, argumentami są nazwa pliku, separator kolumn oraz index kolumny w której znajdują się dane dla histogramu



    using Bin = int; // alias typu wartości dla przedziału histogramu
    using Frequency = int; // alias typu wartości dla częstości wystąpień


    int freq = hist[10.5]; // zwraca częstość dla przedziału do którego należy wartość 10.5

    std::pair<Bin, Bin> range = hist.range(); // zwraca początkowy i końcowy przedział.

    std::pair<Bin, Frequency> max = hist.max(); // zwraca najczęściej występujący przedział oraz jego częstość

    std::vector<Bin> bins = hist.unique_bins(); // zwraca listę unikalnych, niepustych przedziałów

    std::vector<std::pair<Bin, Frequency>> items = hist.unique_items(); // zwraca listę niepustych przedziałów oraz częstość wystąpień

    //konwersja na inne typy
    using BinsVector = std::vector<std::pair<Bin, Frequency>>;
    BinsVector items_vect = static_cast<BinsVector>(hist); // operator rzutowania działa tak samo jak  Histogram::unique_items
    print(items_vect); // zewnętrzna funkcja wyświetlająca wektor elementów histogramu

#endif
}
