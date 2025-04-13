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

struct dsu{
    int sz; vector<int> p;
    dsu (int sz){
        this->sz = sz;
        p.resize(sz);
        iota(p.begin(), p.end(), 0);
    }
    int find(int x){
        return x ^ p[x] ? p[x] = find(p[x]) : x;
    }
    void join(int a, int b){
        a = find(a); b = find(b);
        p[b] = a;
    }
};

const int mxN = 100;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    dsu d(2 * mxN);
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++){
        for (int j = 0; j < mxN; j++){
            d.join(j, j ^ a[i]);
        }
    }
    vector<vector<int>> dp(n+1, vector<int>(2 * mxN, 0));
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++){
        for (int x = 0; x < mxN; x++){
            dp[i][x] += dp[i-1][x];
            dp[i][x ^ a[i-1]] += 2 * dp[i-1][x];
        }
    }
    dbg(dp[n]);
    for (int i = 0; i <= 2 * n; i++){
        for (int j = 0; j < mxN; j++){
            if (d.find(i) == d.find(j)){
                if (dp[n][i] != dp[n][j]){
                    dbg(i, j);
                    dbg(dp[n][i], dp[n][j]);
                    assert(false);
                }
            }
        }
    }
}
