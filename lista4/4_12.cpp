#include <iostream>
#include <random>
#include <stdio.h>
#include <utility>
#include <vector>

#define STREAMS_QUANTITY 10
#define CONSTRAINT_VALUE 5000

using namespace std;

using ui_ui = pair<unsigned int, unsigned int>;

vector<ui_ui> randomStreams() {
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> bits(1000, 9999);
    uniform_int_distribution<int> time(1, 5);

    vector<ui_ui> random_streams;
    for(int i = 0; i < STREAMS_QUANTITY; i++) {
        random_streams.push_back(ui_ui(bits(rng), time(rng)));
    }

    return random_streams;
}



int main() {
    unsigned int constraint = CONSTRAINT_VALUE;

    vector<ui_ui> streams = randomStreams();

    unsigned int bits_sent = 0;
    unsigned int schedule_time = 0;

    printf("r = %d\n", CONSTRAINT_VALUE);
    for(size_t i = 0; i < STREAMS_QUANTITY; ++i) {
        bits_sent += streams[i].first;
        schedule_time += streams[i].second;

        printf("(%u, %u)\n", streams[i].first, streams[i].second);
        if (bits_sent > schedule_time * constraint) {
            printf("Schedule not valid\n");
            exit(0);
        } else {/*donot*/}
    }

    printf("Schedule valid\n");

    return 0;
}
