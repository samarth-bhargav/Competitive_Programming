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
    bool operator==(const Modular& o) const { return v == o.v; }
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

Mint modpow(Mint a, ll p) {
    Mint ans = 1;
    for (; p; p /= 2, a *= a) if (p&1) ans *= a;
    return ans;
}

int32_t main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, q, c; cin >> n >> q >> c;
    set<array<int, 2>> aset;
    vector<array<int, 2>> a;
    map<int,int> mx;
    for (int i = 0; i < q; i++){
        int x, y; cin >> x >> y;
        if (mx.count(y)){
            mx[y] = min(mx[y], x);
        }
        else{
            mx[y] = x;
        }
    }
    for (auto &x : mx){
        a.push_back({x.second, x.first});
    }
    a.push_back({0,1});
    a.push_back({n, n+1});
    sort(a.begin(), a.end());
    q = a.size() - 2;
    for (int i = 1; i <= q+1; i++){
        if (a[i][0] < a[i-1][1]){
            cout << 0 << "\n"; return 0;
        }
    }
    Mint dp[q+2][c+2];
    Mint pref[q+2][c+2];
    for (int i = 0; i <= q+1; i++){
        for (int j = 0; j <= c+1; j++){
            dp[i][j] = 0;
            pref[i][j] = 0;
        }
    }
    for (int j = 1; j <= c; j++){
        dp[0][j] = 1;
        pref[0][j] = j;
    }
    for (int i = 1; i <= q+1; i++){
        Mint npref[c+1]; npref[0] = 0;
        for (int k = 1; k <= c; k++){
            npref[k] = npref[k-1];
            npref[k] += (modpow(k, a[i][1] - a[i-1][1] - 1) - (modpow(k - 1, a[i][0] - a[i-1][1])) * modpow(k, a[i][1] - a[i][0] - 1)) * pref[i-1][k-1];
            npref[k] += dp[i-1][k] * modpow(k, a[i][1] - a[i-1][1] - 1);
        }
        for (int j = 1; j <= (i == q + 1 ? c + 1 : c); j++){
            dp[i][j] = npref[j-1];
            pref[i][j] = pref[i][j-1] + dp[i][j];
        }
    }
    cout << dp[q+1][c+1] << "\n";
}