/*
Author: treewave
orz
*/
#include <bits/stdc++.h>

using namespace std;

const int mxN = 1e5+5;
int n,m;
int parent[mxN];
char cow[mxN];
vector <int> adj[mxN];


void init(){
    for (int i = 1; i <= n; i++){
        parent[i] = i;
    }
};
int find(int a){
	return a^parent[a]?parent[a]=find(parent[a]):a;
}
void join(int a, int b){
    int c = find(a);
    int d = find(b);
    if (c != d && cow[c] == cow[d]){
        parent[c] = d;
    }
}
void dfs(int e, int a){
    join(e,a);
    for (auto & i : adj[e]){
        if (i != a){
            dfs(i, e);
        }
    }
}
int main() {
    freopen("milkvisits.in", "r", stdin);
    freopen("milkvisits.out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; i++){
        cin >> cow[i];
    }
    for (int i = 0; i < n-1; i++){
        int a,b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    init();
    dfs(1,1);
    for (int i = 0; i < m; i++){
        int a,b; char c;
        cin >> a >> b >> c;
        if (find(a) == find(b)){
            cout << (cow[a] == c);
        }
        else{
            cout << 1;
        }
    }
    cout << "\n";
}

