#include <array>
#include <iostream>
#include <vector>

#define VALUES_SIZE 8

using namespace std;
using cousint = const unsigned int;


// vector<vector <cousint> makeAdjList(int*);
unsigned int maxValue(cousint, array<unsigned int, VALUES_SIZE>);

template<typename T>
inline T max(T& a, T& b) {
    return a > b? a : b;
}

int main() {
    array <unsigned int, VALUES_SIZE> values;
    for (unsigned int i = 0; i < values.size(); ++i) {
        unsigned int new_weight = 0;
        cin >> new_weight;
        values[i] = new_weight;
    }

    cout << max(maxValue(0, values), maxValue(1, values)) <<endl;

    return 0;
}

unsigned int maxValue(cousint index, array<unsigned int, VALUES_SIZE> values) {
    cousint first_neighbor = index + 2;
    cousint second_neighbor = index + 3;
    if (first_neighbor < values.size() && second_neighbor < values.size()) {
        return values[index] + max(maxValue(first_neighbor, values), maxValue(second_neighbor, values));
    } else if (first_neighbor < values.size() && second_neighbor >= values.size()) {
        return values[index] + maxValue(first_neighbor, values);
    } else if (first_neighbor >= values.size()) {
        return values[index];
    } else {
        return -1;
    }
    return -1;
}
