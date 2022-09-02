#include <bits/stdc++.h>
using namespace std;

const int mxN = 400;
int dp[mxN][mxN];
map<int, set<pair<int,int>>> intervals;

int main(){
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    int ans = -1;
    memset(dp, -1, sizeof(dp));
    int j;
    for (int len = 0; len < n; len++){
        for (int i = 0; i + len < n; i++){
            j = i + len;
            if (len == 0){
                dp[i][j] = a[i];
                intervals[a[i]].insert({j, i});
            }
            else{
                int k1;
                for (int k = i; k <= j; k++){
                    //we consider [i, k] inclusive
                    if (dp[i][k] != -1){
                        auto it = intervals[dp[i][k]].lower_bound({j, -1});
                        if (it->first == j){
                            k1 = it->second;
                            if (k1 <= k){
                                continue;
                            }
                            if (k1 == k+1){
                                dp[i][j] = dp[i][k] + dp[k1][j];
                            }
                            else{
                                if (dp[k+1][k1-1] != -1){
                                    dp[i][j] = dp[i][k] + dp[k+1][k1-1] + dp[k1][j];
                                }
                            }
                        }
                    }
                }
                if (dp[i][j] != -1){
                    intervals[dp[i][j]].insert({j, i});
                }
            }
            ans = max(ans, dp[i][j]);
        }
    }
    cout << ans << "\n";
}
