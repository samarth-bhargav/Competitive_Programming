#include <bits/stdc++.h>

using namespace std;

#define dbg(x) for (int a : x) {cout << a << " ";} cout << "\n";

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<vector<int>> adj(n);
        for (int i = 1; i < n; i++){
            int x; cin >> x; x--;
            adj[x].push_back(i);
        }
        vector<int> dp(n);
        vector<vector<int>> children(n);
        vector<int> sz(n, 1);
        auto dfs = [&](auto self, int u, int v) -> void{
            for (int neighbor : adj[u]){
                if (neighbor != v){
                    self(self, neighbor, u);
                    children[u].push_back(neighbor);
                }
            }
            for (int x : children[u]){
                sz[u] += sz[x];
            }
        };
        dfs(dfs, 0, -1);
        auto dfs2 = [&](auto self, int u, int v) -> int{
            vector<int> sizes;
            for (int child : children[u]){
                sizes.push_back(sz[child]);
            }
            if (sizes.empty()) return 0;
            sort(sizes.begin(), sizes.end());
            int best_node = -1;
            for (int child : children[u]){
                if (sz[child] == sizes.back()){
                    best_node = child; break;
                }
            }
            int tot = 0;
            int sum = accumulate(sizes.begin(), sizes.end(), 0LL);
            if (sizes.back() > sum / 2){
                tot += sum - sizes.back();
                tot += min((sizes.back() - (sum - sizes.back())) / 2, self(self, best_node, u));
            }
            else{
                tot = sum / 2;
            }
            return tot;
        };
        cout << dfs2(dfs2, 0, -1) << "\n";
    }
}