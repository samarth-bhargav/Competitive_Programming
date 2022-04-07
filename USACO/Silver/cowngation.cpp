#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5+5;
vector<int>adj[mxN];
long long n, ans = 0;

void dfs(int edge, int ancestor){
    int init = 1;
    if (adj[edge].size() == 1 && edge != 1){
        return;
    }
    for (int i = 0; i < 18; i++){
        init*=2;
        ans++;
        if (init >= adj[edge].size()+(edge==1)){
            break;
        }
    }
    for (auto & i : adj[edge]){
        if (i != ancestor){
            ans++;
            dfs(i,edge);
        }
    }
}

int main(){
    cin >> n;
    for (int i = 0; i < n-1; i++){
        int a,b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1,1);
    cout << ans << "\n";
}
