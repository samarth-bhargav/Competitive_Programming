#include <bits/stdc++.h>
using namespace std;

#define int long long
const int mxN = 1e5;
vector<pair<int,int>> adj[mxN];
vector<int> adj1[mxN];
vector<int> minimum(mxN);
int dist[mxN];

int32_t main(){
    ifstream cin("timeline.in");
    ofstream cout("timeline.out");
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, c;
    cin >> n >> m >> c;
    for (int i = 0; i < n; i++){
        cin >> minimum[i];
    }
    for (int i = 0; i < c; i++){
        int a, b, x;
        cin >> a >> b >> x; a--; b--;
        adj[a].emplace_back(b, x);
        adj1[b].emplace_back(a);
    }
    vector<int> roots;
    for (int i = 0; i < n; i++){
        if (adj1[i].empty()){
            roots.push_back(i);
        }
    }
    set<pair<int, pair<int,int>>> edges; //edge weight, from, to
    //this way, each edge will only be processed once
    memset(dist, 0x3f, sizeof(dist));
    for (int i = 0; i < roots.size(); i++){
        dist[roots[i]] = -minimum[roots[i]];
        for (pair<int,int> edge : adj[roots[i]]){
            edges.insert({-(minimum[roots[i]] + edge.second), {roots[i], edge.first}});
        }
    }
    while (!edges.empty()){
        int weight = edges.begin()->first;
        int to = edges.begin()->second.second;
        if (weight >= dist[to]){
            edges.erase(edges.begin());
            continue;
        }
        dist[to] = min(weight, -minimum[to]);
        edges.erase(edges.begin());
        for (pair<int,int> edge : adj[to]){
            edges.insert({dist[to] - edge.second, {to, edge.first}});
        }
    }
    for (int i = 0; i < n; i++){
        cout << -dist[i] << "\n";
    }
}
