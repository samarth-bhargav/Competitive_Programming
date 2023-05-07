#include <bits/stdc++.h>
using namespace std;

const int mxN = 1501;
int n;
int g[mxN][mxN], cows[mxN][mxN];

int dfs(int x, int y, int d){
    //only one route
    cows[x][y] += d;
    if (x == n || y == n){
        return d * g[x][y];
    }
    if (g[x][y] == -1){
        //go down
        return dfs(x+1, y, d);
    }
    else{
        //go right
        return dfs(x, y+1, d);
    }
}

bool vis[mxN][mxN];
int ans = 0;

void init(int x, int y, int px=-1, int py=-1){
    if (px == -1 && py == -1){
        cows[x][y] = 1;
    }
    else{
        cows[x][y] += cows[px][py];
        if (!(x == n || y == n)){
            cows[x][y] += (!vis[x][y]);
        }
    }
    vis[x][y] = true;
    if (x == n || y == n){
        ans += cows[x][y] * g[x][y];
        return;
    }
    if (g[x][y] == -1){
        //go down
        init(x+1, y, x, y);
    }
    else{
        init(x, y+1, x, y);
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; i++){
        string s; cin >> s;
        for (int j = 0; j < n; j++){
            if (s[j] == 'R'){
                g[i][j] = 1;
            }
            else{
                g[i][j] = -1;
            }
        }
        cin >> g[i][n];
    }
    for (int i = 0; i < n; i++){
        cin >> g[n][i];
    }
    //initialize cows
    memset(vis, false, sizeof(vis));
    memset(cows, 0, sizeof(cows));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (!vis[i][j]){
                init(i, j);
            }
        }
    }
    cout << ans << "\n";
    int q; cin >> q;
    for (int i = 0; i < q; i++){
        int x, y; cin >> x >> y; x--; y--;
        int old_cows = cows[x][y];
        ans += dfs(x, y, -cows[x][y]);
        g[x][y] = -g[x][y];
        ans += dfs(x, y, old_cows);
        cout << ans << "\n";
    }
}
