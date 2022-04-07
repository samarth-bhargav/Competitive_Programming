/*
Author: treewave
orz
*/
#include <bits/stdc++.h>

using namespace std;

const int mxN = 2e2+1;
int ar[mxN][mxN]; bool vis[mxN][mxN];
int n,k,final = 1e9+1;

bool valid(int x, int y, bool init){
    if (x < 1 || y < 1 || x > n || y > n) {
        return false;
    }
    return true;
}
void dfs(int ans, int x, int y, int cnt, bool init){
    vis[x][y] = true;
    if (cnt == k){
        final = min(final, ans);
        return;
    }
    if (valid(x+1,y,init)){
        dfs(max(ans,abs(ar[x+1][y]-ar[x][y])),x+1,y,cnt+1,init);
    }
    if (valid(x-1,y,init)){
        dfs(max(ans,abs(ar[x-1][y]-ar[x][y])),x-1,y,cnt+1,init);
    }
    if (valid(x,y+1,init)){
        dfs(max(ans,abs(ar[x][y+1]-ar[x][y])),x,y+1,cnt+1,init);
    }
    if (valid(x,y-1,init)){
        dfs(max(ans,abs(ar[x][y-1]-ar[x][y])),x,y-1,cnt+1,init);
    }
}

int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            cin >> ar[i][j];
        }
    }
    memset(vis,0,sizeof(vis));
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            dfs(-1e9,i,j,1,vis[i][j]);
        }
    }
    cout << final << "\n";
}

