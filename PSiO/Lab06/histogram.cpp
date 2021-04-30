#include "histogram.h"

#include <iostream>
#include <fstream>
#include <numeric>
#include <algorithm>

// https://xkcd.com/303/
Histogram::Histogram()
{

}

Histogram::Histogram(const std::vector<int> &data) {

    for (const auto value : data) {
        bins[value]++;
    }
}

void Histogram::emplace(int value){
    bins[value]++;
}

void Histogram::emplace(const std::vector<int>& values){
    for (const auto value : values) {
        bins[value]++;
    }
}
Histogram& Histogram::operator<<(int value) {
    emplace(value);
    return *this;
}
// rownowazne powyzszemu, lecz zaimplementowane jako funkcja wolna
//Histogram& operator<<(Histogram& histogram, int value) {
//    histogram.emplace(value);
//    return histogram;
//}

std::ostream& operator<<(std::ostream & out, const Histogram& histogram) {
    out << "Size: " << histogram.bins.size() << '\n';
    for(auto [bin, frequency] : histogram.bins) {
        out << bin << ": " << frequency <<'\n';
    }
    return out;
}

std::ofstream& operator<<(std::ofstream & out, const Histogram& histogram) {
    int element_count = std::accumulate(histogram.bins.begin(),
                                        histogram.bins.end(),
                                        0,
                                        [](int x, const std::pair<Bin, Frequency>& koszyk){
                                            return x + koszyk.second;
                                        });
    out << element_count << '\n';

    for(auto [bin, frequency] : histogram.bins) {
        while (frequency--) {
            out << bin  <<'\n';
        }
    }
    return out;
}


/* Przykładowe wejscie do wczytywania histogramu
5
42
1337
42
1337
4
 */

std::istream& operator>>(std::istream & in,
                         Histogram& histogram) {
    std::size_t n;
    in >> n;
    for (std::size_t index = 0; index < n; ++index) {
        int value;
        in >> value;
        histogram.emplace(value);
    }
    return in;
}



void Histogram::clear() {
   bins.clear();
}

std::pair<Bin, Bin> Histogram::range() const {

    using bin_pair = std::pair<Bin, Frequency>;
    auto [min_it, max_it] = std::minmax_element(bins.begin(),
                     bins.end(),
                     [](const bin_pair& p1, const bin_pair& p2) {
                        return p1.first < p2.first;
    });
    std::cout << min_it->first << ": " << min_it->second << '\n';
    std::cout << max_it->first << ": " << max_it->second << '\n';

    return {};

}


















