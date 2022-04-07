/*
Author: treewave
orz
*/
#include <bits/stdc++.h>

using namespace std;

const int mxN = 1e5+5;
vector <int> vals(mxN);
vector <pair<int,pair<int,int>>>edges(mxN);
set<int>adj[mxN];

int main() {
//    freopen("wormsort.in", "r", stdin);
//    freopen("wormsort.out", "w", stdout);
    int n,m;
    cin >> n >> m;
    for (int i = 0; i < n; i++){
        cin >> vals[i+1];
    }
    bool bad = false;
    for (int i = 1; i <= n; i++){
        if (vals[i] != i){
            bad = true;
            break;
        }
    }
    if (!bad){
        cout << -1 << "\n";
        return 0;
    }
    for (int i = 0; i < m; i++){
        int a,b;
        cin >> a >> b;
        adj[a].insert(b);
        adj[b].insert(a);
        int w;
        cin >> w;
        edges[i] = {w,{a,b}};
    }
    sort(edges.begin(),edges.begin()+m);
    for (int i = 0; i < edges.size(); i++){
        //check if we can remove edge
        int a = edges[i].second.first;
        int b = edges[i].second.second;
        int w = edges[i].first;
        adj[a].erase(b);
        adj[b].erase(a);
        if (adj[a].empty()){
            if (vals[a] != a){
                cout << w << "\n";
                return 0;
            }
        }
        if (adj[b].empty()){
            if (vals[b] != b){
                cout << w << "\n";
                return 0;
            }
        }
    }
}

