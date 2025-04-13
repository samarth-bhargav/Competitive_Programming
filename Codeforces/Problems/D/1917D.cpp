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

struct Tree {
	typedef int T;
	static constexpr T unit = 0;
	T f(T a, T b) { return a+b; } // (any associative fn)
	vector<T> s; int n;
	Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
	void update(int pos, T val) {
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e)
        if (e <= b) return unit;
        if (e <= 0) return unit;
        e = min(e, n); b = max(b, 0LL);
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--){
        int n, k; cin >> n >> k;
        vector<int> p(n), q(k);
        for (int &x : p) cin >> x;
        for (int &x : q) cin >> x;

        Mint iv = 0;
        Tree inversion_st(k);
        for (int i = 0; i < k; i++){
            inversion_st.update(i, 1);
        }
        for (int i = 0; i < k; i++){
            iv += inversion_st.query(0, q[i]);
            inversion_st.update(q[i], 0);
        }

        Tree st(2 * n);
        for (int i = 0; i < n; i++){
            st.update(p[i], 1);
        }
        const int mxL = 39;
        vector<vector<int>> num_smaller(n, vector<int>(mxL));
        for (int i = 0; i < n; i++){
            st.update(p[i], 0);
            for (int j = 0; j < mxL; j++){
                if (j - mxL / 2 < 0){
                    num_smaller[i][j] = st.query(0, (p[i] >> (mxL / 2 - j)) + 1);
                }
                else{
                    num_smaller[i][j] = st.query(0, (p[i] << (j - mxL / 2)) + 1);
                }
            }
            dbg(num_smaller[i]);
            for (int j = mxL-1; j > 0; j--){
                num_smaller[i][j] -= num_smaller[i][j-1];
            }
        }
        dbg(num_smaller);
        Mint ans = 0;
        vector<vector<int>> num(k, vector<int>(mxL));
        //num[i][j] stores the number of indices k afterward s.t. q[i] - q[k] <= j
        vector<int> tot(mxL);
        for (int i = 0; i < k; i++){
            for (int j = 0; j < mxL; j++){
                num[i][j] = min(max(q[i] + (j - mxL / 2) + 1, 0LL), k);
            }
            for (int j = 0; j < mxL; j++){
                tot[j] += num[i][j];
            }
        }
        dbg(tot);
        reverse(tot.begin(), tot.end());
        for (int j = 0; j < mxL; j++){
            for (int i = 0; i < n; i++){
                ans += tot[j] * num_smaller[i][j];
            }
        }
        cout << ans + iv * n << "\n";
    }
}