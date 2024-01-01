#include <bits/stdc++.h>

using namespace std;

#define int long long
const int mxN = 3e6;
int M;
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

    int n;
    cin >> n >> M;
    precalc();
    int zero = 1;
    int one = ((2 * fac[2*n] - fac[n] - 1) % M + M) % M;
    int three = 0;
    for (int a = 0; a <= n; a++){
        three = (three + ((binpow(nCr(n, a), 2) * nCr(2*n-a, n-a)) % M) + M) % M;
    }
    three = (three * binpow(fac[n], 3));
    three = (three % M + M) % M;
    three = ((three + fac[3*n] - ((((fac[2*n] * fac[n]) % M * nCr(2*n, n)) % M) * 2) % M) % M + M) % M;
    int two = ((fac[3*n] - zero - one - three) % M + M) % M;
//    cout << zero << " " << one << " " << two << " " << three << "\n";
    int ans = ((three * 3) % M + M) % M;
    ans = ((ans + (two * 2)) % M + M) % M;
    ans = ((ans + one) % M + M) % M;
    cout << ans << "\n";
}