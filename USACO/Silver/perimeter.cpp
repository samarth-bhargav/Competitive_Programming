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

const int maxN = 1e2;
bool ar[maxN+2][maxN+2];
bool vis[maxN+2][maxN+2];
int ans = 0;
bool visit(int x, int y){
    return x <= maxN + 1 && x >= 0 && y <= maxN + 1 && y >= 0;
}
void dfs(int x, int y){
    if (ar[x][y]){
        ans++;
        return;
    }
    if (vis[x][y]){
        return;
    }
    vis[x][y] = true;
    if (visit(x-1,y)){
        dfs(x-1,y);
    }
    if (visit(x+1, y)){
        dfs(x+1,y);
    }
    if (visit(x,y+1)){
        dfs(x,y+1);
    }
    if (visit(x,y-1)){
        dfs(x,y-1);
    }
}
int main() {
    setIO("perimeter");
    int t;
    cin >> t;
    for (int i = 0; i < t; i++){
        int x,y;
        cin >> x >> y;
        ar[x][y] = true;
    }
    dfs(0,0);
    cout << ans << "\n";
}

