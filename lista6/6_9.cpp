#include <iostream>
#include <random>
#include <vector>

#define SCHEDULE_SIZE 8
#define PC_MAX_CAPACITY 16

using namespace std;

vector<unsigned int> getSchedule();
unsigned int processTerabytes(const vector<unsigned int>);
unsigned int calculateProcess(const int, const int);

int main() {
    vector<unsigned int> schedule = getSchedule();
    vector<unsigned int> test_schedule = {5, 7, 3, 19, 18, 6, 15, 16};

    for (unsigned int i : schedule) {
        cout << i << " ";
    }
    cout <<endl;

    cout << "max processed: " << processTerabytes(schedule) <<endl;

    return 0;
}

vector<unsigned int> getSchedule() {
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> terabytes(1, 20);

    vector<unsigned int> schedule;
    for (int i = 0; i < SCHEDULE_SIZE; ++i) {
        schedule.push_back(terabytes(rng));
    }

    return schedule;
}

unsigned int processTerabytes(const vector<unsigned int> schedule) {
    unsigned int pc_capacity = PC_MAX_CAPACITY;
    vector<unsigned int> max_processed;
    max_processed.push_back(calculateProcess(PC_MAX_CAPACITY, schedule[0]));
    pc_capacity /= 2;

    unsigned int alt1 = max_processed[0] + calculateProcess(pc_capacity, schedule[1]);
    unsigned int alt2 = calculateProcess(PC_MAX_CAPACITY, schedule[1]);
    if (alt1 > alt2) {
        max_processed.push_back(alt1);
        pc_capacity /= 2;
    } else {
        max_processed.push_back(alt2);
        pc_capacity = PC_MAX_CAPACITY;
    }

    for (int i = 2; i < SCHEDULE_SIZE; ++i) {
        unsigned int alt1 = max_processed[i - 2] + calculateProcess(PC_MAX_CAPACITY, schedule[i]);
        unsigned int alt2 = max_processed[i - 1] + calculateProcess(pc_capacity, schedule[i]);
        if (alt1 > alt2) {
            max_processed.push_back(alt1);
            pc_capacity = PC_MAX_CAPACITY / 2;
        } else {
            max_processed.push_back(alt2);
            pc_capacity /= 2;
        }
    }
    return max_processed.back();
}

unsigned int calculateProcess(const int pc_capacity, const int process_size) {
    if (pc_capacity  >= process_size) {
        return process_size;
    } else {
        return pc_capacity;
    }
}
