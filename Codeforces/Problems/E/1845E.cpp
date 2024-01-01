#include <bits/stdc++.h>

using namespace std;

const int M = 1e9+7;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, kk;
    cin >> n >> kk;
    int SQRT = ceil(sqrt(kk)) + 1;
    int TWOSQRT = 2 * SQRT + 1;
    vector<vector<int>> dp(kk+1, vector<int> (TWOSQRT, 0)), ndp(kk+1, vector<int> (TWOSQRT, 0));
    vector<int> a(n);
    vector<int> ones;
    for (int i = 0; i < n; i++){
        cin >> a[i];
        if (a[i]) ones.push_back(i);
    }
    vector<vector<int>> perspective(n, vector<int> (n, -1));
    vector<vector<int>> ones_sqrtaway(n);
    for (int i = 0; i < n; i++){
        int curr_idx = lower_bound(ones.begin(), ones.end(), i) - ones.begin();
        for (int j = min(curr_idx, (int)ones.size()-1); j >= max(0, curr_idx - SQRT); j--){
            ones_sqrtaway[i].push_back(ones[j]);
        }
        for (int j = curr_idx+1; j < min((int)ones.size(), curr_idx + SQRT); j++){
            ones_sqrtaway[i].push_back(ones[j]);
        }
        sort(ones_sqrtaway[i].begin(), ones_sqrtaway[i].end());
        for (int j = 0; j < ones_sqrtaway[i].size(); j++){
            perspective[i][ones_sqrtaway[i][j]] = j;
        }
        ones_sqrtaway[i].push_back(1e9);
    }
    //dp[j][k] is sum of distance j, and you're on the kth 1 in the ones_sqrtaway array
    //dp[i][j][k from i's perspective] = dp[i-1][j][k from (i-1)'s perspective] + dp[i-1][j - dist((k-1)th 1 from i-1 perspective)][(k-1)th 1 from i-1 perspective]
    dp[0][0] = 1; dp[ones[0]][1] = 1;
    for (int i = 1; i < n; i++){
        for (int j = 0; j <= kk; j++){
            for (int k = 0; k < ones_sqrtaway[i].size(); k++){
                ndp[j][k] = 0;
                //using 0
                if (k != ones_sqrtaway[i].size()-1 && perspective[i-1][ones_sqrtaway[i][k]] != -1){
                    ndp[j][k] += dp[j][perspective[i-1][ones_sqrtaway[i][k]]];
                    ndp[j][k] = (ndp[j][k] % M + M) % M;
                }
                else if (k == ones_sqrtaway[i].size()-1){
                    ndp[j][k] += dp[j][ones_sqrtaway[i-1].size()-1];
                    ndp[j][k] = (ndp[j][k] % M + M) % M;
                }
                //using 1
                if (k != 0 && perspective[i-1][ones_sqrtaway[i][k-1]] != -1 && abs(i - ones_sqrtaway[i-1][perspective[i-1][ones_sqrtaway[i][k-1]]]) <= j){
                    ndp[j][k] += dp[j - abs(i - ones_sqrtaway[i-1][perspective[i-1][ones_sqrtaway[i][k-1]]])][perspective[i-1][ones_sqrtaway[i][k-1]]];
                    ndp[j][k] = (ndp[j][k] % M + M) % M;
                }
            }
        }
        swap(ndp, dp);
//        for (int j = 0; j <= kk; j++){
//            for (int k = 0; k < ones_sqrtaway[i].size(); k++){
//                cerr << "i: " << i << " j: " << j << " k: " << k << " dp[i][j][k]: " << dp[j][k] << "\n";
//            }
//        }
    }
    int ans = 0;
    for (int s = kk; s >= 0; s -= 2){
        ans += dp[s][ones_sqrtaway[n-1].size()-1];
        ans = (ans % M + M) % M;
    }
    cout << ans << "\n";
}