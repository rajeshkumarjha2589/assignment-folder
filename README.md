# assignment-folder
assignment question solution
Solve the questions in C/C++/ Go lang/JAVA only No other Language


Hyderabad consists of numerous network towers of various network providers. The metadata consisting of the location of the towers is given to you in an array format towers, where towers[i] = [xi, yi, qi] denotes the ith network tower with location (xi, yi) and quality factor qi. All the coordinates are integral coordinates on the X-Y plane, and the distance between the two coordinates is the Euclidean distance.
You are also given an integer radius where a tower is reachable if the distance is less than or equal to radius. Outside that distance, the signal becomes garbled, and the tower is not reachable.
The signal quality of the ith tower at a coordinate (x, y) is calculated with the formula ⌊qi / (1 + d)⌋, where d is the distance between the tower and the coordinate. The network quality at a coordinate is the sum of the signal qualities from all the reachable towers.
Return the array [cx, cy] representing the integral coordinate (cx, cy) where the network quality is maximum. If there are multiple coordinates with the same network quality, return the lexicographically minimum non-negative coordinate.
Note:
A coordinate (x1, y1) is lexicographically smaller than (x2, y2) if either:
x1 < x2, or
x1 == x2 and y1 < y2.
⌊val⌋ is the greatest integer less than or equal to val (the floor function).


Example:


Input: towers = [[1,2,5],[2,1,7],[3,1,9]], radius = 2
Output: [2,1]
Explanation: At coordinate (2, 1) the total quality is 13.
- Quality of 7 from (2, 1) results in ⌊7 / (1 + sqrt(0)⌋ = ⌊7⌋ = 7
- Quality of 5 from (1, 2) results in ⌊5 / (1 + sqrt(2)⌋ = ⌊2.07⌋ = 2
- Quality of 9 from (3, 1) results in ⌊9 / (1 + sqrt(1)⌋ = ⌊4.5⌋ = 4
No other coordinate has a higher network quality.

Constraints:
1 <= towers.length <= 50
towers[i].length == 3
0 <= xi, yi, qi <= 50
1 <= radius <= 50




Solution in c language 


#include <stdio.h>
#include <math.h>
#include <limits.h>

int get_distance(int x1, int y1, int x2, int y2) {
    int dx = x1 - x2;
    int dy = y1 - y2;
    return (int)sqrt(dx*dx + dy*dy);
}

int get_signal_quality(int q, int d) {
    return q / (1 + d);
}

int is_reachable(int x1, int y1, int x2, int y2, int radius) {
    int d = get_distance(x1, y1, x2, y2);
    return d <= radius ? 1 : 0;
}

int* get_best_coordinate(int towers[][3], int n, int radius) {
    int max_quality = INT_MIN;
    int* min_coordinate = (int*)calloc(2, sizeof(int));
    int i, j, x, y, network_quality, signal_quality, d;

    for (x = -radius; x <= radius; x++) {
        for (y = -radius; y <= radius; y++) {
            network_quality = 0;
            for (i = 0; i < n; i++) {
                if (is_reachable(x, y, towers[i][0], towers[i][1], radius)) {
                    d = get_distance(x, y, towers[i][0], towers[i][1]);
                    signal_quality = get_signal_quality(towers[i][2], d);
                    network_quality += signal_quality;
                }
            }
            if (network_quality > max_quality) {
                max_quality = network_quality;
                min_coordinate[0] = x;
                min_coordinate[1] = y;
            } else if (network_quality == max_quality && (x < min_coordinate[0] || (x == min_coordinate[0] && y < min_coordinate[1]))) {
                min_coordinate[0] = x;
                min_coordinate[1] = y;
            }
        }
    }

    return min_coordinate;
}

int main() {
    int towers[][3] = {{1,2,5},{2,1,7},{3,1,9}};
    int n = sizeof(towers) / sizeof(towers[0]);
    int radius = 2;

    int* best_coordinate = get_best_coordinate(towers, n, radius);
    printf("[%d, %d]\n", best_coordinate[0], best_coordinate[1]);

    return 0;
}




Solution in c++

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
