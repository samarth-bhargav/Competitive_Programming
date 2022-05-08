/*
Author: treewave
orz
*/
#include <bits/stdc++.h>

using namespace std;

const int mxN = 1e5 + 5;
int n;
bool match[mxN];
vector <int> adj[mxN];
set <int> ar[mxN];


void dfs1(int child, int ancestor, int init, int cnt){
    if (cnt == 1){
        ar[child].insert(ancestor);
        ar[child].insert(init);
        ar[init].insert(child);
        ar[ancestor].insert(child);
        return;
    }
    for (auto & i : adj[child]){
        if (i != ancestor){
            ar[child].insert(ancestor);
            ar[child].insert(init);
            ar[init].insert(child);
            ar[ancestor].insert(child);
            dfs1(i, child, init, cnt+1);
        }
    }
}
int main(){
    freopen("planting.in", "r", stdin);
    freopen("planting.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n-1; i++){
        int a,b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 1; i <= n; i++){
        dfs1(i,0,i,0);
    }
    int ans = 0;
    for (int i = 1; i <= n; i++){
        ans = max(ans, (int)ar[i].size()-1);
    }
    cout << ans << "\n";
}

