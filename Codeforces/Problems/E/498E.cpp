/*
ID: samarth10
LANG: C++11
TASK:
*/
#include <bits/stdc++.h>

using namespace std;

const int mxN = 2e5;
int t, q, subtree[mxN+5] = {0};
vector <int> flatten;
vector <int> adj[mxN+2];
map <int,int> inlinefind;

void dfs1(int e){
    flatten.push_back(e);
    inlinefind.insert(make_pair(e,flatten.size()-1));
    for (auto i : adj[e]){
        dfs1(i);
    }
}
int dfs2(int e){
    if (adj[e].empty()){
        subtree[e] = 1;
        return 1;
    }
    else{
        for (auto & i : adj[e]) {
            subtree[e] += dfs2(i);
        }
        subtree[e] += 1;
    }
    return subtree[e];
}
int main() {
    //setIO();
    cin >> t >> q;
    for (int i = 2; i <= t; i++){
        int a;
        cin >> a;
        adj[a].push_back(i);
    }
    dfs1(1);
    dfs2(1);
    for (int i = 0; i < q; i++){
        int a,b;
        cin >> a >> b;
        cout << (subtree[a] < b ? -1 : flatten[inlinefind[a]+b-1]) << "\n";
    }
}

