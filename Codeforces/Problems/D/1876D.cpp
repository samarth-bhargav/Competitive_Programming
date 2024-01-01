#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define int ll
const int M = 998244353;

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
using Mint = Modular<M>;
const Mint I2 = 499122177;

Mint modpow(Mint a, ll p) {
    Mint ans = 1;
    for (; p; p /= 2, a *= a) if (p&1) ans *= a;
    return ans;
}
Mint invert(Mint a) { return modpow(a,M-2); }

struct dsu{
    vector<int> p;
    dsu(int n){
        p.resize(n); iota(p.begin(), p.end(), 0);
    }
    int find(int x){
        return x ^ p[x] ? p[x] = find(p[x]): x;
    }
    void join(int a, int b){
        a = find(a); b = find(b);
        p[a] = b;
    }
};

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    vector<int> a(n);
    map<int, int> cnts;
    for (int i = 0; i < n; i++){
        cin >> a[i];
        cnts[a[i]]++;
    }
    int c = cnts.size();
    for (auto x : cnts){
        if (x.second % 2 == 1){
            cout << modpow(2, c-1) << "\n";
            return 0;
        }
    }
    queue<int> curr_nums;
    vector<vector<int>> intervals;
    set<int> curr_inside;
    vector<int> curr;
    for (int i = 0; i < n; i++){
        if (curr_nums.empty()){
            intervals.push_back(curr);
            curr.clear();
        }
        if (curr_inside.contains(a[i]) && curr_nums.front() != a[i]){
            cout << modpow(2, c-1) << "\n";
            return 0;
        }
        else if (!curr_nums.empty() && curr_nums.front() == a[i]){
            curr_nums.pop();
            curr_inside.erase(a[i]);
        }
        else{
            curr_nums.push(a[i]);
            curr_inside.insert(a[i]);
        }
    }
    assert(curr_nums.empty());
    dsu d(200001);
    for (vector<int> &x : intervals){
        for (int j = 1; j < x.size(); j++){
            d.join(x[j], x[j-1]);
        }
    }
    set<int> components;
    for (int i = 0; i < n; i++){
        components.insert(d.find(a[i]));
    }
    Mint mid = modpow(2, (ll)components.size());
    Mint ans = (modpow(2, c) - mid) * I2;
    cout << ans << "\n";
}
