#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++){
            cin >> a[i]; a[i]--;
        }
        vector<vector<bool>> removable(n, vector<bool>(n, 0));
        for (int i = 0; i < n; i++){
            vector<int> occ(n, 0);
            int res = i, count = 1;
            occ[a[res]]++;
            for (int j = i+1; j < n; j++){
                occ[a[j]]++;
                if (a[res] == a[j]){
                    count++;
                }
                else{
                    count--;
                }
                if (count == 0){
                    res = j;
                    count = 1;
                }
                if (occ[a[res]] * 2 <= (j - i + 1) && ((j - i + 1) % 2 == 0)){
                    removable[i][j] = true;
                }
            }
        }
        vector<vector<int>> occ(n);
        for (int i = 0; i < n; i++){
            occ[a[i]].push_back(i);
        }
        int ans = 0;
        for (int i = 0; i < n; i++){
            vector<int> dp(n, -INF);
            for (int j = 0; j < n; j++){
                if (removable[0][j]){
                    dp[j] = max(dp[j], 0);
                }
                if (a[j] == i){
                    if (j == 0){
                        dp[j] = max(dp[j], 1);
                    }
                    else{
                        dp[j] = max(dp[j], dp[j-1] + 1);
                    }
                }
                for (int k = 0; k < occ[i].size() && occ[i][k] < j; k++){
                    if (removable[occ[i][k]][j] && occ[i][k] != 0){
                        dp[j] = max(dp[j], dp[occ[i][k]-1]);
                    }
                    if (occ[i][k] != n-1 && removable[occ[i][k]+1][j]){
                        dp[j] = max(dp[j], dp[occ[i][k]]);
                    }
                }
            }
            ans = max(ans, dp.back());
        }
        cout << ans << "\n";
    }
}