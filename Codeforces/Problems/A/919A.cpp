//#pragma GCC optimize("O3,unroll-loops")
//#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

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

const int M = 1e9+7;

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

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    if (n <= 5000){
        //brute force
        int ans = 0;
        for (int i = 0; i < n; i++){
            multiset<int> occ;
            int curr_min = INT_MAX;
            for (int j = i; j < n; j++){
                occ.insert(a[j]);
                auto it = occ.lower_bound(a[j]);
                if (it != occ.begin()){
                    curr_min = min(curr_min, a[j] ^ *(prev(it)));
                }
                if (it != prev(occ.end())){
                    curr_min = min(curr_min, a[j] ^ *(next(it)));
                }
                if (curr_min < k) break;
                if (curr_min == k){
                    ans++;
                }
            }
        }
        cout << ans << "\n";
    }
    else if (k == 0){
        vector<int> nxt(n, 1e9);
        map<int, vector<int>> curr;
        for (int i = 0; i < n; i++){
            for (int x : curr[a[i]]){
                nxt[x] = i;
            }
            curr[a[i]].clear();
            curr[a[i]].push_back(i);
        }
        for (int i = n-2; i >= 0; i--){
            nxt[i] = min(nxt[i], nxt[i+1]);
        }
//        dbg(nxt);
        long long ans = 0;
        for (int i = 0; i < n; i++){
            ans += max((ll)n - nxt[i], 0LL);
        }
        cout << ans << "\n";
    }
}