/*
Dont raise your voice,improve your argument
--Desmond Tutu
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/
const int M = 1e9+7;
int dp[1001][1001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--){
        int n,k;
        cin >> n >> k;
        //dp[i][j] = i energy in j plane
        for (int i = 1; i <= n; i++){
            dp[1][i] = 1;
        }
        for (int i = 1; i <= k; i++){
            dp[i][0] = 1;
        }
        for (int i = 2; i <= k; i++) {
            for (int j = 1; j <= n; j++) {
                dp[i][j] = (dp[i - 1][n - j] + dp[i][j - 1]) % M;
            }
        }
        cout << dp[k][n] << "\n";
    }
}

