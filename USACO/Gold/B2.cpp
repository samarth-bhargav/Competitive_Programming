#include <bits/stdc++.h>

using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m; cin >> n >> m;

    vector<array<int, 3>> edges; //label, a, b
    vector<vector<int>> adj(n);
    vector<vector<array<int, 2>>> w_adj(n);

    set<int> labels;

    vector<int> in_deg(n, 0);
    for (int i = 0; i < m; i++){
        int a, b, l; cin >> a >> b >> l; a--; b--;
        w_adj[a].push_back({b, l});
        adj[a].push_back(b);
        labels.insert(l);
        edges.push_back({a, b, l});
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
            assert(in_deg[x] >= 0);
            if (in_deg[x] == 0){
                q.push(x);
            }
        }
    }
    reverse(topo_sort.begin(), topo_sort.end());
    vector<int> distances(n, 0);
    vector<int> sums(n, 0);
    vector<array<int, 2>> descendant(n);

    for (int i = 0; i < n; i++){
        for (int x : adj[topo_sort[i]]){
            distances[topo_sort[i]] = max(distances[topo_sort[i]], distances[x] + 1);
        }
        int best = -1, best_l = 1e9+1;

        if (labels.size() == 1 || labels.size() == m){
            for (array<int, 2> arr : w_adj[topo_sort[i]]){
                int u = arr[0], l = arr[1];
                if (distances[topo_sort[i]] == distances[u] + 1){
                    if (l < best_l){
                        best_l = l; best = u;
                    }
                }
            }
            if (best == -1){
                sums[topo_sort[i]] = 0; continue;
            }
            sums[topo_sort[i]] = sums[best] + best_l;
            continue;
        }
        vector<int> poss;
        int initial_best_l = -1;
        for (array<int, 2> arr : w_adj[topo_sort[i]]){
            int u = arr[0], l = arr[1];
            if (distances[topo_sort[i]] == distances[u] + 1){
                if (l < best_l){
                    best_l = l; best = u;
                    poss = {u};
                }
                else if (l == best_l){
                    poss.push_back(u);
                }
            }
        }

        initial_best_l = best_l;
        vector<int> ascendant(n);
        for (int x : poss){
            ascendant[x] = topo_sort[i];
        }

        for (int j = 0; j < distances[topo_sort[i]] - 1; j++){
            vector<int> new_poss;
            best_l = 1e9+1;
            for (int x : poss){
                array<int, 2> d = descendant[x];
                if (d[1] < best_l){
                    best_l = d[1];
                    ascendant[d[0]] = x;
                }
            }
            for (int x : poss){
                array<int, 2> d = descendant[x];
                if (d[1] == best_l){
                    new_poss.push_back(d[0]);
                }
            }
            swap(new_poss, poss);
        }
        if (!poss.empty()){
            int tp = poss[0];
            vector<bool> vis(n, false);
            while (ascendant[tp] != topo_sort[i]){
                assert(!vis[tp]);
                vis[tp] = true;
                tp = ascendant[tp];
            }
            descendant[topo_sort[i]] = {tp, initial_best_l};
            sums[topo_sort[i]] = initial_best_l + sums[tp];
        }
        else{
            sums[topo_sort[i]] = 0;
        }
    }

    for (int i = 0; i < n; i++){
        cout << distances[i] << " " << sums[i] << "\n";
    }
    return 0;
    //try n,m = 5000?

}
