#include <bits/stdc++.h>
using namespace std;

#define int long long
const int mxN = 1e5, M = 1e9+7;
vector<int> adj[mxN];
int dp[mxN][3];

void dfs(int e, int p){
    for (auto & node : adj[e]){
        if (node != p){
            dfs(node, e);
        }
    }
    for (int color = 0; color < 3; color++){
        if (dp[e][color] == 0){
            continue;
        }
        int temp = 1;
        for (auto & node : adj[e]){
            if (node != p){
                temp = ((temp * (dp[node][0] + dp[node][1] - dp[node][color] + dp[node][2])) % M + M) % M;
            }
        }
        dp[e][color] = ((temp % M) + M) % M;
    }
}

int32_t main(){
    ifstream cin("barnpainting.in");
    ofstream cout("barnpainting.out");
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n-1; i++){
        int a,b;
        cin >> a >> b; a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 0; i < n; i++){
        for (int c = 0; c < 3; c++){
            dp[i][c] = 1;
        }
    }
    for (int i = 0; i < k; i++){
        int b, c;
        cin >> b >> c; b--; c--;
        for (int node : adj[b]){
            dp[node][c] = 0;
        }
        for (int color = 0; color < 3; color++){
            if (color != c){
                dp[b][color] = 0;
            }
        }
    }
    dfs(0, -1);
    cout << ((dp[0][0] + dp[0][1] + dp[0][2]) % M + M) % M << "\n";
//    int x = M + M - M + M;
//    cerr << x << "\n";
}
