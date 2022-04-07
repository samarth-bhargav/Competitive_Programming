/*
Author: treewave
orz
*/
#include <bits/stdc++.h>

using namespace std;


const int mxN = 1e5+5;
vector<int>adj[mxN];
pair<int,int>coords[mxN];
pair<int,int>lows[mxN];
pair<int,int>highs[mxN];
bool vis[mxN];
int n,k;

struct dsu{
    int parent[mxN];
    void init(){
        for (int i = 1; i <= n; i++){
            parent[i] = i;
            lows[i] = coords[i];
            highs[i] = coords[i];
        }
    }
    int find(int x){
        return x^parent[x]?parent[x]=find(parent[x]):x;
    }
    void join(int a, int b){
        int c = find(a);
        int d = find(b);
        parent[c] = d;
        lows[c].first = min(lows[c].first,lows[d].first);
        lows[c].second = min(lows[c].second,lows[d].second);
        lows[d].first = min(lows[c].first,lows[d].first);
        lows[d].second = min(lows[d].second,lows[c].second);
        highs[c].first = max(highs[c].first,highs[d].first);
        highs[c].second = max(highs[c].second,highs[d].second);
        highs[d].first = max(highs[c].first,highs[d].first);
        highs[d].second = max(highs[d].second,highs[c].second);
    }
    void solve(){
        int ans = 1<<30;
        for (int i = 1; i <= n; i++){
            int a = find(i);
            ans = min(ans,(highs[a].first-lows[a].first)*2+(highs[a].second-lows[a].second)*2);
        }
        cout << ans << "\n";
    }
}ans;

void dfs(int e, int u, int init){
    vis[e] = true;
    if (e != init){
        ans.join(e,u);
    }
    for (auto & i : adj[e]){
        if (!vis[i]){
            dfs(i,e,init);
        }
    }
}

int main() {
    freopen("fenceplan.in", "r", stdin);
    freopen("fenceplan.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= n; i++){
        cin >> coords[i].first >> coords[i].second;
    }
    ans.init();
    for (int i = 0; i < k; i++){
        int a,b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 1; i <= n; i++){
        if (!vis[i]){
            dfs(i,-1e9,i);
        }
    }
    ans.solve();
}

