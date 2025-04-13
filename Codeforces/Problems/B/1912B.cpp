#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#define dbg(...) cerr<< "LINE "<<__LINE__<<": -> [" << #__VA_ARGS__ << "]:", dbg_out(__VA_ARGS__)
#else
#define dbg(...) 7;
#endif

typedef long long ll;
#define int ll

const int M = 998244353;

#define FORN(i, a, b) for(int i = a; i < b; i++)

template<int MOD> struct Modular {
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
using Mint = Modular<M>;

Mint modpow(Mint a, ll p) {
    Mint ans = 1;
    for (; p; p /= 2, a *= a) if (p&1) ans *= a;
    return ans;
}
Mint invert(Mint a) { return modpow(a,M-2); }

const int MXN = 1e5+2;

vector<Mint> fc(MXN+1), iv(MXN+1);
void precompute_factorials() {
    fc[0] = 1;
    FORN(i,1,MXN+1) fc[i] = fc[i-1] * i;
    FORN(i,0,MXN+1) iv[i] = invert(fc[i]);
}
Mint choose(ll n, ll k) { return (n < k ? 0 : fc[n] * iv[k] * iv[n-k]); }


int32_t main(){
    precompute_factorials();
    int t; cin >> t;
    while (t--){
        auto mid_ops = [&](int x){
            return (x % 2 == 1 ? (x / 2) * (x / 2) : (x / 2 - 1) * (x / 2));
        };

        auto end_ops = [&](int x){
            return x * (x - 1) / 2;
        };

        int n, k; cin >> n >> k;
        if (k == 1){
            cout << end_ops(n / 2) + end_ops(n - n / 2) << " " << (n % 2 == 0 ? 1 : 2) << "\n";
            continue;
        }
        int ans = 1e18;
        Mint cnt = 0;
        for (int s = max(0LL, n / k - 10); s <= min(n, n / k + 10); s++){
            int left = n - s;
            int v1 = (n - s) / (k - 1);
            int type2 = left - v1 * (k - 1);
            int type1 = (k - 1) - type2;
            if (v1 == 0 || s / 2 == 0){
                continue;
            }
            int tot = mid_ops(v1) * type1 + mid_ops(v1+1) * type2 + end_ops(s / 2) + end_ops(s - s / 2);
            if (tot < ans){
                cnt = 0;
                ans = tot;
            }
            if (tot == ans){
                if (v1 == 3 || v1+1 == 3){
                    int x, y;
                    if (v1 == 3){
                        x = type1; y = type2;
                    }
                    else{
                        x = type2; y = type1;
                    }
                    for (int i = 0; i <= x / 2; i++){
                        cnt += (fc[k-1] * iv[x - 2 * i] * iv[y + i] * iv[i]) * (s % 2 == 1 ? 2 : 1);
                    }
                    continue;
                }
                cnt += (fc[k-1] * iv[type1] * iv[type2]) * (s % 2 == 1 ? 2 : 1);
            }
        }
        cout << ans << " " << cnt << "\n";
    }
}