#include <bits/stdc++.h>
using namespace std;


#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

#define oset tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>

const int M = 1e9+7;
const int mxN = 1e5;
int dp[mxN];

int pow(long long x, unsigned int y, int p){
    int res = 1;
    x = x % p;
    if (x == 0) return 0;
    while (y > 0){
        if (y & 1){
            res = (res*x) % p;
        }
        y = y>>1;
        x = (x*x) % p;
    }
    return (res%p + p) % p;
}

int main(){
    ifstream cin("help.in");
    ofstream cout("help.out");
    int n; cin >> n;
    vector<pair<int,int>> intervals(n);
    for (int i = 0; i < n; i++){
        cin >> intervals[i].first >> intervals[i].second;
    }
    sort(intervals.begin(), intervals.end());
    dp[0] = 1;
    oset startpoints, endpoints;
    startpoints.insert(intervals[0].first);
    endpoints.insert(intervals[0].second);
    for (int i = 1; i < n; i++){
        int outside = 0;
        //find # of startpoints STRICTLY above intervals[i].second
        auto it1 = startpoints.lower_bound(intervals[i].second);
        if (it1 != startpoints.end()){
            outside += i - startpoints.order_of_key(*startpoints.lower_bound(intervals[i].second));
        }
        //find # of endpoints STRICTLY below intervals[i].first
        auto it = endpoints.lower_bound(intervals[i].first);
        if (it != endpoints.begin()){
            outside += endpoints.order_of_key(*prev(endpoints.lower_bound(intervals[i].first))) + 1;
        }
        dp[i] = (((2*dp[i-1]) % M + pow(2, outside, M)) % M + M) % M;
        startpoints.insert(intervals[i].first);
        endpoints.insert(intervals[i].second);
    }
    cout << (dp[n-1]%M + M) % M << "\n";
}
