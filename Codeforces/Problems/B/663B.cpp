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
int a,b;
int ans = 0;
const int maxN = 1e2;
char grid[maxN+1][maxN+1];
bool check[maxN+1][maxN+1];
bool valid(int x, int y){
    if (x >= a || y >= b || x < 0 || y < 0){
        return false;
    }
    return true;
}
void dfs(int x, int y){
    if (x == a-1 && y == b-1){
        return;
    }
    check[x][y] = false;
    if (grid[x][y] == 'D'){
        if (valid(x+1, y)){
            dfs(x+1,y);
        }
        else{
            grid[x][y] = 'R';
            ans++;
            dfs(x,y);
        }
    }
    else{
        if (valid(x, y+1)){
            dfs(x, y+1);
        }
        else{
            grid[x][y] = 'D';
            ans++;
            dfs(x,y);
        }
    }
}

int main() {
    //setIO();
    int t;
    cin >> t;
    while (t--) {
        cin >> a >> b;
        for (int i = 0; i < a; i++) {
            for (int k = 0; k < b; k++) {
                cin >> grid[i][k];
                if (!(i == a-1 && k == b-1)){
                    check[i][k] = true;
                }
            }
        }
        for (int i = 0; i < a; i++) {
            for (int k = 0; k < b; k++) {
                if (check[i][k]) {
                    dfs(i, k);
                }
            }
        }
        cout << ans << "\n";
        ans = 0;
    }
}

