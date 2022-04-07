/*
Author: treewave
orz
*/
#include <bits/stdc++.h>

using namespace std;

const int mxN = 1e3 + 5;
int dp[mxN][mxN];
int n,k;

int main() {
    freopen("paintbarn.in", "r", stdin);
    freopen("paintbarn.out", "w", stdout);
    memset(dp,0,sizeof(dp));
    cin >> n >> k;
    while (n--){
        int a,b,c,d;
        cin >> a >> b >> c >> d;
        //corners are (a,b) and (c,d);
        for (int i = b; i < d; i++){
            ++dp[i][a];
            --dp[i][c];
        }
    }
    int ans = 0;
    for (int i = 0; i < 1000; i++){
        for (int j = 0; j < 1000; j++){
            dp[i][j+1] = dp[i][j] + dp[i][j+1];
        }
    }
    for (int i = 0; i < 1000; i++){
        for (int j = 0; j < 1000; j++){
            if (dp[i][j] == k){
                ans++;
            }
        }
    }
    cout << ans << "\n";
}

