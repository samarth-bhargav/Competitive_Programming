#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <deque>
#include <bitset>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <utility>
#include <limits>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>
#include <chrono>
#include <random>
#include <climits>

using namespace std;

#ifdef LOCAL
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#define dbg(...) cerr << "LINE " << __LINE__ <<": -> [" << #__VA_ARGS__ << "]:", dbg_out(__VA_ARGS__)
#else
#define dbg(...) 7;
#endif

typedef long long ll;

const int INF = 1e9;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<int> a(n+2);
        for (int i = 1; i <= n; i++){
            cin >> a[i];
        }
        a[0] = -INF; a[n+1] = INF;
        int dp[n+2][n+1];
        memset(dp, 0xc0, sizeof(dp));
        dp[0][0] = 0;
        for (int i = 1; i <= n+1; i++){
            for (int j = 0; j <= n; j++){
                if (a[i-1] < a[i]){
                    dp[i][j] = max(dp[i][j], dp[i-1][j] + 1);
                }
                for (int k = 0; k < i-1; k++){
                    if (a[k] < a[i] && j > 0){
                        dp[i][j] = max(dp[i][j], dp[k][j-1] + 1);
                    }
                }
            }
        }
//        dbg(vector<int>(dp[n], dp[n]+n+1));
        //prefix max
        for (int i = 1; i <= n; i++){
            dp[n+1][i] = max(dp[n+1][i], dp[n+1][i-1]);
        }
        for (int i = 1; i <= n; i++){
            cout << n - (dp[n+1][i] - 1) << " ";
        }
        cout << "\n";
    }
}
