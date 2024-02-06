#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <tuple>
#include <cstdio>

using namespace std;

// Union-Find Data Structure
class UnionFind {
public:
    vector<int> parent, rank;

    UnionFind(int size) : parent(size), rank(size, 0) {
        for(int i = 0; i < size; ++i) parent[i] = i;
    }

    int find(int x) {
        if(parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unionSet(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if(rootX == rootY) return false;
        if(rank[rootX] < rank[rootY]) swap(rootX, rootY);
        parent[rootY] = rootX;
        if(rank[rootX] == rank[rootY]) rank[rootX]++;
        return true;
    }
};

int main() {
    int N, M, K;
    scanf("%d %d %d", &N, &M, &K);
    vector<tuple<int, int, int>> avenues(M);
    for(int i = 0; i < M; ++i) {
        int a, b, t;
        scanf("%d %d %d", &a, &b, &t);
        avenues[i] = make_tuple(t, a-1, b-1); // Store with maintenance time first for sorting
    }

    // Sort avenues by maintenance time in descending order
    sort(avenues.rbegin(), avenues.rend());

    UnionFind uf(N);
    int components = N;
    vector<int> includedTimes;

    for(const auto &avenue : avenues) {
        int t = get<0>(avenue);
        int a = get<1>(avenue);
        int b = get<2>(avenue);
        if(uf.unionSet(a, b)) {
            includedTimes.push_back(t);
            components--;
        }
        if(components == 1) break; // All cities are connected
    }

    sort(includedTimes.begin(), includedTimes.end());
    if(K >= includedTimes.size()) {
        printf("infinity\n");
    } else {
        printf("%d\n", includedTimes[K]);
    }

    return 0;
}
