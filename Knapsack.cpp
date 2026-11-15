#include "Knapsack.h"


int knapTab(int capacity, const vector<Item>& items, vector<vector<int>>& dp) {
    int n = items.size();

    // initialize dp table
    dp.resize(n+1, vector<int>(capacity+1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (items[i-1].weight > w) {
                dp[i][w] = dp[i - 1][w];
            }
            else {
                // choose max value between taking and not taking the item
                dp[i][w] = max(dp[i-1][w], items[i-1].value + dp[i-1][w - items[i-1].weight]);
            }
        }
    }

    return dp[n][capacity];
}

vector<string> knapItems(const vector<Item>& items, const vector<vector<int>>& dp, int capacity){
    vector<string> selected;

    int i = items.size();
    int w = capacity;

    while (i > 0 && w > 0) {
        // trace backward through the table to find the selected items
        if (dp[i][w] != dp[i - 1][w]) {
            selected.push_back(items[i - 1].name);
            w -= items[i - 1].weight;
        }
        i--;
    }
    return selected;
}