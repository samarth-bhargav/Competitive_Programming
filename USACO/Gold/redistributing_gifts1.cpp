#include <bits/stdc++.h>
using namespace std;

const int mxN = 18;
int p[mxN][mxN], dp[1 << mxN], dp1[1 << mxN];
bool over[mxN][mxN][mxN];
int cycles[1 << mxN];
int c, n;

void dfs(int u, int start, int visited){
    for (int v = 0; v < n; v++){
        if (over[v][v][u] || ((1 << v) & c) == 0 || u == v){
            continue;
            //target did not improve
        }
        if (v == start){
            cycles[visited]++;
            continue;
        }
        else{
            if (((1 << v) & visited) == 0){
                //has not been visited
                dfs(v, start, (visited + (1 << v)));
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cin >> p[i][j];
            p[i][j]--;
        }
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            for (int k = 0; k < n; k++){
                over[i][j][k] = (find(p[i], p[i]+n, j) - find(p[i], p[i]+n, k) < 0);
            }
        }
    }
    c = 0;
    for (int i = 0; i < n; i++){
        c += (1 << i);
    }
    for (int i = 0; i < n; i++){
        dfs(i, i, 1 << i);
        c -= (1 << i);
    }
    for (int i = 0; i < n; i++){
        c += (1 << i);
    }
    memset(dp, 0, sizeof(dp));
    memset(dp1  , 0, sizeof(dp));
    dp[0] = 1;
    for (int mask = 1; mask < (1 << n); mask++){
        for (int submask = ((mask - 1) & mask); submask; submask = (submask - 1) & mask){
            dp[mask] += (dp[submask] * dp[mask ^ submask]);
        }
        dp[mask] /= 2;
        dp[mask] += cycles[mask];
    }
    dp1[0] = 1;
    for (int mask = 1; mask < (1 << n); mask++){
        for (int submask = mask; ; submask = (submask - 1) & mask){
            dp1[mask] += dp[submask];
            if (submask == 0){
                break;
            }
        }
    }
    int queries; cin >> queries;
    for (int q = 0; q < queries; q++){
        string s; cin >> s;
        int x = 0, y = 0;
        for (int i = 0; i < n; i++){
            if (s[i] == 'G'){
                x += (1 << i);
            }
            else{
                y += (1 << i);
            }
        }
        cout << dp1[x] * dp1[y] << "\n";
    }
}