#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n, k; cin >> n >> k;
        vector<int> a(n);
        for (int i = 0; i < n; i++){
            char c; cin >> c;
            a[i] = c - '0';
        }
        int dp_pref[n][k+2][2], dp_suf[n][k+2][2];
        memset(dp_pref, 0, sizeof(dp_pref));
        memset(dp_suf, 0, sizeof(dp_suf));
        if (a[0] == 0){
            dp_pref[0][1][1] = 1;
            dp_pref[0][1][0] = 1;
        }
        else{
            dp_pref[0][0][1] = 1;
            dp_pref[0][0][0] = 1;
        }
        for (int i = 1; i < n; i++){
            for (int j = 0; j <= k; j++){
                if (a[i] == 1){
                    dp_pref[i][j][1] = dp_pref[i-1][j][1] + 1;
                }
                else{
                    if (j != 0){
                        dp_pref[i][j][1] = dp_pref[i-1][j-1][1] + 1;
                    }
                }
                dp_pref[i][j][0] = max(dp_pref[i-1][j][0], dp_pref[i][j][1]);
            }
        }

        if (a[n-1] == 0){
            dp_suf[n-1][1][1] = 1;
            dp_suf[n-1][1][0] = 1;
        }
        else{
            dp_suf[n-1][0][1] = 1;
            dp_suf[n-1][0][0] = 1;
        }
        for (int i = n-2; ~i; i--) {
            for (int j = 0; j <= k; j++) {
                if (a[i] == 1) {
                    dp_suf[i][j][1] = dp_suf[i + 1][j][1] + 1;
                } else {
                    if (j != 0) {
                        dp_suf[i][j][1] = dp_suf[i + 1][j - 1][1] + 1;
                    }
                }
                dp_suf[i][j][0] = max(dp_suf[i + 1][j][0], dp_suf[i][j][1]);
            }
        }

        vector<int> ans(n+1, 0);
        //no zeros
        if (count(a.begin(), a.end(), 0) <= k){
            for (int i = 1; i <= n; i++){
                ans[i] = max(ans[i], n);
            }
        }

        vector<array<int, 2>> combos;
        for (int s = 0; s < n; s++){
            int num_swaps = 0;
            int j;
            for (j = s-1; j < n; j++){
                if (num_swaps > k) break;
                int max_ones = 0;
                max_ones = max(max_ones, (s == 0 ? 0 : dp_pref[s-1][k - num_swaps][0]));
                max_ones = max(max_ones, (j == n-1 ? 0 : dp_suf[j+1][k - num_swaps][0]));
                combos.push_back({(j - s + 1), max_ones});
                if (j != n-1){
                    if (a[j+1] == 1) num_swaps++;
                }
            }
        }
        map<int,int> max_for_zeros;
        for (int i = 0; i < combos.size(); i++){
            max_for_zeros[combos[i][0]] = max(max_for_zeros[combos[i][0]], combos[i][1]);
        }
        for (int x = 1; x <= n; x++){
            for (auto z : max_for_zeros){
                ans[x] = max(ans[x], z.first * x + z.second);
            }
            cout << ans[x] << " ";
        }
        cout << "\n";
    }
}