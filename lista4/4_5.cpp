#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {

    int n = 0;
    const double max_dist = 4.0;
    scanf("%d", &n);

    vector<double> positions;
    for (int i = 0; i < n; ++i) {
        double pos = 0;
        scanf("%lf", &pos);
        positions.push_back(pos);
    }

    sort(positions.begin(), positions.end());

    int tower_count = 0;

    while (!positions.empty()) {

        int houses_count = 1;
        double distance = positions[1] - positions[0];

        while(positions.size() >= 2 && distance <= max_dist) {
            distance += positions[1] - positions[0];
            ++houses_count;
        }

        positions.erase(positions.begin(), positions.begin() + houses_count);

        ++tower_count;
    }

    printf("tower count = %d\n", tower_count);

    return 0;
}
