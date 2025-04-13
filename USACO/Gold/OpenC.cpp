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

#define int long long

int32_t main(){
    int n; cin >> n;
    vector<int> a(n+1), b(n+1);

    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];

    int dp[n+1][n+1];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;

    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            int sum_k = 0;
            for (int k = i; k >= 1; k--){
                sum_k += a[k];
                int sum_l = 0;
                for (int l = j; l >= 1; l--){
                    sum_l += b[l];
                    if ((i - k + 1) * sum_l >= (j - l + 1) * sum_k){
                        dp[i][j] += dp[k-1][l-1];
                        dp[i][j] %= (1000000007);
                    }
                }
            }
        }
    }

    const int M = 1e9 + 7;
    cout << ( dp[n][n] % M + M) % M << "\n";
}