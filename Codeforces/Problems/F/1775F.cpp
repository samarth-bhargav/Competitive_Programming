#include <bits/stdc++.h>

using namespace std;

int M;
const int INF = 1e9;

const int mxSQRT = 1400;
int dp[mxSQRT];
long long dp2[mxSQRT], dp4[mxSQRT];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t, u; cin >> t >> u;
    if (u == 2){
        cin >> M;
        memset(dp, 0, sizeof(dp));
        memset(dp2, 0, sizeof(dp2));
        memset(dp4, 0, sizeof(dp4));

        vector<int> pentagonal;
        for (int m = 1; m * (3 * m - 1) / 2 <= mxSQRT; m++){
            pentagonal.push_back(m * (3 * m - 1) / 2);
            pentagonal.push_back(-m * (-3 * m - 1) / 2);
        }
        dp[0] = 1;
        for (int i = 1; i < mxSQRT; i++){
            for (int j = 0; j < pentagonal.size() && pentagonal[j] <= i; j++){
                dp[i] += (j % 4 > 1 ? -1 : 1) * dp[i - pentagonal[j]];
                dp[i] %= M;
            }
            dp[i] = (dp[i] + M) % M;
        }

        for (int i = 0; i < mxSQRT; i++){
            for (int j = 0; j <= i; j++){
                dp2[i] += ((long long)dp[j] * dp[i - j]);
                dp2[i] %= M;
            }
            dp2[i] = (dp2[i] + M) % M;
        }

        for (int i = 0; i < mxSQRT; i++){
            for (int j = 0; j <= i; j++){
                dp4[i] += dp2[j] * dp2[i - j];
                dp4[i] %= M;
            }
            dp4[i] = (dp4[i] + M) % M;
        }
    }
    while (t--){
        int n; cin >> n;
        int min_perim = INF;
        vector<array<int, 2>> optimal_configs;
        for (int r = 1; (r - 1) * (r - 1) <= n; r++){
            int c = (n + r - 1) / r;
            if (r > c) continue;
            if (2 * (r + c) < min_perim){
                optimal_configs.clear();
                min_perim = 2 * (r + c);
                optimal_configs.push_back({r, c});
            }
            else if (2 * (r + c) == min_perim){
                optimal_configs.push_back({r, c});
            }
        }
        if (u == 1){
            int r = optimal_configs[0][0], c = optimal_configs[0][1];
            cout << r << " " << c << "\n";
            string ans[r];
            for (int i = 0; i < r; i++){
                ans[i] = string(c, '#');
            }
            assert((r * c) - n <= c);
            for (int i = 0; i < (r * c) - n; i++){
                ans[0][i] = '.';
            }
            for (int i = 0; i < r; i++){
                cout << ans[i] << "\n";
            }
        }
        else{
            long long ans = 0;
            for (int i = 0; i < optimal_configs.size(); i++){
                int r = optimal_configs[i][0], c = optimal_configs[i][1];
                ans += dp4[(r * c) - n]; ans %= M;
                if (r < c){
                    ans += dp4[(r * c) - n]; ans %= M;
                }
            }
            ans = (ans + M) % M;
            cout << min_perim << " " << ans << "\n";
        }
    }
}