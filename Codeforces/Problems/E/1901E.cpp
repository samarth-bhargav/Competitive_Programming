#include <bits/stdc++.h>

using namespace std;

#define int long long

const int INF = 1e18;

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        vector<vector<int>> adj(n);
        for (int i = 0; i < n-1; i++){
            int u, v; cin >> u >> v; u--; v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<int> dp(n, -INF);
        int ans = 0;
        auto dfs = [&](auto self, int u, int v, bool root = false) -> void{
            vector<int> children;
            for (int child : adj[u]){
                if (child ^ v){
                    self(self, child, u);
                    children.push_back(child);
                }
            }
            vector<int> children_dp;
            for (int child : children){
                children_dp.push_back(dp[child]);
            }
            sort(children_dp.begin(), children_dp.end());

            if (adj[u].size() == 1){
                dp[u] = a[u];
            }
            else if (adj[u].size() == 2){
                dp[u] = max(dp[children[0]], a[u]); //can choose to either keep current, or to delete & go next
            }
            else{
                //option 1: keep stable while keeping children
                int sum = a[u];
                for (int i = 0; i < children_dp.size(); i++){
                    int c = children_dp[i];
                    if (c < 0 && children_dp.size() - i - 1 > 1){
                        continue;
                    }
                    else{
                        sum += c;
                    }
                }
                dp[u] = max(dp[u], sum);
                //option 2: remove everything, only keep a[i]
                dp[u] = max(dp[u], a[u]);
                //option 3: make i degree 2, then take one dp[child]
                dp[u] = max(dp[u], children_dp.back());
            }

            //computing answer if u is the root

            if (children_dp.size() == 0){
                ans = max(ans, a[u]);
            }
            else if (children_dp.size() == 1){
                ans = max(ans, max({dp[children[0]], a[u], a[u] + dp[children[0]]}));
            }
            else if (children_dp.size() == 2){
                //option 1: keep a[i]
                ans = max(ans, a[u] + children_dp.back());
                //option 2 remove a[i]
                ans = max(ans, max({dp[u], dp[children[0]] + dp[children[1]], dp[children[0]], dp[children[1]]}));
            }
            else{
                //option 1: keep stable while keeping children
                int sum = a[u];
                for (int i = 0; i < children_dp.size(); i++){
                    int c = children_dp[i];
                    if (c < 0 && children_dp.size() - i - 1 > 2){
                        continue;
                    }
                    else{
                        sum += c;
                    }
                }
                ans = max(ans, sum);
                //option 2: remove everything, only keep a[i] and biggest child
                ans = max(ans, a[u] + children_dp.back());
                //option 3: make a[i] degree 2 to take max 2 children
                ans = max(ans, children_dp.back() + children_dp[children_dp.size() - 2]);
            }
        };
        dfs(dfs, 0, -1, true);
        cout << ans << "\n";
    }
}