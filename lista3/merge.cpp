#include <iostream>
#include <cstring>
#include <random>
#include <stdio.h>

using namespace std;

bool maxa;
bool mina;

template <typename T>
T MAX(T a, T b) {
    maxa = a >= b;
    return a >= b ? a : b;
}

template <typename T>
T MIN(T a, T b) {
    mina = a <= b;
    return a <= b ? a : b;
}

int *random_unsorted_array(int, int, int);
void merge_sort(int *, int);
void join(int *, int *, int *, int, int);

int main(int argc, char **argv) {
    int size = 20;

    int *unsorted = random_unsorted_array(size, 0, 100);
    for (int i = 0; i < size; ++i) {
        printf("%d ", unsorted[i]);
    } printf("\n");
    printf("\n");

    merge_sort(unsorted, size);

    for (int i = 0; i < size; ++i) {
        printf("%d ", unsorted[i]);
    } printf("\n");

    delete[] unsorted;
    return 0;
}

void merge_sort(int *array, int count) {
    //split in 2
    int *a = array;
    int acount = count/2;

    int *b = array + acount;
    int bcount = count - acount;

    printf("\nspliting array: \n");
    for(int i = 0; i < count; i++) printf("[%d] ", array[i]);
    printf("\ninto:\n");

    printf("left half: ");
    for(int i = 0; i < acount; i++) printf("[%d] ", array[i]);
    printf("\n");

    printf("right half: ");
    for(int i = acount; i < count; i++) printf("[%d] ", array[i]);
    printf("\n");

    //sort left
    if (acount > 1) {
        merge_sort(a, acount);
    }
    //sort right
    if (bcount > 1) {
        merge_sort(b, bcount);
    }
    join(array, a, b, acount, bcount);

}

void join(int *dest, int *srca, int *srcb, int acount, int bcount) {
    printf("\nleft half: ");
    for(int i = 0; i < acount; i++) printf("[%d] ", srca[i]);
    printf("\n");

    printf("right half: ");
    for(int i = 0; i < bcount; i++) printf("[%d] ", srcb[i]);
    printf("\n");

    int acc(0), bcc(0);
    int *daux = new int[acount + bcount];

    for (int i = 0; i < acount + bcount; ++i) {
        if (acc < acount && bcc < bcount) {
            printf("comparing (left)%d & %d(right)... %d chosen!\n", srca[acc], srcb[bcc], MIN(srca[acc], srcb[bcc]));
            daux[i] = MIN(srca[acc], srcb[bcc]);
            acc += (int)mina;
            bcc += (int)!mina;
        } else if (acc >= acount) {
            printf("<><>left side empty. dumping right side...\n");
            int count = bcount - bcc;
            memcpy(daux + i, srcb + bcc, sizeof(int) * (count));
            break;
        } else if (bcc >= bcount) {
            printf("<><>right side empty. dumping left side...\n");
            int count = acount - acc;
            memcpy(daux + i, srca + acc, sizeof(int) * (count));
            break;
        }
    }

    memcpy(dest, daux, (acount + bcount) * sizeof(int));
    delete[] daux;
}

int *random_unsorted_array(int count, int min, int max) {
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> uni(min, max);

    int *unsorted = new int[count];
    for (int i = 0; i < count; ++i) {
        unsorted[i] = uni(rng);
    }

    return unsorted;
}
