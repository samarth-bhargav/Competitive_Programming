#include <bits/stdc++.h>
using namespace std;

const int mxN = 1.5e5+5;
vector<int>adj[mxN];
int n,m;
map<pair<int,int>,bool>vis;
bool visited[mxN];

struct dsu{
    int parent[mxN];
    long long sz[mxN];
    long long nodesz[mxN];
    void init(){
        for (int i = 1; i <= n; i++){
            parent[i] = i;
            sz[i] = 0;
            nodesz[i] = 1;
        }
    }
    int find(int x){
        return x^parent[x]?parent[x]=find(parent[x]):x;
    }
    void join(int a, int b){
        if (a == b){
            return;
        }
        int c = find(a);
        int d = find(b);
        if (c == d){
            sz[d]++;
            return;
        }
        parent[c] = d;
        sz[d] += sz[c]+1;
        nodesz[d] += nodesz[c];
    }
}d;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < m; i++){
        int a,b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    d.init();
    for (int i = 1; i <= n; i++){
        for (auto & j : adj[i]){
            d.join(i,j);
        }
    }
    for (int i = 1; i <= n; i++){
        if (d.sz[d.find(i)] != (d.nodesz[d.find(i)]-1)*(d.nodesz[d.find(i)])){
            cout << "NO\n";
            return 0;
        }
    }
    cout << "YES\n";
}