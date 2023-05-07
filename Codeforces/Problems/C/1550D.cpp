#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int M = 1e9+7;
const int mxF = 2e5+1;
ll fact[mxF];

ll binpow(ll a, ll b) {
    a %= M;
    ll ret = 1;
    while (b > 0) {
        if (b & 1)
            ret = (ret * a) % M;
        a = (a * a) % M;
        b >>= 1;
    }
    return (ret % M + M) % M;
}

ll nCr(ll a, ll b){
    if (b > a) return 0;
    if (b < 0) return 0;
    ll ret = fact[a];
    ret *= binpow(fact[b], M-2);
    ret = ((ret % M) + M) % M;
    ret *= binpow(fact[a - b], M-2);
    ret = ((ret % M) + M) % M;
    return ret;
}

int32_t main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fact[0] = 1;
    for (int i = 1; i < mxF; i++){
        fact[i] = fact[i-1] * i;
        fact[i] = (fact[i] % M + M) % M;
    }
    int t; cin >> t;
    while (t--){
        int n, lb, ub;
        cin >> n >> lb >> ub;
        vector<array<int, 2>> intervals;
        for (int i = 1; i <= n; i++){
            intervals.push_back({lb-i, ub-i});
        }
        set<array<int, 3>> process;
        set<array<int, 2>> active;
        for (int i = 0; i < n; i++){
            process.insert({abs(intervals[i][0]), 0, i});
            process.insert({abs(intervals[i][1]), 1, i});
            active.insert({0, i});
            active.insert({1, i});
        }
        int lst = 0;
        ll ans = 0;
        int x = 0, y = 0, z = n;
        for (auto it = process.begin(); it != process.end(); it++){
            if (x + y + z < n){
                break;
            }
            int diff = (*it)[0] - lst;
            ans += diff * nCr(z, n / 2 - x);
            ans = (ans % M + M) % M;
            if (n & 1){
                ans += diff * nCr(z, (n / 2 + 1) - x);
                ans = (ans % M + M) % M;
            }
            lst = (*it)[0];
            while ((*it)[0] == lst && it != process.end()){
                if ((*it)[1] == 0){
                    int idx = (*it)[2];
                    if (active.count({1, idx})){
                        z--; y++;
                    }
                    else{
                        x--;
                    }
                }
                else{
                    int idx = (*it)[2];
                    if (active.count({0, idx})){
                        z--; x++;
                    }
                    else{
                        y--;
                    }
                }
                active.erase({(*it)[1], (*it)[2]});
                it++;
            }
            it--;
        }
        cout << ans << "\n";
    }
}
