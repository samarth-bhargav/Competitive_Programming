#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m; cin >> n >> m;

    vector<array<int, 3>> edges; //label, a, b
    vector<vector<int>> adj(n);
    vector<vector<int>> radj(n);

    vector<int> in_deg(n);
    for (int i = 0; i < m; i++){
        int a, b, l; cin >> a >> b >> l; a--; b--;
        edges.push_back({l, a, b});
        adj[a].push_back(b);
        radj[b].push_back(a);
        in_deg[b]++;
    }
    vector<int> roots;
    for (int i = 0; i < n; i++){
        if (in_deg[i] == 0){
            roots.push_back(i);
        }
    }
    queue<int> q;
    vector<int> topo_sort;

    for (int x : roots) q.push(x);
    while (!q.empty()){
        int tp = q.front(); q.pop();
        topo_sort.push_back(tp);
        for (int x : adj[tp]){
            in_deg[x]--;
            if (in_deg[x] == 0){
                q.push(x);
            }
        }
    }
    reverse(topo_sort.begin(), topo_sort.end());
    vector<int> distances(n, 0);
    for (int i = 0; i < n; i++){
        for (int x : adj[topo_sort[i]]){
            distances[topo_sort[i]] = max(distances[topo_sort[i]], distances[x] + 1);
        }
    }
//    for (int i = 0; i < n; i++){
//        cout << distances[i] << "\n";
//    }
    sort(edges.begin(), edges.end());
    vector<bool> completed(n, false);

    for (int i = 0; i < n; i++){
        if (adj[i].size() == 0){
            completed[i] = true;
        }
    }

    vector<ll> sum(n, 0);

    for (int i = 0; i < n; i++){
        adj[i].clear(); adj[i].shrink_to_fit();
    }

    vector<array<int, 3>> new_edges;

    for (int i = 0; i < m; i++){
        if (distances[edges[i][0]] == distances[edges[i][1]] + 1){
            new_edges.push_back(edges[i]);
        }
    }

    edges = new_edges;

    vector<vector<array<int, 2>>> rev_aux_adj(n);

    auto dfs = [&](auto self, int u)-> void{
        for (array<int, 2> x : rev_aux_adj[u]){
            int v = x[0], l = x[1];
            if (completed[v]) continue;
            if (distances[v] == distances[u] + 1){
                completed[v] = true;
                sum[v] = sum[u] + l;
                self(self, v);
            }
        }
    };

    for (int i = 0; i < m; i++){
        array<int, 3> edge = edges[i];
        int l = edge[0], a = edge[1], b = edge[2];
        rev_aux_adj[b].push_back({a, l});

    }

    for (int i = 0; i < n; i++){
        cout << distances[i] << " " << sum[i] << "\n";
    }
}