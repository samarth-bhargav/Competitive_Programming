#include <bits/stdc++.h>
using namespace std;

const int mxN = 100, INF = 1e9;
array<int, 2> dp[mxN][mxN][mxN];
int dp1[mxN][mxN];

array<int, 2> max(array<int, 2> a, array<int, 2> b){
    if (a[0] < b[0]) return b;
    if (b[0] < a[0]) return a;
    if (a[1] < b[1]) return a;
    return b;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        for (int i = 0; i < n; i++){
            for (int j = 1; j <= n; j++){
                for (int k = 1; k <= n; k++){
                    dp[i][j][k] = {-INF, INF};
                }
                dp1[i][j] = INF;
            }
        }
        for (int j = 1; j <= n; j++){
            dp[0][j][a[0]] = {0, 1};
        }
        dp[0][a[0]][a[0]] = {1, 0};
        dp1[0][a[0]] = 1;
        for (int i = 1; i < n; i++){
            dp[i][a[i]][a[i]] = max(dp[i][a[i]][a[i]], {dp[i-1][a[i]][a[i]][0]+1, dp[i-1][a[i]][a[i]][1]});
            for (int j = 1; j <= n; j++){
                dp[i][j][a[i]] = max(dp[i][j][a[i]], {dp[i-1][j][a[i]][0], dp[i-1][j][a[i]][1]+1});
            }
            dp1[i][a[i]] = min(dp1[i][a[i]], dp1[i-1][a[i]]+1);
            unordered_set<int> min_len0;
            for (int j = 1; j <= n; j++){
                if (dp1[i][j] == 0){
                    min_len0.insert(j);
                }
            }
            if (min_len0.size() > 1 || min_len0.size() == 1 && *min_len0.begin() != a[i]){
                dp[i][a[i]][a[i]] = max(dp[i][a[i]][a[i]], {1, 0});
            }
            for (int j = 1; j <= n; j++){
                dp[i][j][a[i]] = max(dp[i][j][a[i]], {dp[i-1][j][j][0], 1});
                for (int k = 1; k <= n; k++){
                    if (k == a[i]) continue;
                    dp[i][j][j] = max(dp[i][j][j], {dp[i-1][j][k][0], );
                }
            }
            //update min dp
            for (int j = 1; j <= n; j++){
                if (dp1[i-1][j] <= n){
                    if (dp1[i-1][j] == 0){
                        if (dp[i-1][j][j] > 0){
                            dp1[i][j] = min(dp1[i][j], 1);
                        }
                        else{
                            dp1[i][j] = min(dp1[i][j], INF);
                        }
                    }
                    else{
                        dp1[i][j] = min(dp1[i][j], dp1[i-1][j] - 1);
                    }
                }
                if (min_len0.size() > 1 || min_len0.size() == 1 && *min_len0.begin() != a[i]){
                    dp1[i][j] = min(dp1[i][j], 1);
                }
            }
        }
//        for (int i = 0; i < n; i++){
//            for (int j = 1; j <= n; j++){
//                for (int k = 1; k <= n; k++){
//                    cout << "i: " << i << " j: " << j << " k: " << k << " dp[i][j][k]: " << dp[i][j][k] << "\n";
//                }
//            }
//        }
        int ans = 0;
        for (int j = 1; j <= n; j++){
            ans = max(ans, dp[n-1][j][j]);
        }
        cout << ans << "\n";
    }
}