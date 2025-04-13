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
void dbg_out() { cerr << "\033[0m" << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#define dbg(...) cerr<<"\033[1;31m"<< "LINE "<<__LINE__<<": -> [" << #__VA_ARGS__ << "]:", dbg_out(__VA_ARGS__) 
#else
#define dbg(...) 7;
#endif

typedef long long ll;

const int mxN = 1e6+1;
int dp[mxN], ndp[mxN];

const int INF = 1e9;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--){
        int w, f; cin >> w >> f;
        w = min(w, (int)1e6); f = min(f, (int)1e6);
        int n; cin >> n;
        vector<int> s(n);
        for (int i = 0; i < n; i++){
            cin >> s[i];
        }
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= n; i++){
            //prefix to i-1
            for (int j = 0; j < mxN; j++){
                ndp[j] = min((s[i-1] > j ? INF : dp[j - s[i-1]]), dp[j] + s[i-1]);
                // dbg(i, j, ndp[j]);
            }
            swap(dp, ndp);
        }
        int ans = INF;
        for (int i = 0; i < mxN; i++){
            ans = min(ans, max((i + w - 1) / w, (dp[i] + f - 1) / f));
        }
        cout << ans << "\n";
    }
}