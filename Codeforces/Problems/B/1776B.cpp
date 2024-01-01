#include <bits/stdc++.h>

using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, h; cin >> n >> h;
    vector<int> c(n);
    for (int i = 0; i < n; i++){
        cin >> c[i];
    }
    int dp[n][n];
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 0; i < n; i++){
        dp[i][i] = 0;
    }
    for (int l = 1; l < n; l++){
        for (int s = 0; s + l < n; s++){
            for (int k = s; k < s + l; k++){
                dp[s][s+l] = min(dp[s][s+l], dp[s][k] + dp[k+1][s+l]
                                                        + 2 * ((c[s+l] - c[s] + 1) / 2 - 1) + 1
                                                        - (c[k] - c[s] + 1) / 2
                                                        - (c[s+l] - c[k+1] + 1) / 2);
            }
        }
    }
//    for (int i = 0; i < n; i++){
//        for (int j = i; j < n; j++){
//            cerr << "i: " << i << " j: " << j << " dp[i][j]: " << dp[i][j] << endl;
//        }
//    }
    int dp1[n][n], mindp1[n];
    memset(dp1, 0x3f, sizeof(dp1));
    memset(mindp1, 0x3f, sizeof(mindp1));
    dp1[0][0] = h; mindp1[0] = h;
    for (int i = 1; i < n; i++){
        for (int j = 0; j < i; j++){
            if ((c[i] - c[j] + 1) / 2 > h) continue;
            for (int k = i; k >= j; k--){
                if ((c[i] - c[k] + 1) / 2 > h) continue;
                //merge (k, i)
                dp1[i][j] = min(dp1[i][j], dp[k][i] + (k != j ? dp1[k-1][j] : h - (c[i] - c[j] + 1) / 2) + (j != 0 ? mindp1[j-1] : 0) + (c[i] - c[j] + 1) / 2 - (c[i] - c[k] + 1) / 2);
            }
        }
        dp1[i][i] = mindp1[i-1] + h;
        for (int j = 0; j <= i; j++){
            mindp1[i] = min(mindp1[i], dp1[i][j]);
        }
    }
    cout << mindp1[n-1] << "\n";
}