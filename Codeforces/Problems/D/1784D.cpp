#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define int ll
const int M = 998244353;
int fact[1 << 20];
int dp[21][(1 << 20) + 1];
int pow2[21], invf[(1 << 20) + 1];

ll binpow(ll a, ll b) {
    a %= M;
    ll ret = 1;
    while (b > 0) {
        if (b % 2 == 1)
            ret = (ret * a) % M;
        a = (a * a) % M;
        b /= 2;
    }
    return (ret % M + M) % M;
}

ll nCr(ll a, ll b){
    if (a < 0) return 0;
    if (a < b) return 0;
    if (a == 0) return (b == 0);
    ll ret = fact[a];
    ret *= invf[b];
    ret %= M;
    ret *= invf[a-b];
    ret = ((ret % M) + M) % M;
    return ret;
}

int32_t main(){
    int n; cin >> n;
    memset(fact, 0, sizeof(fact));
    fact[0] = 1;
    for (int i = 1; i <= (1 << n); i++){
        fact[i] = fact[i-1] * i;
        fact[i] = (fact[i] % M + M) % M;
    }
    pow2[0] = 1;
    for (int i = 1; i <= 20; i++){
        pow2[i] = pow2[i-1] * 2;
    }
    for (int i = 0; i <= (1 << n); i++){
        invf[i] = binpow(fact[i], M-2);
    }
    n++;
    dp[1][1 << (n-1)] = nCr(pow2[n-1] - pow2[n-2] - 1, pow2[n-2] - 1);
    int pref[pow2[n-1] + 2];
    for (int k = 2; k < n; k++){
        pref[pow2[n-1] + 1] = 0;
        for (int i = pow2[n-1]; i >= 1; i--){
            pref[i] = pref[i+1] + dp[k-1][i];
            pref[i] %= M;
        }
        //pref[i] denotes sum of all dp[k-1][j] for j >= i
        for (int x = 1; x <= pow2[n-1]; x++){
            dp[k][x] = nCr(x - pow2[n-k-1] - 1, pow2[n-k-1] - 1) * pref[x+1];
            dp[k][x] %= M;
        }
    }
    pref[pow2[n-1] + 1] = 0;
    for (int i = pow2[n-1]; i >= 1; i--){
        pref[i] = pref[i+1] + dp[n-1][i];
        pref[i] = (pref[i] % M + M) % M;
    }
    vector<int> ans(pow2[n-1] + 1);
    for (int i = 1; i <= pow2[n-1]; i++){
        ans[i] = pref[i+1];
        ans[i] *= pow2[n-1]; ans[i] %= M;
        for (int j = 1; j <= n-2; j++){
            ans[i] *= fact[pow2[j]];
            ans[i] %= M;
        }
    }
    reverse(ans.begin()+1, ans.end());
    for (int i = 1; i <= (1 << (n-1)); i++){
        cout << ans[i] << "\n";
    }
}
