#include <bits/stdc++.h>

#define int long long
using namespace std;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
//        return x;
    }

    size_t operator()(array<int, 2> x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x[0] + FIXED_RANDOM) * 2 + splitmix64(x[1] + FIXED_RANDOM);
//        return x[0] + x[1];
    }
};

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> a(m+1, vector<int>(n));
    for (int j = 0; j < n; j++){
        for (int i = 1; i <= m; i++){
            cin >> a[i][j];
        }
    }
    unordered_map<array<int, 2>, int, custom_hash> dp;
    if (k != 1){
        dp[{1, 0}] = 0;
    }
    dp[{1, 1}] = 0;
    for (int i = 0; i < n; i++){
        dp[{1, 1}] = max(dp[{1, 1}], a[1][i]);
    }
    for (int i = 2; i <= m; i++){
        vector<int> col;
        for (int j = 0; j < n; j++){
            col.push_back(a[i][j]);
        }
        sort(col.rbegin(), col.rend());
        vector<int> pf(n+1); pf[0] = 0;
        for (int j = 1; j <= n; j++){
            pf[j] = pf[j-1] + col[j-1];
        }
        for (int j = max(i-k+1, 0LL); j <= min(i, m-k+1); j++){
            dp[{i, j}] = 0;
            for (int l = 0; l <= min({n, i, m-i+1}); l++){
                if (dp.count({i-1, j-l})){
                    dp[{i, j}] = max(dp[{i, j}], dp[{i-1, j-l}] + pf[l]);
                }
            }
        }
    }
    cout << dp[{m, m-k+1}] << "\n";
}