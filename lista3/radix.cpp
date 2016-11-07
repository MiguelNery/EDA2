/*INSTRUÇÕES
Funciona com inteiros num intervalo de "menor inteiro na sua máquina" até 1000000
NÃO funciona com negativos
PARA COMPILAR: g++ radix.cpp -std=c++11
PARA EXECUTAR: ./a.out < radix_input.txt
dentro de radix_input.txt:
    o primeiro número, N (inteiro), representa a quantidade de elementos desordenados
    os próximos N inteiros são os elementos desordenados
*/

#include <iostream>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <algorithm>

#define COUNTING_SIZE 10
#define COEFFICIENT 1000000

using ui = unsigned int;
using cousint = const unsigned int;

std::vector<int> radixSort(std::vector<int>, cousint);
void countingSort(std::vector<int>&, cousint);
int getDigit(cousint, cousint);

int main() {
    std::vector<int> unsorted;

    ui size = 0;
    scanf("%u", &size);
    for(ui i = 0; i < size; i++) {
        int some_integer = 0;
        scanf("%d", &some_integer);
        unsorted.push_back(some_integer);
    }
    printf("sorted = ");
    for(ui i = 0; i < unsorted.size(); i++) printf("[%d] ", unsorted[i]);
    printf("\n");

    std::vector<int> sorted = radixSort(unsorted, COEFFICIENT);

    printf("sorted = ");
    for(ui i = 0; i < unsorted.size(); i++) printf("[%d] ", sorted[i]);
    printf("\n");

    return 0;
}

int getDigit(cousint some_integer, cousint coefficient) {
    return (some_integer % coefficient) / (coefficient / 10);
}

void countingSort(std::vector<int>& bucket, cousint coefficient) {
    //counting how many of each number
    int index[COUNTING_SIZE];
    memset(index, 0, sizeof(int) * COUNTING_SIZE);
    for(ui i = 0; i <= bucket.size(); i++) {
        ++index[getDigit(bucket[i], coefficient)];
    }
    //determining sorted positions
    for(ui i = 1; i < COUNTING_SIZE; i++) {
        index[i] += index[i - 1];
    }

    // sorting bucket
    std::vector<int> aux (bucket.size());
    std::copy(bucket.begin(), bucket.end(), aux.begin());
    int j = 1;
    for(ui i = 0; i < bucket.size(); i++) {
        int current = aux[bucket.size() - j++]; //current number beeing ordered from bucket array
        int result_position = --index[getDigit(current, coefficient)] - 1; //position in which 'current' will be put
        bucket[result_position] = current;
    }
}



std::vector<int> radixSort(std::vector<int> unsorted, cousint coefficient) {
    if (unsorted.size() > 1 && coefficient > 1) {
        std::vector<int> buckets[10];
        std::vector<int> sorted;

        // spliting into buckets
        for(ui i = 0; i < unsorted.size(); i++) {
            buckets[getDigit(unsorted[i], coefficient)].push_back(unsorted[i]);
        }

        // sorting buckets
        for(ui i = 0; i < 10; i++) {
            if (buckets[i].size() > 1) {
                countingSort(buckets[i], coefficient);
                buckets[i] = radixSort(buckets[i], coefficient / 10);
            } else {/*donot*/}
        }

        // storing result
        for(ui i = 0; i < 10; i++) {
            for(ui j = 0; j < buckets[i].size(); j++) {
                sorted.push_back(buckets[i][j]);
            }
        }
        return sorted;
    } else {
        return unsorted;
    }
}
