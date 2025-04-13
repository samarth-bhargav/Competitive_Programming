#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int MOD = 1e9+7;

template<const int MOD> struct Modular {
    static const int mod = MOD;
    int v; explicit operator int() const { return v; }
    Modular():v(0) {}
    Modular(ll _v) { v = int((-MOD < _v && _v < MOD) ? _v : _v % MOD); if (v < 0) v += MOD; }
    friend Modular mpw(Modular a, ll p) {
        Modular ans = 1;
        for (; p; p /= 2, a *= a) if (p&1) ans *= a;
        return ans; }
    friend Modular inv(const Modular& a) { return mpw(a,MOD-2);}
    friend bool operator!=(const Modular& a, const Modular& b) { return !(a == b); }
    friend bool operator<(const Modular& a, const Modular& b) { return a.v < b.v; }
    Modular& operator+=(const Modular& o) { if ((v += o.v) >= MOD) v -= MOD; return *this; }
    Modular& operator-=(const Modular& o) { if ((v -= o.v) < 0) v += MOD; return *this; }
    Modular& operator*=(const Modular& o) { v = int((ll)v*o.v%MOD); return *this; }
    Modular& operator/=(const Modular& o) { return (*this) *= inv(o); }
    Modular operator-() const { return Modular(-v); }
    Modular& operator++() { return *this += 1; }
    Modular& operator--() { return *this -= 1; }
    friend Modular operator+(Modular a, const Modular& b) { return a += b; }
    friend Modular operator-(Modular a, const Modular& b) { return a -= b; }
    friend Modular operator*(Modular a, const Modular& b) { return a *= b; }
    friend Modular operator/(Modular a, const Modular& b) { return a /= b; }
    friend istream& operator>>(istream& inp, Modular& a) { ll x; inp >> x; a = Modular(x); return inp;}
    friend ostream& operator<<(ostream& out, const Modular& a) { out << a.v; return out; }
};
using Mint = Modular<MOD>;

using Mint = Modular<MOD>;
const int mxN = 1e6 + 10;
vector<Mint> f(mxN), invf(mxN);

Mint modpow(Mint x, int e) {
    Mint base = x, curr = 1;
    while (e) {
        if (e & 1) {
            curr *= base;
        }
        base = base * base;
        e >>= 1;
    }
    return curr;
}

void precompute_factorials() {
    f[0] = 1;
    for (int i = 1; i < mxN; i++) {
        f[i] = f[i-1] * i;
    }
    invf[mxN - 1] = modpow(f.back(), MOD - 2);
    for (int i = mxN - 2; i >= 0; i--) {
        invf[i] = invf[i+1] * (i + 1);
    }
}

Mint nCr(int n, int r) {
    return f[n] * invf[n-r] * invf[r];
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    precompute_factorials();

    int n, k; cin >> n >> k;
    if (n % k != 0) {
        cout << 0 << "\n";
        return 0;
    }
    int r = n / k;
    Mint prod = (f[n] * invf[r]) / modpow(k, r);
    for (int i = 1; i < r; i++){
        prod *= (i * k + 1);
    }
    cout << prod << "\n";

}
