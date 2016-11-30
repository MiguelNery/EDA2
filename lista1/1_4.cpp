#include <iostream>
#include <list>
#include <string>
#include <vector>

#define DATABASE_SIZE 3

using namespace std;

enum {
    BLUE = 0,
    RED,
    YELLOW
};

void setValues(vector< list<string> >&);
void findValue(const string, const vector< list<string> >);
bool isPresent(const string, const list<string>);
void printValues(const vector< list<string> >);

const string VALUE_FOUND_MESSAGE = "Value found";
const string VALUE_NOT_FOUND_MESSAGE = "Value not found";

int main() {
    vector< list<string> > database(DATABASE_SIZE);
    setValues(database);
    printValues(database);
    string to_find;
    cin >> to_find;

    cout <<  "\nFind value: " <<to_find <<endl;

    findValue(to_find, database);

    return 0;
}

void setValues(vector< list<string> > &some_vector) {
    for (int i = 0; i < 9; ++i) {
        string input;
        cin >> input;

        switch (input.at(0)) {
            case 'b':
                some_vector[BLUE].push_back(input);
                break;
            case 'r':
                some_vector[RED].push_back(input);
                break;
            case 'y':
                some_vector[YELLOW].push_back(input);
                break;
        }
    }
}

void findValue(const string car, const vector< list<string> > values) {
    switch (car.at(0)) {
        case 'b': {
            if (isPresent(car, values[0])) {
                cout << VALUE_FOUND_MESSAGE <<endl;
            } else {
                cout << VALUE_NOT_FOUND_MESSAGE <<endl;
            }
            break;
        }
        case 'r': {
            if (isPresent(car, values[1])) {
                cout << VALUE_FOUND_MESSAGE <<endl;
            } else {
                cout << VALUE_NOT_FOUND_MESSAGE <<endl;
            }
            break;
        }
        case 'y': {
            if (isPresent(car, values[2])) {
                cout << VALUE_FOUND_MESSAGE <<endl;
            } else {
                cout << VALUE_NOT_FOUND_MESSAGE <<endl;
            }
            break;
        }
        default:
            cout << VALUE_NOT_FOUND_MESSAGE <<endl;
    }
}

bool isPresent(const string car, const list<string> car_list) {
    for (list<string>::const_iterator it = car_list.begin(); it != car_list.end(); ++it) {
        if (!car.compare(*it)) {
            return true;
        } else {/*donot*/}
    }
    return false;
}

void printValues(const vector< list<string> > some_vector) {
    for(list<string> l : some_vector) {
        for(list<string>::const_iterator it = l.begin(); it != l.end(); ++it) {
            cout << *it << " ";
        }
        cout <<endl;
    }
}
