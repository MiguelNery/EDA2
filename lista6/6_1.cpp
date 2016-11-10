#include <array>
#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;
using cousint = const unsigned int;
const unsigned int VALUES_SIZE = 8;


// vector<vector <cousint> makeAdjList(int*);
unsigned int maxValue(cousint, array<unsigned int, VALUES_SIZE>);
unsigned int maxValue(array<unsigned int, VALUES_SIZE>);

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

    cout << maxValue(values) <<endl;
    // cout << max(maxValue(0, values), maxValue(1, values)) <<endl;

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

unsigned int maxValue(array<unsigned int, VALUES_SIZE> values) {
    array<unsigned int, values.size()> max_values = {};
    for(int i = values.size() - 1; i >= 0; --i) {
        unsigned int first_neighbor = i + 2;
        unsigned int second_neighbor = i + 3;
        printf("i: %d, first_neighbor: %d, second_neighbor: %d\n", i, first_neighbor, second_neighbor);
        if (first_neighbor < values.size() && second_neighbor < values.size()) {
            max_values[i] = values[i] + max(max_values[first_neighbor], max_values[second_neighbor]);
        } else if (first_neighbor < values.size() && second_neighbor >= values.size()) {
            max_values[i] =  values[i] + max_values[first_neighbor];
        } else if (first_neighbor >= values.size()) {
            max_values[i] = values[i];
        } else {/*donot*/}
    }

    return max(max_values[0], max_values[1]);
}
