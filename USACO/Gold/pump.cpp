#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
 * Start with empty graph and sort edges based off of flow
 * Add edges to graph based in order of increasing flow
 * Calculate mincost using Dijkstra
 * If mincost changes, then the minflowrate also changes since you're now using that edge
 * Done
*/

#define int ll
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("pump.in", "r", stdin);
    freopen("pump.out", "w", stdout);
    int n,m;
    cin >> n >> m;
    vector<array<int,4>>edges(m);
    for (int i = 0; i < m; i++){
        int a,b,c,f;
        cin >> a >> b >> c >> f; a--; b--;
        edges[i][0] = f;
        edges[i][1] = c;
        edges[i][2] = a;
        edges[i][3] = b;
    }
    sort(edges.rbegin(),edges.rend());
    vector<pair<int,int>>adj[n];
    pair<int,int> ans = {-1e9, 1}; //(flow, cost)
    for (int i = 0; i < m; i++) {
        int f = edges[i][0];
        int c = edges[i][1];
        int a = edges[i][2], b = edges[i][3];
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
        int d[n];
        fill(d, d + n, 1e9);
        d[0] = 0;
        set<pair<int, int>> q;
        for (int j = 0; j < n; j++) {
            q.insert({d[j], j});
        }
        while (!q.empty()) {
            int v = q.begin()->second;
            q.erase(q.begin());

            for (auto e : adj[v]) {
                int to = e.first;
                int cost = e.second;
                if (d[to] > d[v] + cost) {
                    q.erase({d[to], to});
                    d[to] = d[v] + cost;
                    q.insert({d[to], to});
                }
            }
        }
        if (d[n - 1] != 1e9 && d[n - 1] != ans.second) {
            if ((1000000 * ans.first / ans.second) < (1000000 * f) / d[n - 1]) {
                ans.first = f;
                ans.second = d[n - 1];
            }
        }
    }
    cout << (1000000 * ans.first)/ans.second << "\n";
}

