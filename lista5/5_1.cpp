#include <iostream>
#include <random>

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

using namespace std;

void fill_random_ordered_array(int count, int* array);
void join(int *dest, int *srca, int *srcb, int acount, int bcount);

int main() {
    int count = 10;
    int *a = new int[count];
    int *b = new int[count]; //two data sets
    fill_random_ordered_array(count, a);
    fill_random_ordered_array(count, b);

    for (int i = 0; i < count; ++i) {
        printf("%d\t%d\n", a[i], b[i]);
    }

    int *joined = new int[count * 2];
    join(joined, a, b, count, count);

    for (int i = 0; i < count * 2; ++i) {
        printf("%d ", joined[i]);
    } printf("\n");

    double med = ((double)joined[count] + (double)joined[1 + count])/2;
    printf("med = %.2lf\n", med);

    delete[] a;
    delete[] b;
    delete[] joined;

    return 0;
}

void join(int *dest, int *srca, int *srcb, int acount, int bcount) {
    int acc(0), bcc(0);
    int *daux = new int[acount + bcount];

    for (int i = 0; i < acount + bcount; ++i) {
        if (acc < acount && bcc < bcount) {
            daux[i] = MIN(srca[acc], srcb[bcc]);
            acc += (int)mina;
            bcc += (int)!mina;
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
}

void fill_random_ordered_array(int count, int* array) {
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> uni(1, 5);

    int n = uni(rng);
    for (int i = 0; i < count; ++i) {
        array[i] = n;
        n += uni(rng);
    }
}
