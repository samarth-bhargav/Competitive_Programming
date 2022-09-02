#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e3;
const int M = 998244353;
vector<int> adj[mxN], anc[mxN], a(mxN), add(mxN);
vector<int> dp(mxN, -1);

int dfs(int curr){
    if (dp[curr] != -1){
        return dp[curr];
    }
    int ans = a[curr];
    for (auto & node : anc[curr]){
        if (a[node] != 0){
            ans = ((ans + dfs(node)) % M + M) % M;
        }
    }
    dp[curr] = ((ans + M) % M + M) % M;
    return ((ans + M) % M + M) % M;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--){
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        for (int i = 0; i < m; i++){
            int u, v;
            cin >> u >> v; u--; v--;
            adj[u].push_back(v);
            anc[v].push_back(u);
        }
        if (*max_element(a.begin(), a.begin() + n) == 0){
            cout << 0 << "\n";
            for (int i = 0; i < n; i++){
                adj[i].clear();
                anc[i].clear();
            }
            continue;
        }
        int sink = -1;
        for (int i = 0; i < n; i++){
            if (adj[i].empty()){
                sink = i;
                break;
            }
        }
        //simulate first n
        int sink_0 = -1;
        for (int s = 1; s <= n; s++){
            if (a[sink] != 0){
                sink_0 = -1;
            }
            for (int i = 0; i < n; i++){
                if (a[i] > 0){
                    for (auto & node : adj[i]){
                        add[node]++;
                    }
                    a[i]--;
                }
            }
            for (int i = 0; i < n; i++){
                a[i] += add[i];
                add[i] = 0;
            }
            if (a[sink] == 0 && sink_0 == -1){
                sink_0 = s;
            }
        }
        if (*max_element(a.begin(), a.begin() + n) == 0){
            if (sink_0 == -1){
                cout << n << "\n";
            }
            else{
                cout << sink_0 << "\n";
            }
            for (int i = 0; i < n; i++){
                adj[i].clear();
                anc[i].clear();
            }
            continue;
        }
        cout << ((dfs(sink) + n) % M + M) % M << "\n";
        fill(dp.begin(), dp.begin() + n, -1);
        for (int i = 0; i < n; i++){
            adj[i].clear();
            anc[i].clear();
        }
    }
}
