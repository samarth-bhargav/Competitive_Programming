#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        vector<int> dp(n+1, -1e9), bestEnd(n+1);
        dp[0] = 0;
        for (int i = 1; i <= n; i++){
            bestEnd[i] = -n;
        }
        bestEnd[a[0]] = 0; dp[1] = -1;
        for (int i = 2; i <= n; i++){
            dp[i] = max(bestEnd[a[i-1]], -i);
            dp[i] = max(dp[i], dp[i-1] - 1);
            bestEnd[a[i-1]] = max(bestEnd[a[i-1]], dp[i-1]);
        }
        cout << dp[n] + n << "\n";
    }
}