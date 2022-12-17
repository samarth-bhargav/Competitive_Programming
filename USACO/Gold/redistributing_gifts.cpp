#include <bits/stdc++.h>
using namespace std;

const int mxN = 18;
int p[mxN][mxN], dp[1 << mxN];
bool over[mxN][mxN][mxN];
int c, n;

int dfs(int u, int start, int visited){
    int ret = 0;
    for (int v = 0; v < n; v++){
        if (over[v][v][u] || ((1 << v) & c) == 0){
            continue;
            //target did not improve
        }
        if (v == start){
            ret += dp[c ^ visited];
            continue;
        }
        else{
            if (((1 << v) & visited) == 0){
                //has not been visited
                ret += dfs(v, start, (visited + (1 << v)));
            }
        }
    }
    return ret;
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
//    cerr << over[0][1][2] << "\n";
    dp[0] = 1;
    for (int mask = 1; mask < (1 << n); mask++){
        c = 0;
        int active_bit = 0;
        for (int i = 0; i < n; i++){
            if ((1 << i) & mask){
                c += (1 << i);
                active_bit = i;
            }
        }
        dp[mask] = dfs(active_bit, active_bit, 1 << active_bit);
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
        cout << dp[x] * dp[y] << "\n";
    }
}
