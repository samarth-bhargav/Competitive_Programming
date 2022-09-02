#include <bits/stdc++.h>
using namespace std;

const int mxN = 300;
int dp[mxN][mxN];

int main(){
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 0; i < n; i++){
        dp[i][i] = 1;
    }
    set<int> active_begin;
    set<int> active_end;
    for (int len = 2; len <= n; len++){
        for (int i = 0; i + len <= n; i++){
            int j = i + len - 1;
            //base case
            dp[i][j] = 1 + dp[i+1][j]; //just paint[i, i+1]
            //see if theres any overlap...
            bool appeared = false;
            bool found = false;
            for (int k = i+1; k <= j; k++){
                if (a[k] == a[i]){
                    if (len == 2){
                        dp[i][j] = 1;
                        continue;
                    }
                    dp[i][j] = min(dp[i][j], (i+1 > k-1 ? 0 : dp[i+1][k-1]) + (k+1 > j ? 0 : dp[k+1][j]) + (appeared ? (found ? 1 : 0) : 1));
                    appeared = true;
                    found = false;
                    continue;
                }
                else{
                    if (appeared){
                        if (!active_begin.empty() && active_begin.find(a[k]) != active_begin.end()){
                            found = true;
                        }
                    }
                    else{
                        active_begin.insert(a[k]);
                    }
                }
            }
            active_begin.clear();
        }
    }
    cout << dp[0][n-1] << "\n";
}