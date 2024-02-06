#include <iostream>
#include <algorithm>
#include <climits>
#include <cstdio>

using namespace std;

const int MAX_N = 100000; 
int profit[2][MAX_N];    

int maxProfit(int N, int K, int prices[]) {
    if (K == 0 || N == 0) return 0;

    int current = 0, previous = 1;

   bool profitMade = false;
   for (int i = 1; i <= K; ++i) {
       swap(current, previous);
       int maxDiff = INT_MIN;
       profitMade = false;
       for (int j = 1; j < N; ++j) {
       if (profit[previous][j - 1] - prices[j - 1] > maxDiff) {
          maxDiff = profit[previous][j - 1] - prices[j - 1];
        }

        int potentialProfit = prices[j] + maxDiff;

            if (potentialProfit <= profit[current][j - 1]) {
                profit[current][j] = profit[current][j - 1];
            } else {
            profit[current][j] = potentialProfit;
            profitMade = true;
            }
        }

        if (!profitMade) break;
   }



    return profit[current][N - 1];
}

int main() {
    int N, K;
    scanf("%d %d", &N, &K);
    K = min(K, N / 2);

    int prices[MAX_N];
    for (int i = 0; i < N; ++i) {
        scanf("%d", &prices[i]);
    }

    int max_profit = maxProfit(N, K, prices);
    printf("%d\n", max_profit); 

    return 0;
}
