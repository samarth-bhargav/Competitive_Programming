#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main(){
    int n, m;
    cin >> n >> m;
    int a[n], pf[n+1]; pf[0] = 0;
    for (int i = 0; i < n; i++){
        cin >> a[i];
        pf[i+1] = pf[i] + a[i];
    }
    int dp[n][m+1][m+1];
    for (int i = 0; i < n; i++){
        for (int j = 0; j <= m; j++){
            for (int k = 0; k <= m; k++){
                dp[i][j][k] = INF;
            }
        }
    }
    for (int j = 0; j <= m; j++){
        dp[0][j][j] = abs(a[0] - j); //to transfer over
    }
    for (int j = m-1; ~j; j--){
        for (int k = j; k <= m; k++){
            dp[0][j][k] = min(dp[0][j][k], dp[0][j+1][k]);
        }
    }
    for (int i = 1; i < n; i++){
        for (int j = 0; j <= m; j++){
            for (int k = j; k <= m; k++){
                dp[i][j][k] = min(dp[i][j][k], dp[i-1][j][k-j] + abs(pf[i+1] - k));
            }
        }
        for (int j = m-1; ~j; j--){
            for (int k = j; k <= m; k++){
                dp[i][j][k] = min(dp[i][j][k], dp[i][j+1][k]);
            }
        }
    }
    int ans = 1e9;
    for (int j = 0; j <= m; j++){
        ans = min(ans, dp[n-1][j][m]);
    }
    cout << ans << "\n";
}
