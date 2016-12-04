#include <array>
#include <iostream>
#include <utility>

using namespace std;
using cousint = const unsigned int;
using ui_ui = pair<unsigned int, unsigned int>;
cousint JOBS_SIZE = 6;
const bool LOW = false;
const bool HIGH = true;

template <typename T>
inline T& max(T& a, T& b) {
    return a > b? a : b;
}

unsigned int maxValue(array<ui_ui, JOBS_SIZE>);

int main() {
    array<ui_ui, JOBS_SIZE> jobs;
    for (unsigned int i = 0; i < JOBS_SIZE; ++i) {
        unsigned int low_revenue(0);
        unsigned int high_revenue(0);
        cin >> low_revenue >> high_revenue;
        jobs[i].first = low_revenue;
        jobs[i].second = high_revenue;
    }
    for(size_t i = 0; i < jobs.size(); ++i) {
        cout << jobs[i].first << " " << jobs[i].second <<endl;
    }

    cout << maxValue(jobs) <<endl;

    return 0;
}

unsigned int maxValue(array<ui_ui, JOBS_SIZE> jobs) {
    array<unsigned int, jobs.size()> max_value;
    bool last_taken = max(jobs[0].first, jobs[0].second) == jobs[0].first? LOW : HIGH;
    max_value[0] = last_taken == LOW? jobs[0].first : jobs[0].second;

    for (unsigned int i = 1; i < jobs.size(); ++i) {
        unsigned int discount = last_taken == LOW? jobs[i - 1].first : jobs[i - 1].second;
        unsigned int current_high = jobs[i].second + max_value[i - 1] - discount;
        unsigned int current_low = jobs[i].first + max_value[i - 1];
        last_taken = max(current_low, current_high) == current_low? LOW : HIGH;
        max_value[i] = last_taken == LOW? current_low : current_high;
    }

    return max_value.back();
}
