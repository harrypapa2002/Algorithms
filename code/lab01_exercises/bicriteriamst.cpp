#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool possibleMedian(vector<int>& cereals, int m,int N, int K) {
    // checks if there is a subsequence with median at least m
    vector<int> pref(N+1, 0);

    for (int i = 1; i <= N; i++) {
        //count the prefix sums, cumulative sum up to ith element
        pref[i] = pref[i-1] + (cereals[i-1] >= m ? 1 : -1);
    }

    int minPref = 0;
    for (int i = K; i <= N; i++) {
        if (pref[i] - minPref > 0) { //if positive then the median is at least m
            return true;
        }
        minPref = min(minPref, pref[i-K+1]); //slide the window
    }
    return false;
}

int main() {
    int N, K;
    cin >> N >> K;

    vector<int> cereals(N);
    for(int i = 0; i < N; i++) {
        cin >> cereals[i];
    }

    int minVal = *min_element(cereals.begin(), cereals.end());
    int maxVal = *max_element(cereals.begin(), cereals.end());
    int ans = minVal;

    while (minVal <= maxVal) {
        int m =  (maxVal + minVal) / 2;
        if (possibleMedian(cereals, m, N, K)) {
            ans = m;
            minVal = m+1;
        } else {
            maxVal = m-1;
        }
    }

    cout << ans << endl;
    return 0;
}