
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>


// alias na typ `std::vector<double`. Jest to ten sam typ, jednakze ma "przyjemniejsza" nazwę
// Polynomial przechowuje wspolczyniki wielomianu
using Polynomial = std::vector<double>;

// Przechowuje wartosci wielomianu
using PolynomialValues = std::vector<double>;

template <typename T>
void print(const std::vector<T> &input) {
    std::cout << "Size: " << input.size() << '\n';
    for (auto x : input) {
        std::cout << x << '\n';
    }
}

Polynomial get_poly(std::size_t n) {
    Polynomial coefficients(n);

    for(size_t index = 0; index < n; index++) {
        std::cout << "Podaj wspolczynnik i=" << index << ": ";
        std::cin >> coefficients[index];
    }
    return coefficients;

}


double poly(double x, const Polynomial &coefficients) {

    double result = 0;

    for (std::size_t index = 0; index < coefficients.size(); ++index) {
        result += coefficients[index] * std::pow(x, index);

    }
    return result;
}

bool are_signs_different(double x, double y) {
    return std::signbit(x) != std::signbit(y);
}

double zero_r(double bottom,  double top, const Polynomial& p) {
    const double epsilon = 1e-9;

    double x_begin = bottom;
    double x_mid = (bottom + top)/2.0;
    double x_end = top;

    double y_begin = poly(x_begin, p);
    double y_mid = poly(x_mid, p);
    double y_end = poly(x_end, p);

    if (top-bottom < epsilon) {
        return x_mid;
    } else if (are_signs_different(y_begin, y_mid)) {
       return zero_r(x_begin, x_mid, p);
    } else if (are_signs_different(y_mid, y_end)){
       return zero_r(x_mid, x_end, p);
    } else {
        std::cout << "To sie nie powinno wydarzyc\n";
        // brak wartosci zerowej
    }

    return 0.0;

}

PolynomialValues zero(const Polynomial &p, double x_min, double x_max, double step ) {
    PolynomialValues values;

    std::size_t steps_count = static_cast<std::size_t>((x_max - x_min) / step);

    for (std::size_t k = 0; k < steps_count; ++k) {

        double x1 = x_min + k * step;
        double x2 = x_min + (k+1) * step;

        double x1_value = poly(x1, p);
        double x2_value = poly(x2, p);

        if (are_signs_different(x1_value, x2_value)) {
//        if (std::signbit(x1_value) != std::signbit(x2_value)) {
            std::cout << "Miejsce zerowe w przedziale (" << x1<< "; " << x2<< ")\n";
            std::cout << "Miejsce zerowe w przedziale wartosci (" << x1_value << "; " << x2_value << ")\n";
            double x_zero = zero_r(x1, x2, p);
            values.push_back(x_zero);
        }
    }

    return values;
}

void zadanie10() {


    int n = 4;

//    std::vector<double> p = get_poly(n);

    Polynomial p = {1,2,-3,-4};

    std::cout << poly(-0.6, p) << '\n';
    std::cout << poly(1, p) << '\n';
    std::cout << poly(2, p) << '\n';
    std::cout << poly(2.5, p) << '\n';

    PolynomialValues zeros = zero(p, -2, 1, 0.1);

    std::cout <<"Wielomian: \n";
    print(p);

    std::cout <<"\nMiejsca zerowe: \n";
    print(zeros);


}

int main() {

//    std::fstream file("../kursy_usd_eur.csv", std::fstream::in);
//    if (file.is_open()) {
//        std::cout << "Ahoj z drugich laboratoriów\n";
//    }

    zadanie10();

}
