//babybeluga
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/
const int mxN = 1e3;
ll dp[mxN][mxN],g[mxN][mxN];
const int M = 1e9+7;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,m;
    cin >> n >> m;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++)
            cin >> g[i][j];
    }
    dp[0][0] = 1;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (g[i][j] == 1){
                dp[i][j] = 0;
            }
            else{
                if (j == 0){
                    if (i == 0){
                        dp[i][j] = 1;
                    } else{
                        dp[i][j] = dp[i-1][j]%M;
                    }
                } else{
                    if (i == 0){
                        dp[i][j] = dp[i][j-1]%M;
                    } else{
                        dp[i][j] = (dp[i][j-1] + dp[i-1][j])%M;
                    }
                }
            }
        }
    }
    cout << dp[n-1][m-1] << "\n";
}

