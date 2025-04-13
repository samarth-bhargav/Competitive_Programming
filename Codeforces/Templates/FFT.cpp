#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#define dbg(...) cerr << "LINE "<<__LINE__<<": -> [" << #__VA_ARGS__ << "]:", dbg_out(__VA_ARGS__)
#else
#define dbg(...) 7;
#endif

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
Mint g = 5; //primitive root
Mint i2 = (MOD+1) / 2;

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

vector<Mint> fft(vector<Mint> a, bool invert){
    int N = a.size();
    if (N == 1){
        return a;
    }
    vector<Mint> even(N/2), odd(N/2);
    for (int i = 0; i < N; i++){
        if (i % 2 == 0){
            even[i / 2] = a[i];
        }
        else{
            odd[i / 2] = a[i];
        }
    }
    vector<Mint> even_fft = fft(even, invert);
    vector<Mint> odd_fft = fft(odd, invert);
    Mint rou = modpow(g, (MOD-1) / N);

    if (invert){
        rou = rou.inv(rou);
    }

    vector<Mint> res(N);
    Mint curr_rou = 1;

    for (int i = 0; i < N / 2; i++){
        res[i] = even_fft[i] + curr_rou * odd_fft[i];
        res[i + N/2] = even_fft[i] - curr_rou * odd_fft[i];
        if (invert){
            res[i] *= i2;
            res[i + N/2] *= i2;
        }
        curr_rou *= rou;
    }
    return res;
}

vector<Mint> multiply(vector<Mint> &a, vector<Mint> &b){
    int N = 1;
    while (N <= a.size() + b.size()){
        N <<= 1;
    }
    a.resize(N, 0);
    b.resize(N, 0);

    vector<Mint> a_dft = fft(a, false);
    vector<Mint> b_dft = fft(b, false);
    vector<Mint> ab_dft(N);
    for (int i = 0; i < N; i++){
        ab_dft[i] = a_dft[i] * b_dft[i];
    }
    vector<Mint> res = fft(ab_dft, true);
    return res;
}

int32_t main(){

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M; cin >> N >> M;
    vector<Mint> a(N), b(M);
    for (int i = 0; i < N; i++){
        int x; cin >> x; a[i] = x;
    }
    for (int i = 0; i < M; i++){
        int x; cin >> x; b[i] = x;
    }

    vector<Mint> res = multiply(a, b);
    for (int i = 0; i <= (N-1 + M-1); i++){
        cout << res[i] << " ";
    }
    cout << "\n";

}
