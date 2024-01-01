#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        vector<int> dp;
        int ans = 0;
        for (int i : a) {
            int pos = lower_bound(dp.begin(), dp.end(), i) - dp.begin();
            if (pos == dp.size()) {
                // we can have a new, longer increasing subsequence!
                dp.push_back(i);
            } else {
                // oh ok, at least we can make the ending element smaller
                dp[pos] = i;
            }
            if (pos == 1){
                ans++;
            }
        }
        cout << ans << "\n";
    }
}