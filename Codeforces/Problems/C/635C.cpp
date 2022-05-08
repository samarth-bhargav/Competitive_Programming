/*
ID: samarth10
LANG: C++11
TASK: 
*/
#include <bits/stdc++.h>
using namespace std;


void setIO(string name) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen((name + ".in").c_str(), "r", stdin);
    freopen((name + ".out").c_str(), "w", stdout);
}

const int mxN = 2*1e5+5;
int subtree[mxN] = {0}, depth[mxN] = {0}, subtreeminusdepth[mxN], n, m;
vector <int> adj[mxN];

bool compare(int a, int b){
    return a > b;
}
int hi = 0, hi1 = 0, hi2 = 0, hi3 = 0, hi4 = 0, hi5 = 0, hi6 = 0;
int dfs(int e, int ancestor){
    depth[e] = depth[ancestor] + 1;
    subtree[e] = 0;
    if (adj[e].size() == 1 && e != 1){
        subtree[e] = 0;
        return 0;
    }
    else{
        for (auto edge : adj[e]){
            if (edge != ancestor){
                subtree[e] += dfs(edge, e);
            }
            else{
                continue;
            }
            subtree[e] += 1;
        }
    }
    return subtree[e];
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n-1; i++){
        int a,b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    depth[0] = -1;
    dfs(1,0);
    for (int i = 1; i <= n; i++){
        subtreeminusdepth[i] = depth[i]-subtree[i];
    }
    sort(subtreeminusdepth+1, subtreeminusdepth+n+1, compare);
    long long ans = 0;
    for (int i = 1; i <= m; i++){
        ans += subtreeminusdepth[i];
    }
    cout << ans << "\n";
}

