#include <bits/stdc++.h>
using namespace std;

#define int long long

const int mxN = 1e4;
int n,m,t, c[mxN], p[mxN], d[mxN], traffic[mxN];
bool visited[mxN];
vector<pair<int,int>> adj[mxN];

int dfs(int node){
    visited[node] = true;
    for (auto & e : adj[node]){
        if (!visited[e.first] && p[e.first] == node){
            traffic[node] += dfs(e.first);
        }
    }
    traffic[node] += c[node];
    return traffic[node];
}

int32_t main(){
    ifstream cin("shortcut.in");
    ofstream cout("shortcut.out");
    cin >> n >> m >> t;
    for (int i = 0; i < n; i++){
        cin >> c[i];
    }
    for (int i = 0; i < m; i++){
        int a, b, w;
        cin >> a >> b >> w; a--; b--;
        adj[a].emplace_back(b, w);
        adj[b].emplace_back(a, w);
    }
    //dijkstra
    set<pair<int,int>> pq;
    memset(d, 0x3f, sizeof(d));
    memset(p, 0x3f, sizeof(p));
    d[0] = 0;
    for (int i = 0; i < n; i++){
        pq.insert({d[i], i});
    }
    while (!pq.empty()){
        int node = pq.begin()->second;
        for (auto & e : adj[node]){
            if (d[e.first] == d[node] + e.second){
                //lexicographic
                if (p[e.first] > node){
                    p[e.first] = node;
                }
            }
            else if (d[e.first] > d[node] + e.second){
                pq.erase({d[e.first], e.first});
                d[e.first] = d[node] + e.second;
                pq.insert({d[e.first], e.first});
                p[e.first] = node;
            }
        }
        pq.erase({d[node], node});
    }
    memset(visited, false, sizeof(visited));
    memset(traffic, 0, sizeof(traffic));
    dfs(0);
    int ans = 0;
    for (int i = 1; i < n; i++){
        if ((d[i] - t) * traffic[i] > ans){
            ans = ((d[i] - t) * traffic[i]);
        }
    }
    cout << ans << "\n";
//    for (int i = 0; i < n; i++){
//        cerr << "node: " << i+1 << " distance: " << d[i] << " traffic: " << traffic[i] << " parent: " << p[i]+1 << "\n";
//    }
}
