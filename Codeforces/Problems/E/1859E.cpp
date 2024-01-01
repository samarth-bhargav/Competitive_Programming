#include <bits/stdc++.h>

using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n, k; cin >> n >> k;
        vector<int> a(n+1), b(n+1);
        for (int i = 1; i <= n; i++){
            cin >> a[i];
        }
        for (int i = 1; i <= n; i++){
            cin >> b[i];
        }
        vector<vector<int>> dp(n+1, vector<int> (n+1, 0));
        dp[0][0] = 0;
        //dp[i][j] means max cost looking at i-th prefix and length of j
        vector<vector<int>> dp_max(n, vector<int> (4, 0));

        //dp_max[k][0] means max(dp[i][j] + a(i+1) + b(i+1)) for all i-j = k
        //dp_max[k][1] means max(dp[i][j] + a(i+1) - b(i+1)) for all i-j = k
        //dp_max[k][2] means max(dp[i][j] - a(i+1) + b(i+1)) for all i-j = k
        //dp_max[k][3] means max(dp[i][j] - a(i+1) - b(i+1)) for all i-j = k

        vector<array<int, 2>> c = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

        for (int d = 0; d < 4; d++){
            dp_max[0][d] = c[d][0] * a[1] + c[d][1] * b[1];
        }

        for (int i = 1; i <= n; i++){
            dp[i][0] = 0;
            if (i != n){
                for (int d = 0; d < 4; d++){
                    dp_max[i][d] = c[d][0] * a[i+1] + c[d][1] * b[i+1];
                }
            }
            for (int j = 1; j <= i; j++){
                dp[i][j] = dp[i-1][j];
                dp[i][j] = max(dp[i][j], dp_max[i-j][0] + (-a[i] - b[i]));
                dp[i][j] = max(dp[i][j], dp_max[i-j][3] + (a[i] + b[i]));
                dp[i][j] = max(dp[i][j], dp_max[i-j][1] + (a[i] - b[i]));
                dp[i][j] = max(dp[i][j], dp_max[i-j][2] + (b[i] - a[i]));
//                for (int d = 0; d < 4; d++){
//                    dp[i][j] = max(dp[i][j], dp_max[i-j][d] + (-c[d][0]) * a[i] + (-c[d][1]) * b[i]);
//                }
                if (i != n){
                    for (int d = 0; d < 4; d++){
                        dp_max[i-j][d] = max(dp_max[i-j][d], dp[i][j] + c[d][0] * a[i+1] + c[d][1] * b[i+1]);
                    }
                }
//                cerr << " i: " << i << " j: " << j << " dp[i][j]: " << dp[i][j] << "\n";
            }
        }
        cout << dp[n][k] << "\n";
    }
}