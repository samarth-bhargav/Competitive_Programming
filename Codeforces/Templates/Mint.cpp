#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int MOD = 998244353;

template<const int MOD> struct Modular {
    static const int mod = MOD;
    int v; explicit operator int() const { return v; }
    Modular():v(0) {}
    Modular(ll _v) { v = int((-MOD < _v && _v < MOD) ? _v : _v % MOD); if (v < 0) v += MOD; }
    bool operator==(const Modular& o) const { return v == o.v; }
    friend bool operator!=(const Modular& a, const Modular& b) { return !(a == b); }
    friend bool operator<(const Modular& a, const Modular& b) { return a.v < b.v; }
    Modular exp(Modular a, int e){Modular res = 1; while (e){if (e % 2){res *= a;} a *= a; e >>= 1;} return res;}
    Modular inv(Modular a){return exp(a, MOD-2);}
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
const int mxN = 6e5;
vector<Mint> f(mxN), invf(mxN);

Mint modpow(Mint x, int e) {
    if (e < 0){
        return 0;
    }
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
    if (n < r) return 0;
    return f[n] * invf[n-r] * invf[r];
}

int32_t main(){
    cout << Mint(1) / Mint(2) << "\n";
}