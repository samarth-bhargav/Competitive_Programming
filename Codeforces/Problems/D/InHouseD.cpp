#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
using namespace std::chrono;
#define pb push_back
#define f first
#define s second
#define endl "\n"
#define mp make_pair
#define FASTIO ios_base::sync_with_stdio(false);cin.tie(NULL);
#define TC int tc; cin >> tc; while (tc--) solve();
#define FORN(i, a, b) for(int i = a; i < b; i++)
#define REV(i, b, a) for(int i = b - 1; i >= a; i--)
#define EACH(x, a) for(auto &x : a)
#define DBG(z) FORN(lopital,0,sz(z))cerr<<z[lopital]<<" \n"[lopital==sz(z)-1];
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define rall(a) (a).rbegin(), (a).rend()
#define log(x) (63-__builtin_clzll(x))
#define tcT template<class T
#define tcTU tcT, class U
#define lb lower_bound
#define ub upper_bound
// #define int ll
using ll = long long;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using ppl = pair<pl, pl>;
tcT> using vt = vector<T>;
tcT> using pq = priority_queue<T>;
tcT> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
tcT> using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
tcTU> using ordered_map = tree<T, U, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
tcTU> using ordered_multimap = tree<T, U, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
tcT> inline void chmin(T &a, T b) {a = min(a, b);}
tcT> inline void chmax(T &a, T b) {a = max(a, b);}
const ll MOD = 998244353, MXN = 1e3+5, INF = 1e15;

struct tup {
    ll pts, pen, tot;
    bool operator<(tup &o) {
        if (pts == o.pts) {
            if (pen == o.pen) {
                return tot > o.tot;
            }
            return pen > o.pen;
        }
        return pts < o.pts;
    }
};

void solve() {
    ll n, t; cin >> n >> t;
    vt<pl> arr(n);
    FORN(i,0,n) cin >> arr[i].f;
    FORN(i,0,n) cin >> arr[i].s;
    sort(all(arr));

    vt<vt<tup>> dp(n, vt<tup>(t+1, {-INF, INF, INF}));
    FORN(j,0,t+1) dp[0][j] = {0, 0, 0};
    dp[0][arr[0].f] = {arr[0].s, arr[0].f, arr[0].f};
    FORN(i,1,n) {
        FORN(j,0,t+1) {
            dp[i][j] = dp[i-1][j];
            if (j - arr[i].f >= 0) {
                tup nxt{dp[i-1][j-arr[i].f].pts + arr[i].s, dp[i-1][j-arr[i].f].pen + dp[i-1][j-arr[i].f].tot + arr[i].f, dp[i-1][j-arr[i].f].tot + arr[i].f};
                if (dp[i][j] < nxt) {
                    dp[i][j] = nxt;
                }
            }
            // cerr<<i<<" "<<j<<" "<<dp[i][j].pts<<" "<<dp[i][j].pen<<" "<<dp[i][j].tot<<endl;
        }
    }
    tup ans{-INF, INF, INF};
    FORN(j,0,t+1) {
        if (ans < dp[n-1][j]) {
            ans = dp[n-1][j];
        }
    }
    cout << ans.pts << " " << ans.pen << endl;
}

signed main() {
    FASTIO
    solve();
}