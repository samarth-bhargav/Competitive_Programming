#include <bits/stdc++.h>
using namespace std;

const int mxN = 5e4, mxK = 50;
const int INF = 1e9;

int dp[mxN]; bool vis[mxN], calc[mxN];
vector<int> reverse_adj[mxK];
vector<int> instances[mxK];
vector<int> b(mxN);

void dfs(int node){
    vis[node] = true;
    if (node == 0){
        return;
    }
    int ret = INF;
    for (auto &color : reverse_adj[b[node]]){
        for (auto &edge : instances[color]){
            if (vis[edge] && calc[edge]){
                //it's below && visited
                ret = min(ret, dp[edge] + abs(node - edge));
            }
            else if (vis[edge] && !calc[edge]){
                //it's above
                continue;
            }
            else if (!vis[edge]){
                //not visited
                dfs(edge);
                ret = min(ret, dp[edge] + abs(node - edge));
            }
        }
    }
    dp[node] = ret;
    calc[node] = true;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++){
        cin >> b[i]; b[i]--;
        instances[b[i]].push_back(i);
    }
    for (int i = 0; i < k; i++){
        for (int j = 0; j < k; j++){
            char c; cin >> c;
            if (c == '1'){
                reverse_adj[j].push_back(i);
            }
        }
    }
    fill(dp, dp+n, INF);
    memset(vis, 0, sizeof(vis));
    memset(calc, 0, sizeof(calc));
    dp[0] = 0; calc[0] = true; vis[0] = true;
    dfs(n-1);
    cout << (dp[n-1] == INF ? -1 : dp[n-1]) << "\n";
}
