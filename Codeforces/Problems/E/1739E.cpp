#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define int ll
const int mxN = 2e5+2;
const int INF = 1e9;
int dp[mxN][2][2], g[mxN][2];

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    for (int i = 0; i < 2; i++){
        string s; cin >> s;
        for (int j = 0; j < n; j++){
            if (s[j] == '1'){
                g[j][i] = 1;
            }
            else{
                g[j][i] = 0;
            }
        }
    }
    g[n][0] = 0;
    g[n][1] = 0;
    for (int i = 0; i < n+1; i++){
        for (int j = 0; j < 2; j++){
            for (int k = 0; k < 2; k++){
                dp[i][j][k] = -INF;
            }
        }
    }
    dp[0][0][0] = 0;
    dp[0][0][1] = (g[0][1] ? 0 : -INF);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < 2; j++){
            int nj = g[i+1][j];
            int njp = g[i+1][1-j];
            //right
            dp[i+1][j][0] = max(dp[i+1][j][0], dp[i][j][0] + nj);
            //down right
            dp[i+1][1-j][0] = max(dp[i+1][1-j][0], dp[i][j][1] + njp + 1);
            if (njp){
                //right
                dp[i+1][j][1] = max(dp[i+1][j][1], dp[i][j][0] + nj);
            }
        }
    }
    cout << max({dp[n][0][0], dp[n][0][1], dp[n][1][0], dp[n][1][1]}) << "\n";
}
