#include <bits/stdc++.h>
using namespace std;

const int mxN = 2e5;
vector<int> adj[mxN];

//returns max matching of subtree of e
pair<int, bool> dfs(int e, int p){
    int ret = 0;
    bool no_connection = true;
    for (auto & node : adj[e]){
        if (node != p){
            pair<int, bool> res = dfs(node, e);
            no_connection &= ~res.second;
            ret += res.first;
        }
    }
    return {ret + ~no_connection,no_connection};
}

int main(){
    int n;
    cin >> n;
    for (int i = 0; i < n-1; i++){
        int a, b;
        cin >> a >> b; a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    cout << dfs(0, -1).first;
}