/*
Dont raise your voice,improve your argument
--Desmond Tutu
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/
const int mxN = 105;
int n; vector<int>a;
vector<int>adj[mxN];
int rmq[mxN][mxN];
int d[mxN];

void bld(int l, int r, int pos){
    if (l >= r){
        return;
    }
    if (pos != r){
        adj[a[pos]].push_back(a[rmq[pos+1][r]]);
    }
    if (pos != l){
        adj[a[pos]].push_back(a[rmq[l][pos-1]]);
    }
    bld(l,pos-1,rmq[l][pos-1]);
    bld(pos+1,  r, rmq[pos+1][r]);
}
void dfs(int e, int u, int dep){
    d[e] = dep;
    dep++;
    for (auto & i : adj[e]){
        if (i != u){
            dfs(i,e,dep);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--){
        cin >> n;
        a.resize(n+1);
        for (int i = 1; i <= n; i++){
            cin >> a[i];
        }
        for (int i = 1; i <= n; i++){
            rmq[i][i] = i;
        }
        for (int i = 1; i <= n; i++){
            for (int j = i+1; j <= n; j++){
                if (a[rmq[i][j-1]] > a[j]){
                    rmq[i][j] = rmq[i][j-1];
                }
                else{
                    rmq[i][j] = j;
                }
            }
        }
        bld(1,n,rmq[1][n]);
        dfs(n,n,0);
        for (int i = 1; i <= n; i++) {
            cout << d[a[i]] << " ";
        }
        cout << "\n";
        for (int i = 0; i < mxN; i++){
            adj[i].clear();
        }
    }
}

