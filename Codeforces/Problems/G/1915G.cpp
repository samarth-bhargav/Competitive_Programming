#include <bits/stdc++.h>

using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n, m; cin >> n >> m;
        vector<vector<int>> adj(n);
        int w[n][n];
        memset(w, 0x3f, sizeof(w));
        int INF = w[0][0];
        for (int i = 0; i < m; i++){
            int a, b, wt; cin >> a >> b >> wt; a--; b--;
            if (w[a][b] == INF){
                adj[a].push_back(b);
                adj[b].push_back(a);
            }
            w[a][b] = min(w[a][b], wt);
            w[b][a] = min(w[a][b], wt);
        }
        int s[n];
        for (int i = 0; i < n; i++){
            cin >> s[i];
        }
        int dp[n][n];
        memset(dp, 0x3f, sizeof(dp));
        set<array<int, 3>> q;
        dp[0][0] = 0;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                q.insert({dp[i][j], i, j});
            }
        }
        while (!q.empty()){
            array<int, 3> tp = *q.begin();
            q.erase(tp);
            int wt = tp[0], u = tp[1], bk = tp[2];
            for (int v : adj[u]){
                if (wt + s[bk] * w[u][v] < dp[v][bk]){
                    q.erase({dp[v][bk], v, bk});
                    dp[v][bk] = wt + s[bk] * w[u][v];
                    q.insert({dp[v][bk], v, bk});
                }
                if (wt + s[bk] * w[u][v] < dp[v][v]){
                    q.erase({dp[v][v], v, v});
                    dp[v][v] = wt + s[bk] * w[u][v];
                    q.insert({dp[v][v], v, v});
                }
            }
        }
        int ans = 1e18;
        for (int i = 0; i < n; i++){
            ans = min(ans, dp[n-1][i]);
        }
        cout << ans << "\n";
    }
}