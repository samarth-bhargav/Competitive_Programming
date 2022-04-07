//babybeluga
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/

const int mxN = 1e4;
int n, k, dp[mxN+1];
struct st{
    int p[4*mxN];
    void bld(int a[], int v, int tl, int tr){
        if (tl == tr){
            p[v] = a[tl];
        }
        else{
            int tm = (tl+tr)/2;
            bld(a, v*2, tl, tm);
            bld(a, v*2+1, tm+1, tr);
            p[v] = max(p[v*2], p[v*2+1]);
        }
    }
    int qry(int l, int r){
        return qry(1, 0, n-1, l, r);
    }
    int qry(int v, int tl, int tr, int l, int r){
        if (l > r){
            return 0;
        }
        if (l == tl && r == tr){
            return p[v];
        }
        else{
            int tm = (tl+tr)/2;
            return max(qry(v*2, tl, tm, l, min(r, tm)),
                    qry(v*2+1, tm+1, tr, max(l,tm+1), r));
        }
    }
} s;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("teamwork.in", "r", stdin);
    freopen("teamwork.out", "w", stdout);
    cin >> n >> k;
    int a[n];
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    s.bld(a, 1, 0, n-1);
    memset(dp, 0, sizeof(dp));
    dp[0] = a[0];
    for (int i = 1; i < n; i++){
        for (int j = 1; j <= min(i+1, k); j++){
            dp[i] = max(dp[i], dp[i-j]+s.qry(i-j+1,i) * j);
        }
    }
    cout << dp[n-1] << "\n";
}

