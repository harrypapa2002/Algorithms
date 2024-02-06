#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <climits>
#include <cstdio>

using namespace std;

struct Edge {
    int to, travelTime;
    Edge(int to, int travelTime) : to(to), travelTime(travelTime) {}
};

struct State {
    int city;
    long long time;
    State(int city, long long time) : city(city), time(time) {}
    bool operator>(const State& other) const {
        return time > other.time;
    }
};

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    int A, B, T, K;
    scanf("%d %d %d %d", &A, &B, &T, &K);
    vector<int> c(K);
    for (int i = 0; i < K; ++i) {
        scanf("%d", &c[i]);
    }
    vector<vector<Edge>> graph(N + 1);
    for (int i = 0; i < M; ++i) {
        int u, v, d;
        scanf("%d %d %d", &u, &v, &d);
        graph[u].emplace_back(v, d);
        graph[v].emplace_back(u, d);
    }

    // Track blocked times for each road
    map<pair<int, int>, pair<int, int>> blockedTimes;
    int currentTime = 0;
    for (int i = 0; i < K - 1; ++i) {
        for (Edge& e : graph[c[i]]) {
            if (e.to == c[i + 1]) {
                blockedTimes[{c[i], c[i + 1]}] = {currentTime, currentTime + e.travelTime - 1};
                blockedTimes[{c[i + 1], c[i]}] = {currentTime, currentTime + e.travelTime - 1};
                currentTime += e.travelTime;
                break;
            }
        }
    }

    priority_queue<State, vector<State>, greater<State>> pq;
    vector<long long> dist(N + 1, LLONG_MAX);
    dist[A] = T;
    pq.emplace(A, T);

    while (!pq.empty()) {
        State state = pq.top(); pq.pop();
        int city = state.city;
        long long time = state.time;
        if (dist[city] < time) continue;
        if (city == B) break; // Found the shortest path to B

        for (Edge& e : graph[city]) {
            int adjCity = e.to;
            long long startTime = time;
            auto it = blockedTimes.find({city, adjCity});
            if (it != blockedTimes.end() && startTime >= it->second.first && startTime <= it->second.second) {
                startTime = it->second.second + 1;
            }
            long long arrivalTime = startTime + e.travelTime;
            if (arrivalTime < dist[adjCity]) {
                dist[adjCity] = arrivalTime;
                pq.emplace(adjCity, arrivalTime);
            }
        }
    }

    if (dist[B] == LLONG_MAX) cout << "-1\n"; // No path found
    else cout << dist[B] - T << endl; // Minimum duration of the trip

    return 0;
}
