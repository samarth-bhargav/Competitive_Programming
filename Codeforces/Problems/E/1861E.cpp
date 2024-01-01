#include <bits/stdc++.h>

#define int long long

const int M = 998244353;
using namespace std;

int binpow(int x, int e){
    int res = 1, curr = x;
    while (e){
        if (e & 1){
            res *= curr; res %= M;
        }
        curr *= curr; curr %= M;
        e >>= 1;
    }
    return res;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k; cin >> n >> k;
    int ways[n+1][k+1], suf[n+1][k+1];
    memset(ways, 0, sizeof(ways));
    memset(suf, 0, sizeof(suf));
    ways[0][0] = 1; suf[0][0] = 1;

    int ans = 0;

//    cout << binpow(4, 5) << "\n";

    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= k; j++){
            ways[i][j] = suf[i-1][j] + ways[i-1][j-1] * (k - (j - 1));
            ways[i][j] %= M;
        }
        ans += ways[i][k] * binpow(k, (n-i)); ans %= M;
        ways[i][0] += ways[i][k];
        ways[i][0] %= M;
        ways[i][k] = 0; suf[i][k] = 0;
        for (int j = k-1; ~j; j--){
            suf[i][j] = suf[i][j+1] + ways[i][j];
            suf[i][j] %= M;
        }
    }

    cout << (ans % M + M) % M<< "\n";
}