#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m, k; cin >> n >> m >> k;
    vector<int> c(n);
    for (int i = 0; i < n; i++){
        cin >> c[i];
    }
    vector<vector<int>> adj(n, vector<int>());
    for (int i = 0; i < m; i++){
        int u, v; cin >> u >> v; u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int ans = 0;
    for (int s = 0; s < n; s++){
        queue<array<int, 3>> bfs;
        bool vis[n][2];
        int dist[n][2];
        memset(vis, 0, sizeof(vis));
        memset(dist, 0x3f, sizeof(dist));
        bfs.push({s, 0, 0});
        vis[s][0] = true;
        while (!bfs.empty()){
            array<int,3> tp = bfs.front(); bfs.pop();
            dist[tp[0]][tp[1]] = tp[2];
            for (int x : adj[tp[0]]){
                if (!vis[x][tp[1] ^ (c[x] != c[tp[0]])]){
                    bfs.push({x, tp[1] ^ (c[x] != c[tp[0]]), tp[2]+1});
                    vis[x][tp[1] ^ (c[x] != c[tp[0]])] = true;
                }
            }
        }
        for (int i = 0; i < n; i++){
            for (int hd = 0; hd <= k; hd++){
                ans = max(ans, min(hd + dist[i][0], k - hd + dist[i][1]));
            }
//            if (dist[i][0] == 0x3f3f3f3f || dist[i][1] == 0x3f3f3f3f){
//                ans = max(ans, k + min(dist[i][0], dist[i][1]));
//            }
//            else{
//                for
//                ans = max(ans, k / 2 + max(dist[i][0], dist[i][1]));
//            }
        }
//        cerr << s+1 << "\n";
//        for (int i = 0; i < n; i++){
//            for (int j = 0; j < 2; j++){
//                cerr << "i: " << i+1 << " j: " << j << " dist[i][j]: " << dist[i][j] << "\n";
//            }
//        }
    }
    cout << ans << "\n";
}