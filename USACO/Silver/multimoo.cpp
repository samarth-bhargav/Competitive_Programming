#include <bits/stdc++.h>

using namespace std;
const int mxN = 255;
int n, ans1 = 0, ans2 = 0, currans = 0, ar[mxN][mxN], en[mxN][mxN], de[mxN*mxN][2];
bool vis[mxN][mxN], vis2[mxN*mxN];
unordered_map<int,unordered_set<int>>adj;
map<pair<int,int>,bool>check;
vector<int>save;

struct dsu{
    int parent[mxN*mxN];
    int sz[mxN*mxN];
    void init(){
        for (int i = 1; i <= n*n; i++){
            parent[i] = i;
            sz[i] = 1;
        }
    }
    int find(int x){
        return x^parent[x]?parent[x]=find(parent[x]):x;
    }
    void join(int a, int b){
        int c = find(a);
        int d = find(b);
        if (c == d){
            return;
        }
        if (sz[c]>sz[d]){
            swap(c,d);
        }
        parent[c] = d;
        int one = sz[c];
        int two = sz[d];
        sz[c] = one+two;
        sz[d] = one+two;
    }
} d;

bool valid(int x, int y){
    if (x > n || y > n || x <= 0 || y <= 0){
        return false;
    }
    return !vis[x][y];
}

void dfs1(int x, int y){
    vis[x][y] = true;
    if (valid(x+1,y)){
        if (ar[x+1][y] == ar[x][y]){
             d.join(en[x+1][y],en[x][y]);
             dfs1(x+1,y);
        }
    }
    if (valid(x-1,y)){
        if (ar[x-1][y] == ar[x][y]){
            d.join(en[x-1][y],en[x][y]);
            dfs1(x-1,y);
        }
    }
    if (valid(x,y+1)){
        if (ar[x][y+1] == ar[x][y]){
            d.join(en[x][y+1],en[x][y]);
            dfs1(x,y+1);
        }
    }
    if (valid(x,y-1)){
        if (ar[x][y-1] == ar[x][y]){
            d.join(en[x][y-1],en[x][y]);
            dfs1(x,y-1);
        }
    }
}
//second to bld
void dfs2(int x, int y){
    vis[x][y] = true;
    if (valid(x,y+1)){
        if (d.find(en[x][y+1]) != d.find(en[x][y])){
            adj[d.find(en[x][y])].insert(d.find(en[x][y+1]));
            adj[d.find(en[x][y+1])].insert(d.find(en[x][y]));
        }
        else{
            dfs2(x,y+1);
        }
    }
    if (valid(x,y-1)){
        if (d.find(en[x][y-1]) != d.find(en[x][y])){
            adj[d.find(en[x][y])].insert(d.find(en[x][y-1]));
            adj[d.find(en[x][y-1])].insert(d.find(en[x][y]));
        }
        else{
            dfs2(x,y-1);
        }
    }
    if (valid(x+1,y)){
        if (d.find(en[x+1][y]) != d.find(en[x][y])){
            adj[d.find(en[x][y])].insert(d.find(en[x+1][y]));
            adj[d.find(en[x+1][y])].insert(d.find(en[x][y]));
        }
        else{
            dfs2(x+1,y);
        }
    }
    if (valid(x-1,y)){
        if (d.find(en[x-1][y]) != d.find(en[x][y])){
            adj[d.find(en[x-1][y])].insert(d.find(en[x][y]));
            adj[d.find(en[x][y])].insert(d.find(en[x-1][y]));
        }
        else{
            dfs2(x-1,y);
        }
    }
}
void dfs3(int curr, int init, int sec){
    currans += d.sz[curr];
    vis2[curr] = true;
    save.push_back(curr);
    for (auto & i : adj[curr]){
        if (!vis2[i] && (ar[de[i][0]][de[i][1]] == ar[de[init][0]][de[init][1]] || ar[de[i][0]][de[i][1]] == ar[de[sec][0]][de[sec][1]])){
            dfs3(i,init,sec);
        }
    }
}
int main(){
//    freopen("multimoo.in", "r", stdin);
//    freopen("multimoo.out", "w", stdout);
//    ios_base::sync_with_stdio(0);
//    cin.tie(0);
    cin >> n;
    cerr << "hi" << endl;
    d.init();
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            cin >> ar[i][j];
        }
    }
    cerr << "hi" << endl;
    int cnt = 0;
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            en[i][j] = ++cnt;
            de[cnt][0] = i;
            de[cnt][1] = j;
        }
    }
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            if (!vis[i][j]){
                dfs1(i,j);
            }
        }
    }
    //iterate through find
    for (int i = 1; i <= n*n; i++){
        ans1 = max(ans1,d.sz[i]);
    }
    memset(vis,0,sizeof(vis));
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            if (!vis[i][j]){
                dfs2(i,j);
            }
        }
    }
    for (auto & i : adj){
        for (auto & j : i.second){
            if (check.find(make_pair(i.first,j)) != check.end()){
                continue;
            }
            vis2[i.first] = true;
            vis2[j] = true;
            dfs3(j,i.first,j);
            dfs3(i.first,j,i.first);
            ans2 = max(ans2,currans);
            for (auto & h : save){
                vis2[h] = false;
            }
            save.clear();
            currans = 0;
            check[{i.first,j}] = true;
        }
    }
    cout << ans1 << "\n" << ans2 << "\n";
}

