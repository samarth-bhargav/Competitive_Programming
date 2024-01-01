#include <bits/stdc++.h>

#define int long long
using namespace std;

const int mxN = 3e5;
const int M = 998244353;
int invf[mxN+1], fac[mxN+1], ff[mxN+1];

int binpow(int x, int e){
    int res = 1;
    while (e > 0){
        if (e & 1){
            res = (res * x) % M;
        }
        x = (x * x) % M;
        e >>= 1;
    }
    return (res % M + M) % M;
}

void precalc(){
    fac[0] = 1;
    invf[0] = binpow(fac[0], M-2);
    for (int i = 1; i <= mxN; i++){
        fac[i] = (fac[i-1] * i % M + M) % M;
        invf[i] = binpow(fac[i], M-2);
    }
    ff[0] = 1; ff[1] = 1;
    for (int i = 2; i <= mxN; i++){
        ff[i] = ff[i-2] * i;
        ff[i] = (ff[i] % M + M) % M;
    }
}

int nCr(int n, int r){
    int res = fac[n];
    res *= invf[r]; res %= M;
    res *= invf[n-r]; res = (res % M + M) % M;
    return res;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    precalc();
    vector<int> a(mxN+2, 1);
    a[1] = 1; a[2] = 2;
    for (int i = 3; i <= mxN; i++){
        a[i] = a[i-1] + (i-1) * a[i-2];
        a[i] = (a[i] % M + M) % M;
    }
    while (t--){
        int n; cin >> n;
        int ans = 0;
        for (int fours = 0; fours <= n / 4; fours++){
            int twos = fours * 2;
            int ret = nCr(n - twos, twos) * (twos == 0 ? 1 : ff[twos - 1]);
            ret = (ret % M + M) % M;
            ret *= a[n - 2 * twos];
            ret = (ret % M + M) % M;
            ret *= binpow(2, fours);
            ret = (ret % M + M) % M;
            ans += ret; ans = (ans % M + M) % M;
        }
        cout << (ans % M + M) % M << "\n";
    }
}