#include <bits/stdc++.h>
using namespace std;

#define int long long

struct st {
    vector<int> T; int n;
    st(int n) : T(2 * n, (int)-2e9), n(n) {}

    void upd(int pos, int val) {
        for (T[pos += n] = val; pos > 1; pos /= 2)
            T[pos / 2] = max(T[pos], T[pos ^ 1]);
    }

    int query(int b, int e) {
        int res = -2e9;
        for (b += n, e += n; b < e; b /= 2, e /= 2) {
            if (b % 2) res = max(res, T[b++]);
            if (e % 2) res = max(res, T[--e]);
        }
        return res;
    }
};

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    for (int tt = 0; tt < t; tt++){
        int n, m, k; cin >> n >> m >> k;
        vector<array<int, 2>> intervals(m);
        for (int i = 0; i < m; i++){
            cin >> intervals[i][0] >> intervals[i][1];
        }
        sort(intervals.begin(), intervals.end());
        set<array<int, 2>> active_endpoints; //pos, idx
        int curr_idx = 0;

        vector<vector<int>> cover(n+1);
        set<int> invalid;

        for (int i = 1; i <= n; i++){
            while (curr_idx < m && intervals[curr_idx][0] <= i){
                active_endpoints.insert({intervals[curr_idx][1], curr_idx});
                curr_idx++;
            }
            while (!active_endpoints.empty() && (*active_endpoints.begin())[0] < i){
                active_endpoints.erase(active_endpoints.begin());
            }
            if (active_endpoints.size() <= k){
                for (auto arr : active_endpoints){
                    cover[i].push_back(intervals[arr[1]][0]);
                }
                sort(cover[i].rbegin(), cover[i].rend());
            }
            else{
                invalid.insert(i);
            }
        }
        vector<st> dp_at_k(k+1, st(n+1));
        vector<vector<int>> dp(n+1, vector<int>(k+1, -2e9));
        for (int i = 0; i <= k; i++){
            dp[0][i] = 0;
            dp_at_k[i].upd(0, 0);
        }
        for (int i = 1; i <= n; i++){
            if (invalid.count(i)) continue;
            for (int j = 0; j <= k; j++){
                //find max(dp_k,j-x + 1)
                for (int x = 0; x <= cover[i].size(); x++){
                    int lb = (x == cover[i].size() ? 0 : cover[i][x]);
                    int rb = (x == 0 ? i - 1 : cover[i][x-1]-1);
                    if (lb > rb) continue;
                    if (j - x >= 0){
                        dp[i][j] = max(dp[i][j], dp_at_k[j-x].query(lb, rb+1) + 1);
                    }
                }
                dp_at_k[j].upd(i, dp[i][j]);
            }
        }
        int ans = -2e9;
        for (int j = 0; j <= k; j++){
            ans = max(ans, dp_at_k[j].query(0, n+1));
        }
        cout << ans << "\n";
    }
}