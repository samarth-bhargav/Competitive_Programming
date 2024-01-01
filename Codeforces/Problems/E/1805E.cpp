#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;
vector<int> adj[mxN];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    vector<array<int, 2>> edges;
    for (int i = 0; i < n-1; i++){
        int u, v; cin >> u >> v; u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
        edges.push_back({u, v});
    }
    vector<int> a(n);
    map<int,int> freq;
    for (int i = 0; i < n; i++){
        cin >> a[i];
        freq[a[i]]++;
    }
    auto it = --freq.end();
    while (it->second < 2){
        if (it == freq.begin()){
            for (int i = 0; i < n; i++){
                cout << 0 << "\n";
            }
            return 0;
        }
        it--;
    }
    if (it->second > 2){
        for (int i = 0; i < n-1; i++){
            cout << it->first << "\n";
        }
        return 0;
    }
    int mad = it->first;
    //find path between two vertices
    vector<int> prev(n, -1);
    vector<bool> visited(n, false);
    int start = -1, finish = -1;
    for (int i = 0; i < n; i++){
        if (a[i] == it->first){
            if (start == -1){
                start = i;
            }
            else{
                finish = i;
            }
        }
    }
    queue<int> bfs; bfs.push(start);
    visited[start] = true;
    while (!bfs.empty()){
        int tp = bfs.front(); bfs.pop();
        for (int nxt : adj[tp]){
            if (!visited[nxt]){
                bfs.push(nxt);
                visited[nxt] = true;
                prev[nxt] = tp;
            }
        }
    }
    vector<int> path; path.push_back(finish);
    do{
        finish = prev[finish];
        path.push_back(finish);
    } while (finish != start);

    set<int> path_nodes(path.begin(), path.end());
    reverse(path.begin(), path.end());
    finish = path.front();

    int lb = 0;
    for (auto pr : freq){
        if (pr.second > 2){
            lb = pr.first;
        }
    }
    vector<vector<int>> subtree(path.size());
    vector<vector<int>> dp(n);
    auto dfs = [&](auto self, int u, int v) -> void{
        vector<vector<int>> res;
        if (freq[a[u]] == 2){
            res.push_back({a[u]});
        }
        for (int neighbor : adj[u]){
            if (neighbor != v && !path_nodes.count(neighbor)){
                self(self, neighbor, u);
                res.push_back(dp[neighbor]);
                dp[neighbor].clear(); dp[neighbor].shrink_to_fit();
            }
        }
        sort(res.begin(), res.end(), [&](vector<int> a, vector<int> b){
            return a.size() < b.size();
        });
        for (int i = res.size()-1; i > 0; i--){
            for (int x : res[i-1]){
                res[i].push_back(x);
            }
            res[i-1].clear(); res[i-1].shrink_to_fit();
            swap(res[i-1], res[i]);
        }
        if (res.empty()){
            dp[u] = {};
            return;
        }
        swap(res[0], dp[u]);
    };
    for (int i = 0; i < path.size(); i++){
        dfs(dfs, path[i], -1);
        swap(subtree[i], dp[path[i]]);
    }
    map<int, vector<int>> occ;
    for (int i = 0; i < path.size(); i++){
        for (int x : subtree[i]){
            occ[x].push_back(i);
        }
    }
    vector<int> l_upd(path.size(), -1), r_upd(path.size(), -1);
    for (auto pr : occ){
        assert(pr.second.size() == 2);
        if (pr.second[0] != 0){
            l_upd[pr.second[0]] = max(l_upd[pr.second[0]], pr.first);
        }
        if (pr.second[1] != path.size()-1){
            r_upd[pr.second[1]] = max(r_upd[pr.second[1]], pr.first);
        }
    }
    vector<int> final(path.size()-1, -1);
    int running = -1;
    for (int i = 0; i < path.size()-1; i++){
        running = max(running, r_upd[i]);
        final[i] = max(final[i], running);
    }
    running = -1;
    for (int i = path.size()-2; i >= 0; i--){
        running = max(running, l_upd[i+1]);
        final[i] = max(final[i], running);
    }
    map<array<int, 2>, int> ans;
    for (int i = 1; i < path.size(); i++){
        ans[{path[i-1], path[i]}] = max(lb, final[i-1]);
        ans[{path[i], path[i-1]}] = max(lb, final[i-1]);
    }
    for (array<int, 2> edge : edges){
        if (ans.count(edge)){
            cout << ans[edge] << "\n";
        }
        else{
            cout << mad << "\n";
        }
    }
}