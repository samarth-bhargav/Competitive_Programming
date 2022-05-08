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
const int mxN = 1e3;
bool ar[mxN+1][mxN+1];
bool vis[mxN+1][mxN+1];
int maxA = 0;
int maxP = 0;
int Ans = 0;
int Pns = 0;
void dfs(int x, int y){
    if (!ar[x][y] || x < 0 || y < 0 || x >= 101 || y >= 101){
        return;
    }
    if (ar[x][y+1]) maxP-=2;
    if (y-1 >= 0){
        if (ar[x][y-1]) maxP-=2;
    }
    if (x-1 >= 0){
        if (ar[x-1][y]) maxP-=2;
    }
    if (ar[x+1][y]) maxP-=2;
    maxA += 1;
    maxP += 4;
    ar[x][y] = false;
    dfs(x-1,y);
    dfs(x+1,y);
    dfs(x,y+1);
    dfs(x,y-1);
}

int main() {
    setIO("perimeter");
    int n;
    cin >> n;
    for (int i = 0; i < n; i++){
        for (int k = 0; k < n; k++){
            char c;
            cin >> c;
            ar[i][k] = c == '#';
        }
    }
    for (int i = 0; i < n; i++){
        for (int k = 0; k < n; k++){
            if (ar[i][k]){
                dfs(i,k);
                Ans = max(Ans, maxA);
                Pns = max(Pns, maxP);
                maxA = 0;
                maxP = 0;
            }
        }
    }
    cout << Ans << " " << Pns << "\n";
}

