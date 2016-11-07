#include <iostream>
#include <queue>

using namespace std;

void get_recs(string& source, queue<string>& dest);
string getline();
template <typename T>
T dequeue(queue<T>& queue);

int main() {

    string s, s_sub;
    s = getline();
    s_sub = getline();

    queue<string> s_v;
    queue<string> sub_v;

    get_recs(s, s_v);
    get_recs(s_sub, sub_v);

    auto subi = sub_v.front();
    auto si = s_v.front();

    bool is_sub = false;
    while (!(sub_v.empty() && s_v.empty())) {

        if (!subi.compare(si)) {
            sub_v.pop();
            subi = sub_v.front();
        }

        s_v.pop();
        si = s_v.front();

        if (sub_v.empty()) {
            is_sub = true;
            break;
        }

        if (s_v.empty()) {
            is_sub = false;
            break;
        }
    }

    if (is_sub) {
        printf("S' is a subsequence of S\n");
    } else {
        printf("S' is not a subsequence of S\n");
    }


    return 0;
}

void get_recs(string& source, queue<string>& dest) {
    string it_buffer;
    int source_len = source.length();
    for (int i = 0; i < source_len; ++i) {
        char it = source[i];
        if (it != ',') {
            it_buffer += it;
        } else {
add_rec:
            dest.push(it_buffer);
            it_buffer = string();
            ++i;
            continue;
        }

        if (i == source_len - 1) {
            goto add_rec;
        }
    }
}

string getline() {
    string line;
    char c = 0;
    while ((c = getchar()), c != '\n') {
        line += c;
    }

    return line;
}
