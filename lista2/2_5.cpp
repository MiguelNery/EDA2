#include <iostream>
#include <random>

#define LIST_SIZE 15

using namespace std;

struct Node {
    const int value;
    Node* left;
    Node* right;

    Node(const int v,  Node* l) : value(v), left(l), right(NULL){}
    Node(const int v) : value(v), left(NULL), right(NULL){}

};

struct List {
    Node* front;
    Node* back;

    List() {
        fill();
    }

    bool empty() {
        if (!front) {
            return true;
        } else {
            return false;
        }
    }

    void fill() {
        random_device rd;
        mt19937 rng(rd());
        uniform_int_distribution<int> random_value(0, 99);
        front = new Node(random_value(rng));

        Node* last_node = front;
        for (int i = 0; i < LIST_SIZE; ++i) {
            Node* tail = new Node(random_value(rng), last_node);
            last_node->right = tail;
            last_node = tail;
        }
        back = last_node;
    }

    void print() {
        Node* aux = front;
        while (aux != NULL) {
            cout << aux->value << " ";
            aux = aux->right;
        }
        cout <<endl;
    }
};


int main() {
    List list = List();
    list.print();

    return 0;
}
