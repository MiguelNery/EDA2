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
int merge_sort(int *, int);
int join(int *, int *, int *, int, int);

int main(int argc, char **argv) {
    int size = 6;

    int unsorted[] = {3, 64, 10, 86, 77, 18} /* random_unsorted_array(size, 0, 100) */;
    printf("unsorted: ");
    for (int i = 0; i < size; ++i) {
        printf("%d ", unsorted[i]);
    } printf("\n");

    int inv = merge_sort(unsorted, size);

    printf("\nsorted: ");
    for (int i = 0; i < size; ++i) {
        printf("%d ", unsorted[i]);
    } printf("\n");

    printf("%d significant inversions\n", inv);

    // delete[] unsorted;
    return 0;
}

template <typename T>
void print_array(T *array, int size) {
    for (int i = 0; i < size; ++i) {
        cout << array[i] << " ";
    }
    cout << endl;
}

// Returns inversion count
int merge_sort(int *array, int count) {

    //split in 2
    int *a = array;
    int acount = count/2;

    int *b = array + acount;
    int bcount = count - acount;

    //sort left
    int left_inv = 0;
    int right_inv = 0;

    if (acount > 1) {
        left_inv = merge_sort(a, acount);
    }
    //sort right
    if (bcount > 1) {
        right_inv = merge_sort(b, bcount);
    }

    return left_inv + right_inv + join(array, a, b, acount, bcount);
}

// Returns inversion count
int join(int *dest, int *srca, int *srcb, int acount, int bcount) {

    int acc(0), bcc(0);
    int *daux = new int[acount + bcount];
    int inv = 0;

    print_array(srca, acount);
    print_array(srcb, bcount);

    for (int i = 0; i < acount + bcount; ++i) {
        if (acc < acount && bcc < bcount) {

            daux[i] = MIN(srca[acc], srcb[bcc]);
            if (mina) {
                ++acc;
            } else {
                if (srca[acc] > 2 * srcb[bcc]) {
                    inv += acount - acc;
                }
                ++bcc;
            }

        } else if (acc >= acount) {

            int count = bcount - bcc;
            memcpy(daux + i, srcb + bcc, sizeof(int) * (count));
            break;
        } else if (bcc >= bcount) {

            int count = acount - acc;
            memcpy(daux + i, srca + acc, sizeof(int) * (count));
            break;
        }
    }

    memcpy(dest, daux, (acount + bcount) * sizeof(int));
    delete[] daux;

    printf("%d significant inversions\n", inv);
    return inv;
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
