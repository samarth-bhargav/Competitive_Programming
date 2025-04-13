#include <bits/stdc++.h>

using namespace std;

#define int long long
const int INF = 1e18;

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    vector<array<int,3>> payments;
    for (int i = 0; i < n; i++){
        int cores, clock, price;
        cin >> cores >> clock >> price;
        payments.push_back({clock, cores, -price});
    }
    int m; cin >> m;
    vector<array<int,3>> customers;
    for (int i = 0; i < m; i++){
        int cores, clock, price;
        cin >> cores >> clock >> price;
        payments.push_back({clock, -cores, price});
    }
    sort(payments.begin(), payments.end());
    int maxCores = 1;
    for (int i = 0; i < n+m; i++){
        maxCores += abs(payments[i][1]);
    }
//    cerr << maxCores << "\n";
    vector<int> dp(maxCores, -INF), ndp(maxCores, -INF);
    dp[0] = 0;
    for (int i = n+m-1; i >= 0; i--){
        ndp = dp;
        for (int c = 0; c < maxCores; c++){
            if (0 <= c + payments[i][1] && c + payments[i][1] < maxCores){
                ndp[c + payments[i][1]] = max(ndp[c + payments[i][1]], dp[c] + payments[i][2]);
            }
        }
        swap(ndp, dp);
    }
    int ans = -INF;
    for (int i = 0; i < maxCores; i++){
        ans = max(ans, dp[i]);
    }
    cout << ans << "\n";
}