#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;
vector<int> ans(mxN), adj[mxN];
void dfs(int v, int p=0){
    ans[v] = (ans[p] > 0 ? -1 : 1) * adj[v].size();
    for (int x : adj[v]){
        if (x != p) dfs(x, v);
    }
}

int main(){
    int t;
    cin >> t;
    while (t--){
        int n;
        cin >> n;
        for (int i = 0; i < n-1; i++){
            int a, b;
            cin >> a >> b; a--; b--;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        ans[0] = adj[0].size();
        for (int c : adj[0]){
            dfs(c);
        }
        for (int i = 0; i < n; i++){
            cout << ans[i] << " ";
        }
        cout << "\n";
        for (int i = 0; i < n; i++){
            adj[i].clear();
        }
    }
}
