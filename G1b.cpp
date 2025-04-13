#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n = 10;
    bool dp[n][n];
    memset(dp, false, sizeof(dp));

    for (int i = 2; i <= n-1; i++){
        for (int j = 1; j < i; j++){
            bool can_beat = false;
            for (int k = 1; k <= 12 * j / 4; k++){
                if (k >= i - j){
                    can_beat = true;
                    break;
                }
                if (dp[i-j][k]){
                    can_beat = true;
                    break;
                }
            }
            dp[i][j] = !can_beat;
        }
    }
    for (int i = 2; i <= n-1; i++){
        for (int j = 1; j < i; j++){
            dp[i][j] |= dp[i][j-1];
        }
    }
    for (int i = 2; i <= n-1; i++){
        for (int j = 1; j < i; j++){
            cout << "i: " << i << " j: " << j << " dp[i][j]: " << dp[i][j] << "\n";
        }
    }
}