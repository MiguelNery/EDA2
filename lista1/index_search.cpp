#include <iostream>
// #include <list>

using namespace std;

template <typename T>
struct node {
    T value = 0;
    node<T> *next = NULL;

    node(T value, node<T> *next) : value(value), next(next) { };

    ~node() {
        delete next;
    }
};

template <typename T>
struct list {

    int size = 0;
    node<T> *root = NULL;

    void push_front(T value) {
        node<T> *n = new node<T>(value, NULL);
        if (root) {
            n->next = root;
        }
        root = n;
        ++size;
    }

    void push_back(T value) {
        node<T> *n = new node<T>(value, NULL);

        if (root) {

            node<T> *buffer = root;
            while (buffer->next != NULL) {
                buffer = buffer->next;
            }
            buffer->next = n;
        } else {
            root = n;
        }
        ++size;
    }

    node<T> *pop_front() {
        if (root) {
            node<T> *n = root;
            root = n->next;
            n->next = NULL;

            return root;
        } else {
            return NULL;
        }
        --size;
    }

    node<T> *pop_back() {
        if (root) {
            node<T> *current = root;
            while (current->next != NULL) {
                current = current->next;
            }
            node<T> *n = current->next;
            current->next = NULL;

            return n;
        } else {
            return NULL;
        }
        --size;
    }

    node<T> *front() {
        return root;
    }

    node <T> *back() {
        node<T> *n = root;
        while (n && n->next) {
            n = n->next;
        }
        return n;
    }

    ~list() {
        delete root;
    }
};

void fill(list<int>& p, list<node<int> *>& q, int total_size, int p_index_interval) {

    for (int i = 0; i < total_size; ++i) {
        p.push_back(i);
        if (!(i % p_index_interval)) {
            auto e = p.back();
            q.push_back(e);
        }
    }
}

template <typename T>
node<T> *find(T value, list<T>& src, list<node<T> *> p_idxs) {

    node<int> *n = NULL;
    for (auto nn = p_idxs.front(); nn != NULL; nn = nn->next) {
        auto node_value = nn->value->value;
        if (value < node_value) {
            break;
        }
        n = nn->value;
    }

    printf("starting from: %d\n", n->value);
    bool found = false;
    for (int i = 0; n != NULL; n = n->next) {
        if (n->value == value) {
            found = true;
            break;
        }
    }

    return found ? n : NULL;
}
// Assumindo que um índice primário existe a cada 10 posições, segue a implementação.
int main() {

    list<int> numbers;
    list<node<int> *> primary_indexes;

    //simulando inserções:
    int size = 0;
    int gap = 0;
    printf("type list size: ");
    scanf(" %d", &size);

    printf("type primary index gap: ");
    scanf(" %d", &gap);

    int n = 0;
    printf("type number to find: ");
    scanf(" %d", &n);

    fill(numbers, primary_indexes, size, gap);

    auto found = find(n, numbers, primary_indexes);
    printf("found %p: %d\n", found, found->value);

    return 0;
}
