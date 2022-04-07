#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mxN = 1e5;

struct dsu{
    int sz[mxN],p[mxN];
    void init(){
        for (int i = 0; i < mxN; i++){
            p[i] = i; sz[i] = 1;
        }
    }
    int find(int x){
        return x^p[x]?p[x]=find(p[x]):x;
    }
    void join(int a, int b){
        a = find(a);
        b = find(b);
        p[b] = a;
        sz[a] += sz[b];
    }
} d;

vector<int>adj[mxN];
bool vis[mxN];

bool dfs(int u, int v) {
    if (vis[u]){
        return true;
    }
    vis[u] = true;
    bool x = false;
    for (auto & i : adj[u]){
        if (i != v){
            x |= dfs(i,u);
        }
    }
    return x;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,m;
    cin >> n >> m;
    d.init();
    for (int i = 0; i < m; i++){
        int a,b;
        cin >> a >> b; a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
        d.join(a,b);
    }
    set<int>components;
    for (int i = 0; i < n; i++){
        components.insert(d.find(i));
    }
    int ans = 0;
    for (auto & i : components){
        if (!dfs(i,i)){
            ans++;
        }
        memset(vis,false,sizeof(vis));
    }
    cout << ans << "\n";
}

