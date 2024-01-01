#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int mxN = 2e5;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(array<int, 2> x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return (splitmix64(x[0] + FIXED_RANDOM) >> 1) + splitmix64(x[1] + FIXED_RANDOM);
    }
};

int n;
set<int> adj[mxN];
set<int> adj_cpy[mxN];
vector<int> ans(3 * mxN);
vector<int> dp(3 * mxN);
vector<array<int,2>> edge_to_real;
unordered_map<array<int, 2>, int, custom_hash> real_to_edge;
vector<bool> vis;
vector<int> dfs_order;
vector<int> rev_edge_dfs_order;
int global_k = -1;
int ops = 0;

void dfs(int edge){
    if (vis[edge]){
        return;
    }
    vis[edge] = true;
    int parent = edge_to_real[edge][0], node = edge_to_real[edge][1];
    if (parent != -1){
        adj[parent].erase(node);
    }
    if (dp[edge] != -INF){
        return;
    }
//    new_dfs_order.push_back(edge);
    bool removed_parent = false;
    while (!adj[node].empty()){
        int neighbor = *adj[node].begin();
        if (neighbor != parent){
            int edge_num = real_to_edge[{node, neighbor}];
            dfs(edge_num);
        }
        else{
            removed_parent = true;
            adj[node].erase(adj[node].begin());
        }
    }
    if (removed_parent){
        adj[node].insert(parent);
    }
    dfs_order.push_back(edge);
    return;
}

int ok(){
    vector<vector<int>> min_dp(n, {INF, INF, INF}); //stores minimum 3 dp for every vertex
    vector<vector<int>> ans_min(n, {INF, INF}); //stores minimum two answers for a particular node
    for (int i = 0; i < edge_to_real.size(); i++){
        int parent = edge_to_real[i][0], node = edge_to_real[i][1];
        if (adj[node].size() == 1 && parent != -1){
            dp[i] = 1;
            int v = parent, x = 1;
            if (min_dp[v][0] > x){
                swap(min_dp[v][1], min_dp[v][2]);
                swap(min_dp[v][0], min_dp[v][1]);
                min_dp[v][0] = x;
            }
            else if (min_dp[v][1] > x){
                swap(min_dp[v][1], min_dp[v][2]);
                min_dp[v][1] = x;
            }
            else if (min_dp[v][2] > x){
                min_dp[v][2] = x;
            }
        }
        else{
            dp[i] = -INF;
        }
        ans[i] = INF;
    }
    for (int i = 0; i < dfs_order.size(); i++){
        int parent = edge_to_real[dfs_order[i]][0], node = edge_to_real[dfs_order[i]][1];
        vector<int> dps = min_dp[node];
        ops += min_dp[node].size();
        auto it = find(dps.begin(), dps.end(), dp[rev_edge_dfs_order[i]]);
        if (parent != -1){
            if (it != dps.end()){
                dps.erase(it);
            }
        }
        vector<int> answers = ans_min[node];
//        assert(is_sorted(dps.begin(), dps.end()));
        it = find(answers.begin(), answers.end(), ans[rev_edge_dfs_order[i]]);
        if (parent != -1){
            if (it != answers.end()){
                answers.erase(it);
            }
        }
        dp[dfs_order[i]] = dps[0]+1;
        ans[dfs_order[i]] = min(dps[1], answers[0]);
        if (parent != -1){
            int v = parent, x = dp[dfs_order[i]];
            if (min_dp[v][0] > x){
                swap(min_dp[v][1], min_dp[v][2]);
                swap(min_dp[v][0], min_dp[v][1]);
                min_dp[v][0] = x;
            }
            else if (min_dp[v][1] > x){
                swap(min_dp[v][1], min_dp[v][2]);
                min_dp[v][1] = x;
            }
            else if (min_dp[v][2] > x){
                min_dp[v][2] = x;
            }
            x = ans[dfs_order[i]];
            if (ans_min[v][0] > x){
                swap(ans_min[v][0], ans_min[v][1]);
                ans_min[v][0] = x;
            }
            else if (ans_min[v][1] > x){
                ans_min[v][1] = x;
            }
        }
    }
    int final_ans = -1;
    for (int i = 0; i < edge_to_real.size(); i++){
        if (edge_to_real[i][0] == -1){
            final_ans = max(final_ans, min(dp[i], ans[i]));
        }
    }
    return final_ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        cin >> n;
        for (int i = 0; i < n; i++){
            edge_to_real.push_back({-1, i});
            real_to_edge[{-1, i}] = edge_to_real.size()-1;
        }
        for (int i = 0; i < n-1; i++){
            int u, v; cin >> u >> v; u--; v--;
            adj[u].insert(v);
            adj[v].insert(u);
            adj_cpy[u].insert(v);
            adj_cpy[v].insert(u);
            edge_to_real.push_back({u, v});
            real_to_edge[{u, v}] = edge_to_real.size()-1;
            edge_to_real.push_back({v, u});
            real_to_edge[{v, u}] = edge_to_real.size()-1;
        }
        vis = vector<bool> (edge_to_real.size(), false);
        for (int i = 0; i < edge_to_real.size(); i++){
            int parent = edge_to_real[i][0], node = edge_to_real[i][1];
            if (adj[node].size() == 1 && parent != -1){
                dp[i] = 1;
            }
            else{
                dp[i] = -INF;
            }
        }
        //get traversal order
        for (int i = 0; i < n; i++){
            if (!vis[i]){
                dfs(i);
            }
        }
        for (int i = 0; i < n; i++){
            adj[i] = adj_cpy[i];
        }
        for (int i = 0; i < dfs_order.size(); i++){
            if (edge_to_real[dfs_order[i]][0] == -1){
                rev_edge_dfs_order.push_back(0);
                continue;
            }
            rev_edge_dfs_order.push_back(real_to_edge[{edge_to_real[dfs_order[i]][1], edge_to_real[dfs_order[i]][0]}]);
        }
        cout << ok() << "\n";
        dfs_order.clear();
        rev_edge_dfs_order.clear();
        vis.clear(); vis.shrink_to_fit();
        for (int i = 0; i < n; i++){
            adj[i].clear();
            adj_cpy[i].clear();
//            adj[i].shrink_to_fit();
        }
        edge_to_real.clear();
        real_to_edge.clear();
    }
}
