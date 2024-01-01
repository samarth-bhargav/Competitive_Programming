#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define int ll
const int MOD = 998244353;
const int MXN = 2e5+5;

#define dbg(x) cerr << x << "\n"
#define FORN(i, a, b) for(int i = a; i < b; i++)

template<const int MOD> struct Modular {
    static const int mod = MOD;
    int v; explicit operator int() const { return v; } // explicit -> don't silently convert to int
    Modular():v(0) {}
    Modular(ll _v) { v = int((-MOD < _v && _v < MOD) ? _v : _v % MOD); if (v < 0) v += MOD; }
    bool operator==(const Modular& o) const { return v == o.v; }
    friend bool operator!=(const Modular& a, const Modular& b) { return !(a == b); }
    friend bool operator<(const Modular& a, const Modular& b) { return a.v < b.v; }
    Modular& operator+=(const Modular& o) { if ((v += o.v) >= MOD) v -= MOD; return *this; }
    Modular& operator-=(const Modular& o) { if ((v -= o.v) < 0) v += MOD; return *this; }
    Modular& operator*=(const Modular& o) { v = int((ll)v*o.v%MOD); return *this; }
    Modular& operator/=(const Modular& o) { return (*this) *= inv(o); }
    friend Modular mpw(Modular a, ll p) {
        Modular ans = 1;
        for (; p; p /= 2, a *= a) if (p&1) ans *= a;
        return ans; }
    friend Modular inv(const Modular& a) { return mpw(a,MOD-2); }
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
using pM = pair<Mint, Mint>;

Mint modpow(Mint a, ll p) {
    Mint ans = 1;
    for (; p; p /= 2, a *= a) if (p&1) ans *= a;
    return ans;
}
Mint invert(Mint a) { return modpow(a,MOD-2); }

vector<Mint> fc(MXN+1), iv(MXN+1);
void precompute_factorials() {
    fc[0] = 1;
    FORN(i,1,MXN+1) fc[i] = fc[i-1] * i;
    FORN(i,0,MXN+1) iv[i] = invert(fc[i]);
}
Mint choose(ll n, ll k) { return (n < k ? 0 : fc[n] * iv[k] * iv[n-k]); }

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    precompute_factorials();
    int n, m; cin >> n >> m;
    string astr, bstr; cin >> astr >> bstr;
    vector<int> a(n), b(m);
    vector<int> acnt(27, 0), bcnt(27, 0);

    for (int i = 0; i < n; i++){
        a[i] = astr[i] - 'A' + 1;
        acnt[a[i]]++;
    }
    for (int i = 0; i < m; i++){
        b[i] = bstr[i] - 'A' + 1;
        bcnt[b[i]]++;
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    Mint dp[27][m+1];
    Mint pre[27][m+2];
    for (int i = 0; i <= 26; i++){
        for (int j = 0; j <= m; j++){
            dp[i][j] = Mint(0);
        }
    }
    dp[0][0] = 1;
    pre[0][0] = 0;
    for (int j = 1; j <= m+1; j++){
        pre[0][j] = 1;
    }
    for (int i = 1; i <= 26; i++){
        int a_cnt = acnt[i];
        int b_cnt = bcnt[i];
        for (int j = 0; j <= (i == 26 ? 0 : bcnt[i+1]); j++){
            if (a_cnt < j) break;
            if (b_cnt - (a_cnt - j) >= 0){
                dp[i][j] = pre[i-1][b_cnt - (a_cnt - j) + 1];
            }
            dp[i][j] *= choose(a_cnt, j);
        }
        pre[i][0] = 0;
        for (int j = 1; j <= m+1; j++) pre[i][j] = pre[i][j-1] + dp[i][j-1];
    }

    Mint orig = fc[n];
    for (int i = 1; i <= 26; i++){
        orig *= iv[acnt[i]];
    }

    cout << dp[26][0] * orig << "\n";
}