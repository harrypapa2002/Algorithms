#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v;
    double p, w;
    double modifiedWeight; // Used during the binary search

    Edge(int _u, int _v, double _p, double _w) : u(_u), v(_v), p(_p), w(_w) {}

    bool operator<(const Edge& other) const {
        return modifiedWeight < other.modifiedWeight;
    }
};

// Function to find the parent of a vertex (for union-find)
int findParent(vector<int>& parent, int vertex) {
    if (vertex == parent[vertex]) {
        return vertex;
    }
    return parent[vertex] = findParent(parent, parent[vertex]);
}

// Function to unite two sets (for union-find)
void unionSets(vector<int>& parent, vector<int>& rank, int a, int b) {
    a = findParent(parent, a);
    b = findParent(parent, b);

    if (rank[a] < rank[b]) {
        swap(a, b);
    }
    parent[b] = a;
    if (rank[a] == rank[b]) {
        rank[a]++;
    }
}

// Function to find gcd of two numbers
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    
    int N, M;
    scanf("%d %d", &N, &M); // Using scanf for faster input

    vector<Edge> edges;
    int u, v;
    double p, w;

    for (int i = 0; i < M; ++i) {
        scanf("%d %d %lf %lf", &u, &v, &p, &w); // Using scanf for faster input
        edges.emplace_back(u, v, p, w);
    }
    double low = 0, high = 1e9;
    double optimalRatio = 0;
    vector<Edge> resultEdges;

    while (high - low > 1e-6) {
        double mid =  (high + low) / 2;
        for (Edge& e : edges) {
            e.modifiedWeight = e.w - mid * e.p;
        }

        sort(edges.begin(), edges.end());
        vector<int> parent(N + 1), rank(N + 1, 0);
        for (int i = 1; i <= N; ++i) {
            parent[i] = i;
        }

        double totalModifiedWeight = 0;
        vector<Edge> currentEdges;

        for (Edge& e : edges) {
            if (findParent(parent, e.u) != findParent(parent, e.v)) {
                unionSets(parent, rank, e.u, e.v);
                totalModifiedWeight += e.modifiedWeight;
                currentEdges.push_back(e);
            }
        }

        if (totalModifiedWeight < 0) {
            optimalRatio = mid;
            resultEdges = currentEdges;
            high = mid;
        } else {
            low = mid;
        }
    }

    int totalProfit = 0, totalWeight = 0;
    for (Edge& e : resultEdges) {
        totalProfit += e.p;
        totalWeight += e.w;
    }

    int commonDivisor = gcd(totalProfit, totalWeight);
    cout << totalProfit / commonDivisor << " " << totalWeight / commonDivisor << endl;

    return 0;
}
