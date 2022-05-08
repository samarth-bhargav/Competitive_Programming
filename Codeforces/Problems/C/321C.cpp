#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5+1;
vector <int> adj[mxN];
bool cat[mxN];
int n, m;

int ans = 0;

void dfs(int child, int ancestor, int count){
    if (adj[child].size() == 1 && adj[child][0] == ancestor){
        ans++;
        return;
    }
    for (auto & i : adj[child]){
        if (i != ancestor && count+cat[i] <= m){
            if (!cat[i]){
                dfs(i, child, 0);
            }
            else{
                dfs(i, child, count+1);
            }
        }
    }
}
int main(){
    cin >> n >> m;
    for (int i = 1; i <= n; i++){
        cin >> cat[i];
    }
    int t;
    cin >> t;
    for (int i = 0; i < n-1; i++){
        int a,b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1, 1e9, cat[1]);
    cout << ans << "\n";
}