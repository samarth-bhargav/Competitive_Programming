#include <bits/stdc++.h>

using namespace std;

const int LOG = 21;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m; cin >> n >> m;
    map<array<int, 2>, char> ans;

    vector<vector<int>> adj(n, vector<int>());
    vector<array<int, 2>> edges(m);
    for (int i = 0; i < m; i++){
        cin >> edges[i][0] >> edges[i][1];
        edges[i][0]--; edges[i][1]--;
        if (edges[i][0] != edges[i][1]){
            adj[edges[i][0]].push_back(edges[i][1]);
            adj[edges[i][1]].push_back(edges[i][0]);
        }
        else{
            ans[edges[i]] = 'B';
        }
    }
    int p; cin >> p;
    vector<vector<int>> out(n), in(n);
    for (int i = 0; i < p; i++){
        int u, v; cin >> u >> v; u--; v--;
        if (u == v) continue;
        out[u].push_back(v);
        in[v].push_back(u);
    }

    vector<bool> vis(n, false);

    vector<vector<int>> out_back_edges(n), in_back_edges(n);
    vector<vector<int>> main_tree(n);
    vector<vector<int>> anc(n, vector<int>(LOG, -1));

    int time = 0;
    vector<int> tin(n, -1), tout(n, -1);

    auto dfs_tree = [&](auto self, int u, int parent) -> void{
        vis[u] = true;
        tin[u] = time++;

        anc[u][0] = parent;
        for (int b = 1; b < LOG; b++){
            if (anc[u][b-1] == -1) break;
            anc[u][b] = anc[anc[u][b-1]][b-1];
        }

        for (int v : adj[u]){
            if (v == parent) continue;
            if (!vis[v]){
                main_tree[u].push_back(v);
                main_tree[v].push_back(u);
                self(self, v, u);
            }
            else{
                if (tout[v] != -1){
                    //meaning v is a descendant
                    in_back_edges[u].push_back(v);
                    out_back_edges[v].push_back(u);
                }
                ans[{u, v}] = 'B';
                ans[{v, u}] = 'B';
            }
        }
        tout[u] = time++;
    };

    auto lca = [&](int u, int v) -> int{
        if (tin[u] <= tin[v] && tout[v] <= tout[u]){
            return u;
        }
        if (tin[v] <= tin[u] && tout[u] <= tout[v]){
            return v;
        }
        for (int b = LOG-1; ~b; b--){
            int ancestor = anc[u][b];
            if (ancestor == -1){
                continue;
            }
            if (tin[ancestor] <= tin[v] && tout[v] <= tout[ancestor]){
                continue;
            }
            u = ancestor;
        }
        return anc[u][0];
    };

    vector<int> to_process(n, 0);

    //{backedges, out_p_active, in_p_active}
    auto dfs = [&](auto self, int u, int v) -> array<int, 3>{
        int out_p_active = 0, in_p_active = 0;
        int active_back_edges = 0;
        for (int node : main_tree[u]){
            if (node != v){
                array<int, 3> ret = self(self, node, u);
                active_back_edges += ret[0];
                out_p_active += ret[1];
                in_p_active += ret[2];
            }
        }
        if (v == -1) return {-1, -1, -1};
        active_back_edges += out_back_edges[u].size();
        active_back_edges -= in_back_edges[u].size();
        for (int node : out[u]){
            out_p_active++;
            to_process[lca(node, u)]++;
        }
        for (int node : in[u]){
            in_p_active++;
            to_process[lca(node, u)]++;
        }
        assert(to_process[u] % 2 == 0);
        out_p_active -= to_process[u] / 2;
        in_p_active -= to_process[u] / 2;
//        cerr << "u, v: " << u << " " << v << " backedges = " << active_back_edges << " in_p_active: " << in_p_active << " out_p_active: " << out_p_active << endl;
        if (active_back_edges > 0){
            ans[{u, v}] = 'B';
            ans[{v, u}] = 'B';
        }
        else{
            //we found a bridge
            if (in_p_active > 0 && out_p_active > 0){
                assert(false);
            }
            assert(!(in_p_active > 0 && out_p_active > 0));
            if (in_p_active > 0){
                ans[{u, v}] = 'L';
                ans[{v, u}] = 'R';
            }
            else{
                if (out_p_active > 0){
                    ans[{u, v}] = 'R';
                    ans[{v, u}] = 'L';
                }
                else{
                    ans[{u, v}] = 'B';
                    ans[{v, u}] = 'B';
                }
            }
        }
        return {active_back_edges, out_p_active, in_p_active};
    };


    for (int i = 0; i < n; i++){
        if (!vis[i]){
            int root = i;
            dfs_tree(dfs_tree, root, -1);
            dfs(dfs, root, -1);
            time = 0;
        }
    }

//    cout << lca(2, 8) << "\n";

    for (int i = 0; i < m; i++){
        cout << ans[edges[i]];
    }
    cout << "\n";
}