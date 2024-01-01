#include <bits/stdc++.h>

using namespace std;

int dx[4] = {0, 0, 1, -1};
int dy[4] = {-1, 1, 0, 0};
int dr[4] = {1, -1, 1, -1};
int dc[4] = {-1, -1, 1, 1};

const int INF = 1e9;

const int mxN = 2e5;
string grid[mxN];
int n, m;

bool valid2(int x, int y){
    if (!(0 <= x && x < n) || !(0 <= y && y < m)){
        return false;
    }
    for (int dir = 0; dir < 4; dir++){
        if (0 <= x + dx[dir] && x + dx[dir] < n){
            if (0 <= y + dy[dir] && y + dy[dir] < m){
                if (grid[x+dx[dir]][y+dy[dir]] == '#'){
                    return false;
                }
            }
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    for (int tt = 0; tt < t; tt++){
        cin >> n >> m;
        for (int i = 0; i < n; i++){
            cin >> grid[i];
        }
        vector<array<int, 2>> d(n*m+1);
        d[n*m] = {0, -1};
        for (int i = 0; i < n*m; i++){
            d[i] = {INF, -1};
        }
        vector<array<int, 2>> db[n*m+1];
        db[0].push_back({n*m, d[n*m][0]});
        for (int i = 0; i <= n*m; i++){
            while (!db[i].empty()){
                int tp = db[i].back()[0];
                int r = tp / m;
                int c = tp % m;
                db[i].pop_back();
                if (d[tp][0] < i){
                    continue;
                }
                if (tp == n*m){
                    for (int row = 0; row < n; row++){
                        if (valid2(row, 0)){
                            int idx = row * m;
                            int weight = grid[row][0] != '#';
                            if (d[idx][0] > weight + d[tp][0]){
                                d[idx][0] = weight + d[tp][0];
                                d[idx][1] = tp;
                                if (d[idx][0] <= n*m){
                                    db[d[idx][0]].push_back({idx, d[idx][0]});
                                }
                            }
                        }
                    }
                    continue;
                }
                for (int dir = 0; dir < 4; dir++){
                    if (valid2(r + dr[dir], c + dc[dir])){
                        int idx = (r + dr[dir]) * m + c + dc[dir];
                        int weight = grid[r + dr[dir]][c + dc[dir]] != '#';
                        if (d[idx][0] > weight + d[tp][0]){
                            d[idx][0] = weight + d[tp][0];
                            d[idx][1] = tp;
                            if (d[idx][0] <= n*m){
                                db[d[idx][0]].push_back({idx, d[idx][0]});
                            }
                        }
                    }
                }
            }
            db[i].clear();
            db[i].shrink_to_fit();
        }
        int row = -1;
        int op_val = INF;
        for (int r = 0; r < n; r++){
            //column fixed as m-1
            if (d[r*m + m-1][0] < op_val){
                op_val = d[r*m + m-1][0];
                row = r;
            }
        }
        if (op_val > n * m){
            cout << "NO\n";
            continue;
        }
        cout << "YES\n";
        int idx = row * m + m-1;
        while (d[idx][1] != -1){
            grid[idx / m][idx % m] = '#';
            idx = d[idx][1];
        }
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                cout << grid[i][j];
            }
            cout << "\n";
        }
    }
}