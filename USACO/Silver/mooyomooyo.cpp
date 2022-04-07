#include <bits/stdc++.h>

using namespace std;

const int mxN = 105;
int grid[mxN][10], gridcpy[mxN][10], n, k, modified = 0;
bool is_fall = true, bad = false, vis[mxN][10];
vector <pair<int,int>>resets;


bool valid(int i, int j, int x){
    if (i < 0 || j < 0 || i >= n || j >= 10){
        return false;
    }
    if (grid[i][j] != x){
        return false;
    }
    return true;
}
void cpy(){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < 10; j++){
            gridcpy[i][j] = grid[i][j];
        }
    }
}
void dfs(int i, int j, int x){
    vis[i][j] = true;
    grid[i][j] = 0;
    modified++;
    resets.emplace_back(i,j);
    if (valid(i+1,j,x)) dfs(i+1,j,x);
    if (valid(i,j+1,x)) dfs(i,j+1,x);
    if (valid(i-1,j,x)) dfs(i-1,j,x);
    if (valid(i,j-1,x)) dfs(i,j-1,x);
}
void fall(){
    for (int i = 0; i < 10; i++){
        deque <int> col;
        for (int j = n-1; j >= 0; j--)
            col.push_back(grid[j][i]);
        int cnt = 0;
        for (int j = 0; j < col.size(); j++){
            if (col[j] != 0) cnt++;
        }
        int lclcnt = 0;
        while (true){
            if (lclcnt == cnt) break;
            if (col[lclcnt] == 0){
                col.erase(col.begin()+lclcnt); continue;
            }
            else{
                lclcnt++;
            }
        }
        for (int j = n-1; j >= 0; j--){
            grid[j][i] = col[n-j-1];
        }
    }
}
int main() {
//    freopen("mooyomooyo.in", "r", stdin);
//    freopen("mooyomooyo.out", "w", stdout);
    cin >> n >> k;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < 10; j++){
            char c;
            cin >> c;
            grid[i][j] = c-48;
        }
    }
    cpy();
    while (is_fall){
        bool alg = false;
        for (int j = 0; j < n; j++){
            for (int i = 0; i < 10; i++){
                if (grid[j][i] != 0 && !vis[j][i]){
                    dfs(j,i,grid[j][i]);
                    if (modified < k){
                        for (auto & r : resets){
                            grid[r.first][r.second] = gridcpy[r.first][r.second];
                        }
                    }
                    else{
                        alg = true;
                    }
                    resets.clear();
                    bad = false;
                    modified = 0;
                }
            }
        }
        if (!alg) is_fall = false;
        if (!is_fall){
            break;
        }
        fall();
        cpy();
        memset(vis, 0, sizeof(vis));
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < 10; j++){
            cout << grid[i][j];
        }
        cout << "\n";
    }
}

