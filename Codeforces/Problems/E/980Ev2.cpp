#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e6;
const int mxL = 21;

vector<int> adj[mxN];
int dp[mxN][mxL];
bool keep[mxN];

void dfs(int e, int p){
    dp[e][0] = p;
    for (int i = 1; i < mxL; i++){
        if (dp[e][i-1] != -1) {
            dp[e][i] = dp[dp[e][i-1]][i-1];
        }
    }
    for (int n : adj[e]){
        if (n != p){
             dfs(n, e);
        }
    }
}

int dist_to_graph(int n){
    int ret = 0;
    while (dp[n][0] != -1){
        int i = 0;
        if (keep[dp[n][0]]){
            ret++;
            break;
        }
        for (; i < mxL; i++){
            if (dp[n][i] == -1 || keep[dp[n][i]]){
                i--;
                ret += 1 << i;
                n = dp[n][i];
                break;
            }
        }
    }
    return ret;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,k;
    cin >> n >> k;
    k = n-k;
    for (int i = 0; i < n-1; i++){
        int a,b;
        cin >> a >> b; a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    memset(dp, -1, sizeof(dp));
    memset(keep, 0, sizeof(keep));
    dfs(n-1, -1);
    keep[n-1] = true; k--;
    for (int i = n-2; i >= 0 && k > 0; i--){
        if (keep[i]){
            continue;
        }
        int dist = dist_to_graph(i);
        if (k - dist >= 0){
            for (int node = i; !keep[node]; node = dp[node][0]){
                keep[node] = true;
            }
            k -= dist;
        }
    }
    for (int i = 0; i < n; i++){
        if (!keep[i]){
            cout << i+1 << " ";
        }
    }
    cout << "\n";
}
