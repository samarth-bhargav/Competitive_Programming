#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e3+1;
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
char g[mxN][mxN];
int n, d, dist[mxN][mxN];
bool vis[mxN][mxN], viscpy[mxN][mxN], updown;

struct st{
    vector<pair<int,int>> ym;
    vector<int> mx;
    vector<int> a;
    int sz;
    st(vector<int> a){
        this->a = a;
        sz = a.size();
        mx.resize(4*sz);
        ym.resize(sz);
        fill(ym.begin(), ym.end(), make_pair(updown?-1e9:1e9, -1e9));
        bld(1, 0, sz-1);
    }
    void bld(int v, int tl, int tr){
        if (tl == tr){
            mx[v] = a[tl];
            return;
        }
        int tm = (tl + tr) / 2;
        bld(v*2, tl, tm);
        bld(v*2+1, tm+1, tr);
        mx[v] = max(mx[v*2], mx[v*2+1]);
    }
    int qry(int v, int tl, int tr, int l, int r){
        if (l > r){
            return -1e9;
        }
        if (l == tl && r == tr){
            return mx[v];
        }
        int tm = (tl + tr) / 2;
        return max(qry(v*2, tl, tm, l, min(tm, r)),
                   qry(v*2+1, tm+1, tr, max(l, tm+1), r));
    }
    bool qry(int l, int r, int x){
        return qry(1, 0, sz-1, l, r) >= x;
    }
    void upd(int v, int tl, int tr, int pos, int new_val){
        if (tl == tr){
            a[pos] = new_val;
            mx[v] = new_val;
            return;
        }
        int tm = (tl + tr) / 2;
        if (tm >= pos){
            upd(v*2, tl, tm, pos, new_val);
        }
        else{
            upd(v*2+1, tm+1, tr, pos, new_val);
        }
        mx[v] = max(mx[v*2], mx[v*2+1]);
    }
    void upd(int pos, int new_val, int y_coord, int manhattan){
        upd(1, 0, sz-1, pos, new_val);
        ym[pos] = make_pair(y_coord, manhattan);
    }
};

bool valid(int x, int y){
    if (vis[x][y] || viscpy[x][y]){
        return false;
    }
    return (x >= 0 && x < n && y >= 0 && y < n);
}

int main(){
    memset(vis, 0, sizeof(vis));
    queue<pair<int,int>> q;
    cin >> n >> d;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cin >> g[i][j];
            if (g[i][j] == '#'){
                q.push({i,j});
                dist[i][j] = 0;
                vis[i][j] = 1;
            }
        }
    }
    while (!q.empty()){
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++){
            if (valid(x+dx[i], y+dy[i])){
                vis[x+dx[i]][y+dy[i]] = true;
                dist[x+dx[i]][y+dy[i]] = dist[x][y]+1;
                q.push({x+dx[i], y+dy[i]});
            }
        }
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            dist[i][j]--;
        }
    }
    memset(vis, 0, sizeof(vis));
    memset(viscpy, 0, sizeof(viscpy));
    queue<pair<int, pair<int,int>>> center;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (g[i][j] == 'S'){
                center.push({0, {i,j}});
                vis[i][j] = true;
            }
        }
    }
    int t, x, y;
    while (!center.empty()){
        t = center.front().first;
        x = center.front().second.first;
        y = center.front().second.second;
        center.pop();
        for (int i = 0; i < 4; i++){
            if (valid(x+dx[i], y+dy[i])){
                if (dist[x+dx[i]][y+dy[i]] >= (t / d) && g[x+dx[i]][y+dy[i]] != '#') {
                    if ((t + 1) % d == 0) {
                        if (dist[x + dx[i]][y + dy[i]] >= (t + 1) / d - 1) {
                            if (dist[x + dx[i]][y + dy[i]] == (t + 1) / d - 1) {
                                vis[x + dx[i]][y + dy[i]] = true;
                            }
                            else{
                                vis[x + dx[i]][y + dy[i]] = true;
                                center.push({t + 1, {x + dx[i], y + dy[i]}});
                            }
                        }
                        else{
                            viscpy[x + dx[i]][y + dy[i]] = true;
                        }
                    }
                    else{
                        vis[x + dx[i]][y + dy[i]] = true;
                        center.push({t + 1, {x + dx[i], y + dy[i]}});
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            viscpy[i][j] = vis[i][j];
        }
    }
    st left(vector<int> (n, -1e9)), right(vector<int> (n, -1e9));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (viscpy[i][j]){
                //determine if we need to update
                if (left.ym[j].first + left.ym[j].second < i + dist[i][j]){
                    //we need to update
                    left.upd(j, i+j+dist[i][j], i, dist[i][j]);
                    right.upd(j, i-j+dist[i][j], i, dist[i][j]);
                }
            }
        }
        for (int j = 0; j < n; j++){
            if (!viscpy[i][j] && g[i][j] != '#'){
                vis[i][j] |= left.qry(0, j, i+j);
                vis[i][j] |= right.qry(j, n-1, i-j);
            }
        }
    }
    left = st(vector<int> (n, -1e9));
    right = st(vector<int> (n, -1e9));
    updown = false;
    for (int i = n-1; i > 0; i--){
        for (int j = 0; j < n; j++){
            if (viscpy[i][j]){
                //see if you need to update
                if (left.ym[j].first - left.ym[j].second > i - dist[i][j]){
                    left.upd(j, -i+j+dist[i][j], i, dist[i][j]);
                    right.upd(j, -i-j+dist[i][j], i, dist[i][j]);
                }
            }
        }
        for (int j = 0; j < n; j++){
            if (!viscpy[i][j] && g[i][j] != '#'){
                vis[i][j] |= left.qry(0, j, -i+j);
                vis[i][j] |= right.qry(j, n-1, -i-j);
            }
        }
    }
   int ans = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            ans += (vis[i][j]);
        }
    }
    cout << ans << "\n";
}