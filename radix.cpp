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

// void splitBuckets(int*, ui);
void countingSort(int*, cousint, cousint, cousint);
int getDigit(cousint, cousint);

//test
void bloodyFuck(int);

int main() {
    int unsorted[] = {34, 224, 421, 145, 564, 7234, 9234, 653, 43542, 335, 252, 1235, 652, 25};
    printf("unsorted = ");
    for(ui i = 0; i < 14; i++) {
        printf("[%d] ", unsorted[i]);
    }
    printf("\n");

    ui coefficient = 0;
    ui bot = 0, top = 0;
    scanf("%d %d %d", &bot, &top, &coefficient);
    countingSort(unsorted, bot, top, coefficient);
    // countingSort(unsorted, 0, 4, 1000);

    printf("sorted   = ");
    for(ui i = 0; i < 14; i++) {
        printf("[%d] ", unsorted[i]);
    }
    printf("\n");

    return 0;
}

void countingSort(int* bucket, cousint bot, cousint top, cousint coefficient) {
    //counting how many of each number
    int index[COUNTING_SIZE];
    memset(index, 0, sizeof(int) * COUNTING_SIZE);
    for(ui i = bot; i <= top; i++) {
        ++index[getDigit(bucket[i], coefficient)];
    }

    //determining sorted positions
    int positions[COUNTING_SIZE];
    for(ui i = 0; i < COUNTING_SIZE; i++) {
        if (i > 0) {
            positions[i] = index[i] + positions[i - 1];
        } else {
            positions[i] = bot + index[i] - 1; // the position on index '0' start at bottom of interval
        }
    }

    // sorting bucket
    int* aux = copyArr(bucket, 14); // aux keep original bucket values so bucket can be directly modified
    int j = 0;
    for(ui i = bot; i <= top ; i++) {
        int current = aux[top - j++]; //current number beeing ordered from bucket array
        // printf("current = %d // top = %d\n", top - j + 1, top);
        int result_position = positions[getDigit(current, coefficient)]--; //position in which 'current' will be put
        bucket[result_position] = current;
        // for(ui i = 0; i < 14; i++) printf("[%d] ", bucket[i]);
        // printf("\n");
    }
}

int getDigit(cousint some_shit, cousint coefficient) {
    return (some_shit % coefficient) / (coefficient / 10);
}


// void splitBuckets(int* unsplit, ui size) {
//     int coefficient = 10000;
//     int* buckets = countingSort()
//
//     while(coefficient > 1) {
//
//     }
//
// }

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
