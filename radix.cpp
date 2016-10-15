#include <iostream>
#include <stdio.h>
#include <cstring>

#define COUNTING_SIZE 10
#define UNSET -1

using ui = unsigned int;
using cousint = const unsigned int;

inline void swap(int& a, int& b) {
    int aux = a;
    a = b;
    b = aux;
}

inline int* copyArr(int* a, cousint size) {
    int* b = (int*) malloc(sizeof(int) * size);
    for(ui i = 0; i < size; i++) b[i] = a[i];
    return b;
}

void radixSort(int*, cousint, cousint, cousint);
int* countingSort(int*, cousint, cousint, cousint);
int getDigit(cousint, cousint);

//test
void bloodyFuck(int);

int main() {
    int unsorted[] = {34, 224, 421, 145, 564, 7234, 9234, 653, 4542, 335, 252, 1235, 652, 25};
    // int unsorted[] = {134, 224, 456, 123, 567};
    printf("unsorted = ");
    for(ui i = 0; i < 14; i++) printf("[%d] ", unsorted[i]);
    printf("\n");

    ui coefficient = 0;
    ui bot = 0, top = 0;
    scanf("%d %d %d", &bot, &top, &coefficient);
    radixSort(unsorted, bot, top, coefficient);
    // countingSort(unsorted, bot, top, coefficient);
    // printf("[%d]\n", getDigit(unsorted[1], coefficient));

    printf("sorted   = ");
    for(ui i = 0; i < 14; i++) printf("[%d] ", unsorted[i]);
    printf("\n");

    return 0;
}

int* countingSort(int* bucket, cousint bot, cousint top, cousint coefficient) {
    //counting how many of each number
    int index[COUNTING_SIZE];
    memset(index, 0, sizeof(int) * COUNTING_SIZE);
    for(ui i = bot; i <= top; i++) {
        ++index[getDigit(bucket[i], coefficient)];
    }
    // printf("index: ");
    // for(ui i = 0; i < COUNTING_SIZE; i++) printf("[%d] ", index[i]);
    // printf("\n");

    //determining sorted positions
    for(ui i = 1; i < COUNTING_SIZE; i++) {
        index[i] += index[i - 1];
    }
    // printf("posit: ");
    // for(ui i = 0; i < COUNTING_SIZE; i++) printf("[%d] ", index[i]);
    // printf("\n");

    int* return_buckets = copyArr(index, COUNTING_SIZE); //this will help split buckets


    // sorting bucket
    int* aux = copyArr(bucket, top - bot + 1); // aux keep original bucket values so bucket can be directly modified
    int j = 0;
    for(ui i = bot; i <= top ; i++) {
        int current = aux[top - j++]; //current number beeing ordered from bucket array
        int result_position = --index[getDigit(current, coefficient)]; //position in which 'current' will be put
        // printf("result_position: %d\n", result_position);
        bucket[result_position] = current;
    }

    return return_buckets;
}

int getDigit(cousint some_integer, cousint coefficient) {
    return (some_integer % coefficient) / (coefficient / 10);
}


void radixSort(int* unsorted, cousint bot, cousint top, cousint coefficient) {
    if (coefficient > 1) {
        countingSort(unsorted, bot, top, coefficient);
        int** buckets = (int**) malloc(sizeof(int*) * size)
        for(ui i = bot; i < top - bot + 1; i++) {
            int new_bot = 0;
            int new_top;

            if (i == 0) {
                new_bot = bot;
            } else {
                if (getDigit(buckets[i - 1], coefficient) < getDigit(buckets[i], coefficient)) {
                    new_bot = i;
                } else {/*donot*/}
            }

            if (i == top - 1) {
                new_top = buckets[i];
            } else {
                if (getDigit(buckets[i], coefficient) < getDigit(buckets[i + 1], coefficient)) {
                    new_top = i;
                } else {/*donot*/}
            }
                if (new_top - new_bot + 1 > 1) {
                    radixSort(unsorted, new_bot, new_top, coefficient / 10);
                } else {/*donot*/}
        }

        // printf("buckets (%d): ", coefficient);
        // for(ui i = 0; i < top - bot + 1; i++) printf("[%d] ", buckets[i]);
        // printf("\n");

        // for (ui i = 0; i < COUNTING_SIZE; i++) {
        //     int new_bot = 0;
        //     if (i == 0) {
        //         new_bot = bot;
        //     } else {
        //         new_bot = buckets[i - 1] == 0? buckets[i - 1] : buckets[i - 1] + 1;
        //         // new_bot = buckets[i - 1] + 1;
        //     }
        //
        //     int new_top = buckets[i] - 1;
        // }
    }
}

/*whatever*/
void bloodyFuck(int death) {
    int digit = 0;
    int coefficient = 10; // posição do dígito * 10.
    do {
        int something = death % coefficient; // corta o número a partir do dígito que interessa
        digit = something / (coefficient / 10);
        coefficient *= 10;

        if (digit > 0) {
            printf("%d\n", digit);
        } else {/*fock*/}
    } while(digit != 0);
}
