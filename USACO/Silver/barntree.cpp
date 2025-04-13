#include <bits/stdc++.h>

using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<vector<int>> adj(n);
    for (int i = 0; i < n-1; i++){
        int u, v; cin >> u >> v; u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> nodes_in_subtree(n, 1);
    vector<int> subtree_sum(a.begin(), a.end());
    vector<vector<int>> children(n);

    auto dfs = [&](auto self, int u, int v) -> void{
        for (int child : adj[u]){
            if (child != v){
                self(self, child, u);
                children[u].push_back(child);
            }
            nodes_in_subtree[u] += nodes_in_subtree[child];
            subtree_sum[u] += subtree_sum[child];
        }
    };

    dfs(dfs, 0, -1);
    int avg = subtree_sum[0] / n;

    int ans = 0;

    for (int i = 0; i < n; i++){
        int tot = 0;
        for (int child : children[i]){
            int correct = nodes_in_subtree[child] * avg;
            if (correct - subtree_sum[child] != 0){
                tot++;
            }
        }
        if (i != 0){
            int correct = (n - nodes_in_subtree[i]) * avg;
            if (correct - (subtree_sum[0] - subtree_sum[i]) != 0){
                tot++;
            }
        }
        ans += tot;
    }
    cout << (ans >> 1) << "\n";
}