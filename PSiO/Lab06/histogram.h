#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <vector>

#include <map>

using Bin = int; // alias typu wartości dla przedziału histogramu
using Frequency = int; // alias typu wartości dla częstości wystąpień



class Histogram
{
    std::map<Bin, Frequency> bins;
    // std::map<int, int> bins; - rownowazne powyzszemu

    friend std::ostream& operator<<(std::ostream & out,
                                    const Histogram& histogram);

    friend std::ofstream& operator<<(std::ofstream & out,
                                    const Histogram& histogram);


    friend std::istream& operator>>(std::istream & in,
                                    Histogram& histogram);
public:
    Histogram();

    Histogram(const std::vector<int> &data);

    void emplace(int value);
    void emplace(const std::vector<int>& values);

    void clear();

    Histogram& operator<<(int value);

    const std::map<Bin, Frequency>& getBins() const { return bins; };

    std::pair<Bin, Bin> range() const;

};

//Histogram& operator<<(Histogram& histogram, int value);



#endif // HISTOGRAM_H
