#include <bits/stdc++.h>

using namespace std;

void solve(){
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++){
        char c; cin >> c;
        a[i] = c - '0';
    }
    map<array<int, 2>, int> edges_to_idx;
    vector<set<int>> adj(n);
    vector<int> deg(n, 0);
    for (int i = 0; i < n; i++){
        int x; cin >> x; x--;
        adj[i].insert(x);
        deg[i]++; deg[x]++;
        edges_to_idx[{i, x}] = i;
        edges_to_idx[{x, i}] = i;
    }
    queue<int> q;
    for (int i = 0; i < n; i++){
        if (deg[i] == 1){
            q.push(i);
        }
    }
    vector<int> ops;
    while (!q.empty()){
        int tp = q.front(); q.pop();
        int nbr = *adj[tp].begin();
        if (a[tp] != 0){
            ops.push_back(edges_to_idx[{tp, nbr}]);
            a[tp] ^= 1; a[nbr] ^= 1;
        }
        deg[tp]--; deg[nbr]--;
        adj[nbr].erase(tp); adj[tp].erase(nbr);
        if (deg[nbr] == 1){
            q.push(nbr);
        }
    }
    //should be cycle decomp now....
    for (int i = 0; i < n; i++){
        assert(deg[i] == 0 || deg[i] == 2);
        if (deg[i] == 0 && a[i] != 0){
            cout << -1 << "\n";
            return;
        }
    }
    vector<bool> vis(n+1, false);
    for (int i = 0; i < n; i++){
        if (deg[i] == 2 && !vis[i]){
            int node = i;
            vector<int> plusses;
            //a_{m-1}+a0, a0+a1, .....
            vector<int> edge_nums;
            //a0, a1, .....
            while (true){
                vis[node] = true;
                plusses.push_back(a[node]);
                if (adj[node].empty()){
                    edge_nums.push_back(edges_to_idx[{node, i}]);
                    break;
                }
                int nbr = *adj[node].begin();
                edge_nums.push_back(edges_to_idx[{node, nbr}]);
                if (vis[nbr]){
                    break;
                }
                adj[node].erase(nbr);
                adj[nbr].erase(node);
                node = nbr;
            }
            //set a_{m-1} to be 0
            int m = plusses.size();
            vector<int> on(m, 0);
            //a0, a1, ....
            for (int j = 0; j < m-1; j++){
                on[j] = ((plusses[j] - on[((j-1)%m+m)%m]) % 2 + 2) % 2;
            }
            if (((plusses[m-1] - on[((m-2)%m+m)%m]) % 2 + 2) % 2 != 0){
                cout << -1 << "\n";
                return;
            }
            int tot = count(on.begin(), on.end(), 1);
            if (tot > m / 2){
                for (int j = 0; j < m; j++) on[j] ^= 1;
                tot = m - tot;
            }
            for (int j = 0; j < m; j++){
                if (on[j]){
                    ops.push_back(edge_nums[j]);
                }
            }
        }
    }
    cout << ops.size() << "\n";
    for (int i = 0; i < ops.size(); i++){
        cout << ops[i] + 1 << " ";
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        solve();
    }
}