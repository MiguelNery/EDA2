#include <iostream>
#include <string>
#include <vector>


using namespace std;


bool equivalent(const int first_card, const int second_card) {
    return first_card == second_card;
}

/* Boyer-Moore vote algorithm*/
bool checkMajorityElement(vector<unsigned int> set) {
    /*find a candidade to majority element*/
    unsigned int count(0);
    unsigned int candidate(0);
    for (unsigned int i = 0; i < set.size(); ++i) {
        if (count == 0) {
            candidate = set[i];
            count = 1;
        } else {
            if (equivalent(candidate, set[i])) {
                ++count;
            } else {
                --count;
            }
        }
    }

    /*check if candidate is majority*/
    unsigned int ocurrences(0);
    for (unsigned int i = 0; i < set.size(); ++i) {
        if (equivalent(candidate, set[i])) {
            ++ocurrences;
        } else {/*donot*/}
    }

    return ocurrences > set.size() / 2 ? true : false;
}

int main() {
    vector<unsigned int> cards { 2, 2, 2, 3, 1, 2, 2, 6, 2, 8};
    string hue = checkMajorityElement(cards)? "fraud" : "everything is fine";
    cout << hue <<endl;

    return 0;
}
