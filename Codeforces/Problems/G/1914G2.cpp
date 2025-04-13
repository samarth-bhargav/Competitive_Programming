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

const int M = 998244353;
const int M2 = 1e9 + 7;
 
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
using Mint2 = Modular<M2>;
 
Mint modpow(Mint a, ll p) {
    Mint ans = 1;
    for (; p; p /= 2, a *= a) if (p&1) ans *= a;
    return ans;
}

Mint2 modpow(Mint2 a, ll p){
    Mint2 ans = 1;
    for (; p; p /= 2, a *= a) if (p&1) ans *= a;
    return ans;
}

Mint invert(Mint a) { return modpow(a,M-2); }

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<int> a(2 * n);
        for (int i = 0; i < 2 * n; i++){
            cin >> a[i];
        }
        set<int> active;
        vector<vector<int>> divisions;
        vector<int> curr;
        for (int i = 0; i < 2 * n; i++){
            if (active.empty() && i != 0){
                divisions.push_back(curr);
                curr.clear();     
            }
            if (active.count(a[i])){
                active.erase(a[i]);
            }
            else{
                active.insert(a[i]);
            }
            curr.push_back(a[i]);
        }
        if (!curr.empty()){
            divisions.push_back(curr);
        }
        dbg(divisions);

        vector<int> goods;

        for (vector<int> &arr : divisions){
            int tot_bad = 0;
            vector<array<int, 2>> ranges;
            map<pair<Mint, Mint2>, int> hash_to_t;
            Mint hash1 = 0;
            Mint2 hash2 = 0;
            set<int> active;
            for (int i = 0; i < arr.size(); i++){
                if (active.count(arr[i])){
                    active.erase(arr[i]);
                    hash1 -= modpow(Mint(2), arr[i]);
                    hash2 -= modpow(Mint2(2), arr[i]);
                }
                else{
                    active.insert(arr[i]);
                    hash1 += modpow(Mint(2), arr[i]);
                    hash2 += modpow(Mint2(2), arr[i]);
                }
                if (hash_to_t.count({hash1, hash2})){
                    int st = hash_to_t[{hash1, hash2}];
                    ranges.push_back({st+1, i});
                }
                else{
                    hash_to_t[{hash1, hash2}] = i;
                }
            }
            dbg(ranges);
            if (ranges.empty()){
                goods.push_back((arr.size() / 2));
                continue;
            }
            sort(ranges.begin(), ranges.end());
            vector<array<int, 2>> actual_ranges;
            int curr_ep = ranges[0][1], curr_st = ranges[0][0];
            for (int i = 1; i < ranges.size(); i++){
                if (ranges[i][0] > curr_ep + 1){
                    actual_ranges.push_back({curr_st, curr_ep});
                    curr_st = ranges[i][0]; curr_ep = ranges[i][1];   
                }
                curr_ep = max(curr_ep, ranges[i][1]);
            }
            actual_ranges.push_back({curr_st, curr_ep});
            for (auto x : actual_ranges){
                assert((x[1] - x[0]) & 1);
                tot_bad += (x[1] - x[0] + 1) / 2;
            }
            goods.push_back((arr.size() / 2) - tot_bad);
        }
        Mint ways = 1;
        dbg(goods);
        for (int x : goods){
            ways *= (x * 2);
        }
        cout << divisions.size() << " " << ways << "\n";
    }
}