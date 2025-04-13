#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
void dbg_out() { cerr << "\033[0m" << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#define dbg(...) cerr<<"\033[1;31m"<< "LINE "<<__LINE__<<": -> [" << #__VA_ARGS__ << "]:", dbg_out(__VA_ARGS__)
#else
#define dbg(...) 7;
#endif

typedef long long ll;
const int MOD = 1e9+7;
#define int ll

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
const int mxN = 5005;
vector<Mint> f(mxN), invf(mxN);
Mint nCr[mxN][mxN];

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
    memset(nCr, 0, sizeof(nCr));
    for (int i = 0; i < mxN; i++){
        nCr[i][0] = 1;
    }
    for (int i = 1; i < mxN; i++){
        for (int j = 1; j <= i; j++){
            nCr[i][j] = nCr[i-1][j] + nCr[i-1][j-1];
        }
    }
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    precompute_factorials();

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];;
        }

        vector<int> pf_min(n, 1e9);
        vector<int> sf_min(n, 1e9);
        pf_min[0] = (a[0] == -1 ? 1e9 : a[0]);
        sf_min[n-1] = (a[n-1] == -1 ? 1e9 : a[n-1]);

        for (int i = 1; i < n; i++){
            pf_min[i] = min(pf_min[i-1], (a[i] == -1 ? (int)1e9 : a[i]));
        }
        for (int i = n-2; ~i; i--){
            sf_min[i] = min(sf_min[i+1], (a[i] == -1 ? (int)1e9 : a[i]));
        }
        Mint dp[n+1][n+2];
        for (int i = 0; i <= n; i++){
            for (int j = 0; j <= n+1; j++){
                dp[i][j] = 0;
            }
        }

        vector<int> pos(n, -1);
        for (int i = 0; i < n; i++){
            if (a[i] != -1){
                pos[a[i]] = i;
            }
        }
        vector<int> present_till_m(n+1, 0);
        present_till_m[0] = (pos[0] == -1 ? 0 : 1);
        for (int i = 1; i <= n; i++){
            present_till_m[i] = present_till_m[i-1];
            if (pos[i] != -1){
                present_till_m[i]++;
            }
        }
        for (int l = 0; l < n; l++){
            int c1 = 0;
            for (int r = l; r < n; r++){
                if (a[r] == -1){
                    c1++;
                }
                int mm = n;
                if (l > 0){
                    mm = min(mm, pf_min[l-1]);
                }
                if (r < n-1){
                    mm = min(mm, sf_min[r+1]);
                }
                // present_till_m[mx-1] + c1 == r - l + 1
                int lo = 1, hi = mm;
                while (lo < hi){
                    int mid = (lo + hi + 1) / 2;
                    if (c1 < mid - present_till_m[mid - 1]){
                        hi = mid-1;
                    }
                    else{
                        lo = mid;
                    }
                }
                mm = hi;
                dp[c1][0] += 1;
                dp[c1][mm+1] -= 1;
            }
        }
        for (int c1 = 0; c1 <= n; c1++){
            for (int mx = 1; mx <= n+1; mx++){
                dp[c1][mx] += dp[c1][mx-1];
            }
        }

        int free = 0;
        for (int i = 0; i < n; i++){
            if (a[i] == -1){
                free++;
            }
        }



        Mint ans = 0;

        for (int c1 = 0; c1 <= n; c1++){
            for (int mx = 1; mx <= n+1; mx++){
                int c2 = mx - present_till_m[mx-1];
                ans += nCr[c1][c2] * f[c2] * f[free - c2] * dp[c1][mx];
            }
        }

        cout << ans << "\n";
    }
}