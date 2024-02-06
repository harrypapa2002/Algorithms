#include <iostream>
#include <vector>
#include <list>
#include <limits>
#include <cstdio> 

using namespace std;

typedef pair<int, long long> pii;

struct CityInfo {
    int parent;
    long long distToParent;
    long long distToRoot;
    long long result;
    long long tax;
    long long speed;
    list<pii> neighbors;
};

long long solver(vector<CityInfo>& cities, int node) {
    if (node == 0) return 0LL;
    if (cities[node].result != 0) return cities[node].result;

    long long minimum = numeric_limits<long long>::max();
    for (int x = cities[node].parent; x != -1; x = cities[x].parent) {
        long long distance = cities[node].distToRoot - cities[x].distToRoot;
        if (cities[node].speed * distance > minimum) break;
        minimum = min(minimum, solver(cities, x) + static_cast<long long>(cities[node].speed) * (distance));
    }

    cities[node].result = minimum + cities[node].tax;
    return cities[node].result;
}

int main() {
    int N;
    scanf("%d", &N); 

    vector<CityInfo> cities(N);

    for (int i = 0; i < N - 1; ++i) {
        int city1, city2, distance;
        scanf("%d %d %d", &city1, &city2, &distance); 
        cities[city1 - 1].neighbors.push_back({city2 - 1, distance});
        cities[city2 - 1].neighbors.push_back({city1 - 1, distance});
    }

    for (int i = 1; i < N; ++i) {
        scanf("%lld %lld", &cities[i].tax, &cities[i].speed); 
    }

    cities[0].parent = -1;
    cities[0].distToParent = 0;
    cities[0].distToRoot = 0;
    cities[0].result = 0;

    vector<bool> visited(N, false);
    list<int> queue;

    visited[0] = true;
    queue.push_back(0);

    while (!queue.empty()) {
        int current = queue.front();
        queue.pop_front();

        for (const auto& adjacent : cities[current].neighbors) {
            const int& neighbor = adjacent.first;
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                cities[neighbor].parent = current;
                cities[neighbor].distToParent = adjacent.second;
                cities[neighbor].distToRoot = cities[current].distToRoot + adjacent.second;

                queue.push_back(neighbor);
            }
        }
    }

    int nodes_done = 1;
    for (int i = 1; nodes_done < N; ++i) {
        solver(cities, i);
        nodes_done++;
    }

    for (int i = 1; i < N - 1; ++i) {
        printf("%lld ", cities[i].result);
    }
    printf("%lld\n", cities[N - 1].result); 

    return 0;
}
