#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <map>

#define CHARVS 4096

using namespace std;

struct huffman {
    int value;
    char letter;

    huffman(int v, char l) : value(v), letter(l) { }

    void print() {
        if (letter != 0) {
            printf("%c: %d\n", letter, value);
        }
    }

    void print(string code) {
        if (letter != 0) {
            cout << code << ": " << letter << endl;
        }
    }
};

bool operator >(huffman a, huffman b) {
    return a.value > b.value;
}

bool operator <(huffman a, huffman b) {
    return a.value < b.value;
}

bool operator ==(huffman a, huffman b) {
    return a.value == b.value;
}

struct node {
    const node *left, *right;
    huffman value;

    node() : value(huffman(0, 0)), left(NULL), right(NULL) { }
    node(huffman v) : value(v), left(NULL), right(NULL) { }

    void set_value(huffman v) {
        memcpy(&value, &v, sizeof v);
    }

    void insert(const node *n) {
        if (this->left) {
            this->right = n;
        } else {
            this->left = n;
        }
    }

    void build_codes(map<char, string> &enc, const node *n, string code) {
        if (n->value.letter != 0) {
            enc.insert(pair<char, string>(n->value.letter, code));
            cout << n->value.letter << ": " << code << endl;
        }

        if (n->left) {
            build_codes(enc, n->left, code + '0');
        }

        if (n->right) {
            build_codes(enc, n->right, code + '1');
        }
    }
};

bool operator >(node a, node b) {
    return a.value > b.value;
}

bool operator <(node a, node b) {
    return a.value < b.value;
}

bool operator ==(node a, node b) {
    return a.value == b.value;
}

void huffmancode(char *);

int main(int argc, char **argv) {


    char stream1[] = "How i met your mother";
    huffmancode(stream1);

    char stream2[] = "Starcraft II";
    huffmancode(stream2);

    return 0;
}

void huffmancode(char *stream) {
    priority_queue<node, vector<node>, greater<node> > huffmans;

    int charvs[CHARVS];
    memset(charvs, 0, CHARVS * sizeof(int));

    string str(stream);
    for (int i = 0; i < str.length(); ++i) {
        char c = str.c_str()[i];
        charvs[c]++;
    }

    int qcount = 0;
    for (int i = 0; i < CHARVS; ++i) {
        int v = charvs[i];
        if (v > 0) {
            huffman h = huffman(v, i);
            node *n = new node(h);
            huffmans.push(*n);
            ++qcount;
        }
    }

    while (qcount > 1) {
        node *h1 = new node();
        auto h1v = huffmans.top();
        h1->set_value(h1v.value);
        h1->left = h1v.left;
        h1->right = h1v.right;
        huffmans.pop();

        node *h2 = new node();
        auto h2v = huffmans.top();
        h2->set_value(h2v.value);
        h2->left = h2v.left;
        h2->right = h2v.right;
        huffmans.pop();
        --qcount;

        huffman hn(h1->value.value + h2->value.value, 0);
        node *hnn = new node(hn);
        hnn->insert(h1);
        hnn->insert(h2);

        huffmans.push(*hnn);
    }

    auto hhx = huffmans.top();
    map<char, string> enc;
    hhx.build_codes(enc, &hhx, "");

    string code = "";
    for (int i = 0; i < str.length(); ++i) {
        char c = str.c_str()[i];
        string cc = enc[c];
        code += cc;
    }

    cout << code << endl;
}
