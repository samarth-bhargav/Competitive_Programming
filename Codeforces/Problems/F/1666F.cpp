#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int mxN = 5e3+1, M = 998244353;
ll dp[mxN][mxN][2], fact[mxN], ifact[mxN];

long long binpow(long long a, long long b) {
    a %= M;
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % M;
        a = a * a % M;
        b >>= 1;
    }
    return res;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    fact[1] = 1;
    for (int i = 2; i < mxN; i++){
        fact[i] = fact[i-1] * i;
        fact[i] = (fact[i] % M + M) % M;
    }
    for (int i = 1; i < mxN; i++){
        ifact[i] = binpow(fact[i], M-2);
    }
    while (t--){
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        reverse(a.begin(), a.end());
        int cnt = 1, cnts[n];
        for (int i = 0; i < n; i++){
            if (i == n-1){
                cnts[i] = cnt;
            }
            else if (a[i] != a[i+1]){
                cnts[i] = cnt;
                cnt = 1;
            }
            else{
                cnts[i] = 0;
                cnt++;
            }
        }
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                dp[i][j][0] = 0;
                dp[i][j][1] = 0;
            }
        }
        dp[0][0][1] = 1;
        for (int i = 1; i < n; i++){
            for (int j = 0; i+j < n; j++){
                //placing on top
                if (j > 0){
                    dp[i][j][1] += dp[i-1][j-1][0];
                    dp[i][j][1] = (dp[i][j][1] % M + M) % M;
                    if (a[i] != a[i-1]){
                        dp[i][j][1] += dp[i-1][j-1][1];
                        dp[i][j][1] = (dp[i][j][1] % M + M) % M;
                    }
                }
                //placing on top, version 2
                if (i+j == n-1){
                    dp[i][j][0] += dp[i-1][j][0];
                    dp[i][j][0] = (dp[i][j][0] % M + M) % M;
                    if (a[i] != a[i-1]){
                        dp[i][j][0] += dp[i-1][j][1];
                        dp[i][j][0] = (dp[i][j][0] % M + M) % M;
                    }
                }
                //sandwiching
                if (a[i] == a[i-1]){
                    dp[i][j][1] += dp[i-1][j+1][1] * j; // j+1-1 options (no top)
                    dp[i][j][1] = (dp[i][j][1] % M + M) % M;
                }
                dp[i][j][0] += dp[i-1][j+1][0] * (j+1);
                dp[i][j][0] = (dp[i][j][0] % M + M) % M;
                if (a[i] != a[i-1]){
                    dp[i][j][0] += dp[i-1][j+1][1] * (j+1);
                    dp[i][j][0] = (dp[i][j][0] % M + M) % M;
                }
                if (cnts[i]){
//                    if (dp[i][j][0] % fact[cnts[i]] != 0){
//                        assert(false);
//                    }
//                    if (dp[i][j][1] % fact[cnts[i]] != 0){
//                        cerr << i << " " << j << " " << cnts[i] << " " << dp[i][j][1] << "\n";
//                        assert(false);
//                    }
                    dp[i][j][0] = dp[i][j][0] * ifact[cnts[i]];
                    dp[i][j][1] = dp[i][j][1] * ifact[cnts[i]];
                    dp[i][j][0] = (dp[i][j][0] % M + M) % M;
                    dp[i][j][1] = (dp[i][j][1] % M + M) % M;
                }
            }
        }
//        cout << dp[6][1][0] << "\n";
        cout << ((dp[n-1][0][0] + dp[n-1][0][1]) % M + M) % M << "\n";
    }
}
