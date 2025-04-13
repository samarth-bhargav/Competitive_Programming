#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, t, m; cin >> n >> t >> m; t--; m--;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n-1; i++){
        int a, b; cin >> a >> b; a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<vector<int>> children(n);
    vector<int> moves_above(n);
    vector<int> dp(n);
    vector<int> path_to_m;

//    cerr << "hi" << endl;

    auto dfs_init = [&](auto self, int u, int v) -> bool{
        bool m_in_subtree = false;
        if (u == m) m_in_subtree = true;
        for (int neighbor : adj[u]){
            if (neighbor != v){
                children[u].push_back(neighbor);
                m_in_subtree |= self(self, neighbor, u);
            }
        }
        if (m_in_subtree){
            path_to_m.push_back(u);
        }
        return m_in_subtree;
    };

    dfs_init(dfs_init, t, -1);

//    cerr << "dfs_init" << endl;

    auto dfs_actual = [&](auto self, int u, int ma) -> void{
        moves_above[u] = ma;
        if (u != t){
            ma += children[u].size() - 1;
        }

        vector<int> children_dp;
        for (int neighbor : children[u]){
            self(self, neighbor, ma);
            children_dp.push_back(dp[neighbor]);
        }
        sort(children_dp.begin(), children_dp.end());
        if (children_dp.empty()){
            dp[u] = 0;
        }
        else if (children_dp.size() == 1){
            dp[u] = 1;
        }
        else{
            dp[u] = children_dp[children_dp.size() - 2] + children_dp.size() - 1 + 1;
        }
    };

    dfs_actual(dfs_actual, t, 0);

//    cerr << "dfs_actual" << endl;

    auto ok = [&](int mid){
        int free = 0; //number of restrictions can place
        for (int i = 0; i < path_to_m.size() - 1; i++){
            free++;
            int node = path_to_m[i];
            vector<int> children_dp;
            for (int child : children[node]){
                if (i == 0){
                    children_dp.push_back(dp[child] + children[node].size() - 1 + moves_above[node] + 1);
                }
                else{
                    if (child != path_to_m[i-1]){
                        children_dp.push_back(dp[child] + children[node].size() - 2 + moves_above[node] + 1);
                    }
                }
            }
            if (children_dp.size() == 0){}
            else{
                sort(children_dp.begin(), children_dp.end());
                int sub_from_mid = 0;
                while (children_dp.size() && children_dp.back() > mid){
                    children_dp.pop_back(); free--; sub_from_mid++;
                    if (free < 0) return false;
                }
                mid -= sub_from_mid;
            }
            if (free < 0) return false;
        }
        if (mid < 0) return false;
        return true;
    };

    int lo = 0, hi = 1e9;
    while (lo < hi){
        int mid = (lo + hi) / 2;
        if (ok(mid)){
            hi = mid;
        }
        else{
            lo = mid + 1;
        }
    }
    cout << lo << "\n";
}