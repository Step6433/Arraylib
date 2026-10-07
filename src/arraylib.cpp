#include "arraylib.h"
#include <iostream>
#include <cstddef>
#include <algorithm>
#include <vector>


int arr_sum(const int* a, std::size_t n) {
    int s = 0;
    for (std::size_t i = 0; i < n; ++i) s += a[i];
    return s;
}

int arr_max(const int* a, std::size_t n) {
    int m = a[0];
    for (std::size_t i = 1; i < n; ++i) if (a[i] > m) m = a[i];
    return m;
}

int arr_min(const int* a, std::size_t n) {
    int m = a[0];
    for (std::size_t i = 1; i < n; ++i) if (a[i] < m) m = a[i];
    return m;
}

double arr_average(const int* a, std::size_t n) {
    int s = 0;
    return (arr_sum(a, n) * 1.0) / n; 
}

int arr_count_positive(const int* a, std::size_t n) {
    int s = 0;
    for (std::size_t i = 0; i < n; ++i) if (a[i] > 0) s++;
    return s;
}

int arr_count_negative(const int* a, std::size_t n) {
    int s = 0;
    for (std::size_t i = 0; i < n; ++i) if (a[i] < 0) s++;
    return s;
}

int arr_count_zero(const int* a, std::size_t n) {
    int s = 0;
    for (std::size_t i = 0; i < n; ++i) if (a[i] == 0) s++;
    return s;
}

int arr_product(const int* a, std::size_t n) {
    int s = 1;
    for (std::size_t i = 0; i < n; ++i) s *= a[i];
    return s;
}

double arr_median(const int* a, std::size_t n) {
    std::vector <int> b(a, a + n);
    std::sort(b.begin(), b.end());
    if (n % 2 == 0) return arr_average({b[(n / 2) - 1], b[n / 2]}, 2);
    else return b[n / 2];
}

