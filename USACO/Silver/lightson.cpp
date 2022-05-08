#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e2+5;
bool vis[mxN][mxN], vis1[mxN][mxN];
map <pair<int,int>,vector<pair<int,int>>> mp;
int n,m,ans=0;

bool valid(int x, int y){
    return !(x > n || y > n || x < 1 || y < 1);
}

void dfs(int x, int y){
    vis[x][y] = true;
    for (auto & i : mp[make_pair(x,y)]){
        if (!vis[i.first][i.second]){
            vis[i.first][i.second] = true;
            if (vis[i.first-1][i.second] && valid(i.first-1,i.second)){
                dfs(i.first, i.second);
            }
            else if (vis[i.first][i.second-1] && valid(i.first,i.second-1)){
                dfs(i.first, i.second);
            }
            else if (vis[i.first+1][i.second] && valid(i.first+1,i.second)){
                dfs(i.first, i.second);
            }
            else if (vis[i.first][i.second+1] && valid(i.first,i.second+1)){
                dfs(i.first, i.second);
            }
        }
    }
}
void dfs2(int x, int y){
    ans++;
    vis1[x][y] = true;
    if (valid(x+1,y)){
        if (vis[x+1][y] && !vis1[x+1][y]) dfs2(x+1,y);
    }
    if (valid(x,y-1)){
        if (vis[x][y-1] && !vis1[x][y-1]) dfs2(x,y-1);
    }
    if (valid(x-1,y)){
        if (vis[x-1][y] && !vis1[x-1][y]) dfs2(x-1,y);
    }
    if (valid(x,y+1)){
        if (vis[x][y+1] && !vis1[x][y+1]) dfs2(x,y+1);
    }
}
int main(){
    freopen("lightson.in", "r", stdin);
    freopen("lightson.out", "w", stdout);
    memset(vis,0,sizeof(vis));
    memset(vis1,0,sizeof(vis1));
    cin >> n >> m;
    for (int i = 0; i < m; i++){
        int a,b,c,d;
        cin >> a >> b >> c >> d;
        if (mp.find(make_pair(a,b)) == mp.end()){
            mp.insert(make_pair(make_pair(a,b), vector<pair<int,int>>{make_pair(c,d)}));
        }
        else{
            mp[make_pair(a,b)].push_back(make_pair(c,d));
        }
    }
    dfs(1,1);
    dfs2(1,1);
    cout << ans << "\n";
}