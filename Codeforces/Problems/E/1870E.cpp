#include <bits/stdc++.h>

using namespace std;

const int mxN = 5002;
const int INF = 1e9;
int mex[mxN][mxN], loose_r[mxN][mxN];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n+1; j++){
                mex[i][j] = 0;
                loose_r[i][j] = n;
            }
        }
        for (int i = 0; i < n; i++){
            vector<int> first_occ(n+1, n);
            for (int j = i; j < n; j++){
                first_occ[a[j]] = min(first_occ[a[j]], j);
            }
            for (int j = 1; j < first_occ.size(); j++){
                first_occ[j] = max(first_occ[j], first_occ[j-1]);
            }
            int curr_mex = 0;
            for (int j = i; j < n; j++){
                while (first_occ[curr_mex] <= j){
                    curr_mex++;
                }
                mex[i][j] = curr_mex;
            }
        }
        for (int i = 0; i < n; i++){
            for (int j = i; j < n; j++){
                loose_r[i][mex[i][j]] = min(loose_r[i][mex[i][j]], j);
            }
        }
        for (int m = 0; m < n+1; m++){
            for (int l = n-2; l >= 0; l--){
                loose_r[l][m] = min(loose_r[l][m], loose_r[l+1][m]);
            }
        }
        vector<vector<int>> dijkstra(n+1);
        vector<int> dist(n+1, INF);
        dist[0] = 0;

        dijkstra[0].push_back(0);

        vector<bool> vis(n+2, 0);
        for (int i = 0; i < n; i++){
            for (int j = 0; j < dijkstra[i].size(); j++){
                int node = dijkstra[i][j];
                if (vis[node]) continue;
                vis[node] = true;
                for (int k = 0; k <= n; k++){
                    if (vis[node ^ k]) continue;
                    if (dist[node ^ k] > loose_r[i][k] && loose_r[i][k] != n){
                        dist[node ^ k] = loose_r[i][k];
                        dijkstra[dist[node ^ k] + 1].push_back(node ^ k);
                    }
                }
            }
        }
        int ans = 0;
        for (int i = 0; i <= n; i++){
            if (dist[i] < n){
                ans = max(ans, i);
            }
        }
        cout << ans << "\n";
    }
}