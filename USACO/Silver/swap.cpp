/*
Author: treewave
orz
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    freopen("swap.in", "r", stdin);
    freopen("swap.out", "w", stdout);
    int n,m,k;
    cin >> n >> m >> k;
    int iter = log2(k)+1;
    int dp[n+1][iter+5];
    vector <int> ar(n);
    for (int i = 0; i < n; i++){
        ar[i] = i+1;
    }
    for (int i = 0; i < m; i++){
        int a,b;
        cin >> a >> b;
        reverse(ar.begin()+a-1, ar.begin()+b);
    }
    for (int i = 1; i <= n; i++){
        dp[i][0] = ar[i-1];
    }
    for (int i = 1; i <= iter; i++){
        for (int j = 1; j <= n; j++){
            dp[j][i] = dp[dp[j][i-1]][i-1];
        }
    }
    for (int i = 1; i <= n; i++){
        int curr = i;
        int cnt = 0;
        while (cnt <= n){
            if ((k >> cnt) & 1){
                curr = dp[curr][iter-cnt];
            }
            cnt++;
        }
        cout << curr << "\n";
    }
}

