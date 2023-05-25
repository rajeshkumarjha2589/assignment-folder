
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

vector<int> get_best_coordinate(vector<vector<int>>& towers, int radius) {
    int max_quality = 0;
    vector<int> min_coordinate = {0, 0};

    for (int x = -radius; x <= radius; x++) {
        for (int y = -radius; y <= radius; y++) {
            int network_quality = 0;
            for (auto tower : towers) {
                double d = sqrt(pow(x - tower[0], 2) + pow(y - tower[1], 2));
                if (d <= radius) {
                    int signal_quality = tower[2] / (1 + d);
                    network_quality += signal_quality;
                }
            }
            if (network_quality > max_quality) {
                max_quality = network_quality;
                min_coordinate = {x, y};
            } else if (network_quality == max_quality && (x < min_coordinate[0] || (x == min_coordinate[0] && y < min_coordinate[1]))) {
                min_coordinate = {x, y};
            }
        }
    }

    return min_coordinate;
}

int main() {
    vector<vector<int>> towers = {{1,2,5},{2,1,7},{3,1,9}};
    int radius = 2;

    vector<int> best_coordinate = get_best_coordinate(towers, radius);
    cout << "[" << best_coordinate[0] << ", " << best_coordinate[1] << "]" << endl;

    return 0;
}
