#include <bits/stdc++.h>

using namespace std;

#define int long long
const int mxN = 100;
vector<pair<int,int>> adj[mxN];
int adjmat[mxN][mxN];
const int INF = 1e18;

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m; cin >> n >> m;
    memset(adjmat, -1, sizeof(adjmat));
    for (int i = 0; i < m; i++){
        int u, v, y;
        cin >> u >> v >> y; u--; v--;
        adj[u].push_back({v, y});
        adj[v].push_back({u, y});
        adjmat[u][v] = y;
        adjmat[v][u] = y;
    }
    //check infinity condition
    if (adj[n-1].empty() || adj[0].empty()){
        cout << "inf\n";
        return 0;
    }
    set<int> active;
    for (int i = 0; i < n-1; i++){
        active.insert(i);
    }
    set<int> removed = {n-1};
    vector<pair<string, int>> ans;
    int totTime = 0;
    while (true){
        int minLink = INF;
        for (int u : active){
            for (int v : removed){
                if (adjmat[u][v] >= 0){
                    minLink = min(minLink, adjmat[u][v]);
                }
            }
        }
        totTime += minLink;
        string s(n, '0');
        for (int u : active){
            s[u] = '1';
        }
        ans.push_back({s, minLink});
        set<int> toRemove;
        for (int u : active){
            for (int v : removed){
                if (adjmat[u][v] == minLink){
                    toRemove.insert(u);
                }
                adjmat[u][v] -= minLink;
            }
        }
        if (toRemove.empty()){
            cout << "inf\n";
            return 0;
        }
        for (int u : toRemove){
            active.erase(u);
            removed.insert(u);
        }
        if (removed.count(0)){
            break;
        }
    }
    cout << totTime << " " << ans.size() << "\n";
    for (pair<string, int> q : ans){
        cout << q.first << " " << q.second << "\n";
    }
}