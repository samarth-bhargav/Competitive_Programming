#include <bits/stdc++.h>
using namespace std;

const int mxN = 50;
char g[mxN][mxN];

const int dx[4] = {1, 0, 0, -1};
const int dy[4] = {0, -1, 1, 0};

int n, m;
vector<int> minr, maxr, minc, maxc;
bool in_bounds(array<int, 2> coords, int d){
    int x = coords[0], y = coords[1];
    if (!(0 <= x && x < n && 0 <= y && y < m)) return false;
    if (d == 0 || d == 3){
        return minc[y] <= x && x <= maxc[y];
    }
    else{
        return minr[x] <= y && y <= maxr[x];
    }
}

bool vis[mxN][mxN];
int dfs_count = 0;

const int INF = 1e9;

void dfs(int x, int y){
    dfs_count++;
    vis[x][y] = true;
    for (int d = 0; d < 4; d++){
        if (in_bounds({x + dx[d], y + dy[d]}, d) && g[x+dx[d]][y+dy[d]] == '#' && !vis[x+dx[d]][y+dy[d]]){
            dfs(x + dx[d], y + dy[d]);
        }
    }
}

int main(){
    int t; cin >> t;
    while (t--){
        cin >> n >> m;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                cin >> g[i][j];
            }
        }
        minr = vector<int> (n, 1e9);
        maxr = vector<int> (n, -1);
        minc = vector<int> (m, 1e9);
        maxc = vector<int> (m, -1);
        queue<array<int,2>> bfs;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                if (g[i][j] == '#'){
                    minr[i] = min(minr[i], j);
                    maxr[i] = max(maxr[i], j);
                    minc[j] = min(minc[j], i);
                    maxc[j] = max(maxc[j], i);
                    bfs.push({i, j});
                }
            }
        }
        auto update = [&](int x, int y){
            minr[x] = min(minr[x], y);
            maxr[x] = max(maxr[x], y);
            minc[y] = min(minc[y], x);
            maxc[y] = max(maxc[y], x);
        };
        int filled_count = 0;
        while (!bfs.empty()){
            filled_count++;
            array<int, 2> top = bfs.front();
            bfs.pop();
            for (int d = 0; d < 4; d++){
                g[top[0]][top[1]] = '.';
                array<int, 2> top_cpy = top;
                while (in_bounds(top_cpy, d)){
                    if (g[top_cpy[0]][top_cpy[1]] == '#'){
                        break;
                    }
//                    cerr << top_cpy[0] << " " << top_cpy[1] << endl;
                    g[top_cpy[0]][top_cpy[1]] = '#';
                    update(top_cpy[0], top_cpy[1]);
                    if (top_cpy[0] == top[0] && top_cpy[1] == top[1]){}
                    else bfs.push({top_cpy[0], top_cpy[1]});
                    top_cpy[0] += dx[d]; top_cpy[1] += dy[d];
                }
            }
        }
//        for (int i = 0; i < n; i++){
//            for (int j = 0; j < m; j++){
//                cout << g[i][j];
//            }
//            cout << "\n";
//        }
        cout << "\n";
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                vis[i][j] = false;
            }
        }
        dfs_count = 0;
        bool processed = false;
        for (int i = 0; i < n; i++){
            if (processed) break;
            for (int j = 0; j < m; j++){
                if (g[i][j] == '#'){
                    dfs(i, j);
                    processed = true;
                    break;
                }
            }
        }
        if (dfs_count == filled_count){
            for (int i = 0; i < n; i++){
                for (int j = 0; j < m; j++){
                    cout << g[i][j];
                }
                cout << "\n";
            }
            cout << '\n';
            continue;
        }
        //split up into two connected components
        int mx1 = INF, Mx1 = -1, my1 = INF, My1 = -1;
        int mx2 = INF, Mx2 = -1, my2 = INF, My2 = -1;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                if (vis[i][j]){
                    mx1 = min(mx1, i);
                    Mx1 = max(Mx1, i);
                    my1 = min(my1, j);
                    My1 = max(My1, j);
                }
                else if (g[i][j] == '#'){
                    mx2 = min(mx2, i);
                    Mx2 = max(Mx2, i);
                    my2 = min(my2, j);
                    My2 = max(My2, j);
                }
            }
        }
        bool top, left;
        if (My1 < my2) left = true;
        else left = false;
        if (Mx1 < mx2) top = true;
        else top = false;

        array<int, 2> c1, c2;

        if (top && left){
            g[Mx1][My1] = '#';
            g[mx2][my2] = '#';
            update(Mx1, My1);
            update(mx2, my2);
            c1 = {Mx1, My1};
            c2 = {mx2, my2};
        }
        else if (top && !left){
            g[Mx1][my1] = '#';
            g[mx2][My2] = '#';
            update(Mx1, my1);
            update(mx2, My2);
            c1 = {Mx1, my1};
            c2 = {mx2, My2};
        }
        else if (!top && left){
            g[mx1][My1] = '#';
            g[Mx2][my2] = '#';
            update(mx1, My1);
            update(Mx2, my2);
            c1 = {mx1, My1};
            c2 = {Mx2, my2};
        }
        else{
            g[mx1][my1] = '#';
            g[Mx2][My2] = '#';
            update(mx1, my1);
            update(Mx2, My2);
            c1 = {mx1, my1};
            c2 = {Mx2, My2};
        }
        if (c1[0] > c2[0]) swap(c1, c2);
        for (int i = c1[0]; i <= c2[0]; i++){
            g[i][c1[1]] = '#';
            update(i, c1[1]);
        }
//        for (int i = 0; i < n; i++){
//            for (int j = 0; j < m; j++){
//                cout << g[i][j];
//            }
//            cout << "\n";
//        }
//        cout << '\n';
        for (int i = min(c1[1], c2[1]); i <= max(c1[1], c2[1]); i++){
            g[c2[0]][i] = '#';
            update(c2[0], i);
        }
//        for (int i = 0; i < n; i++){
//            for (int j = 0; j < m; j++){
//                cout << g[i][j];
//            }
//            cout << "\n";
//        }
//        cout << '\n';
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                if (g[i][j] == '#'){
                    bfs.push({i, j});
                }
            }
        }
        filled_count = 0;
        while (!bfs.empty()){
            filled_count++;
            array<int, 2> tp = bfs.front();
            bfs.pop();
            for (int d = 0; d < 4; d++){
                g[tp[0]][tp[1]] = '.';
                array<int, 2> top_cpy = tp;
                while (in_bounds(top_cpy, d)){
                    if (g[top_cpy[0]][top_cpy[1]] == '#'){
                        break;
                    }
//                    cerr << top_cpy[0] << " " << top_cpy[1] << endl;
                    g[top_cpy[0]][top_cpy[1]] = '#';
                    update(top_cpy[0], top_cpy[1]);
                    if (top_cpy[0] == tp[0] && top_cpy[1] == tp[1]){}
                    else bfs.push({top_cpy[0], top_cpy[1]});
                    top_cpy[0] += dx[d]; top_cpy[1] += dy[d];
                }
            }
        }
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                cout << g[i][j];
            }
            cout << "\n";
        }
        cout << "\n";
    }
}