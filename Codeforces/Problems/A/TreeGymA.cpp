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

const int mxN = 3*1e5;
vector <int> adj[mxN];
int path[mxN+1];

bool compare(int a, int b){
    return a > b;
}

void dfs(int e, int ancestor, int cnt){
    path[e] = cnt;
    for (auto edge : adj[e]){
        if (edge != ancestor){
            dfs(edge, e, cnt+1);
        }
    }
}

int main() {
    //setIO();
    int t;
    cin >> t;
    for (int i = 0; i < t-1; i++){
        int a,b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1, 0, 0);
    sort(path+1, path+t+1, compare);
    cout << path[1]*3 << "\n";
}

