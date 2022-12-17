#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int mxN = 5e3;
ll INF = 1e18;

map<ll, ll> dp_p1[mxN], dp_p2[mxN]; //{(time to reload laser), (time to get to h)}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int p1, p2, h_f, s; ll t1, t2;
    cin >> p1 >> t1 >> p2 >> t2 >> h_f >> s;

    dp_p1[0][t2] = 0;
    dp_p2[0][t1] = 0;

    ll ans = INF;

    for (int h = 1; h <= h_f; h++){
        if (h - p1 - p2 + s >= 0){
            //firing both at same time
            dp_p1[h][t2] = INF;
            dp_p2[h][t1] = INF;
            for (pair<ll, ll> kv : dp_p1[h - p1 - p2 + s]){
                dp_p1[h][t2] = min(dp_p1[h][t2], kv.second + max(kv.first, t1));
                dp_p2[h][t1] = min(dp_p2[h][t1], dp_p1[h][t2]);
            }
            for (pair<ll, ll> kv : dp_p2[h - p1 - p2 + s]){
                dp_p2[h][t1] = min(dp_p2[h][t1], kv.second + max(kv.first, t2));
                dp_p1[h][t2] = min(dp_p1[h][t2], dp_p2[h][t1]);
            }
        }
        if (h - p1 + s >= 0){
            //firing p1
            for (pair<ll, ll> kv : dp_p1[h - p1 + s]){
                if (dp_p1[h].find(max(0LL, kv.first - t1)) == dp_p1[h].end()){
                    dp_p1[h][max(0LL, kv.first - t1)] = INF;
                }
                dp_p1[h][max(0LL, kv.first - t1)] = min(dp_p1[h][max(0LL, kv.first - t1)], kv.second + t1);
            }
            for (pair<ll, ll> kv : dp_p2[h - p1 + s]) {
                if (dp_p1[h].find(max(0LL, t2 - kv.first)) == dp_p1[h].end()) {
                    dp_p1[h][max(0LL, t2 - kv.first)] = INF;
                }
                dp_p1[h][max(0LL, t2 - kv.first)] = min(dp_p1[h][max(0LL, t2 - kv.first)], kv.second + kv.first);
            }
        }
        if (h - p2 + s >= 0){
            //firing p2
            for (pair<ll, ll> kv : dp_p2[h - p2 + s]){
                if (dp_p2[h].find(max(0LL, kv.first - t2)) == dp_p2[h].end()){
                    dp_p2[h][max(0LL, kv.first - t2)] = INF;
                }
                dp_p2[h][max(0LL, kv.first - t2)] = min(dp_p2[h][max(0LL, kv.first - t2)], kv.second + t2);
            }
            for (pair<ll, ll> kv : dp_p1[h - p2 + s]) {
                if (dp_p2[h].find(max(0LL, t1 - kv.first)) == dp_p2[h].end()) {
                    dp_p2[h][max(0LL, t1 - kv.first)] = INF;
                }
                dp_p2[h][max(0LL, t1 - kv.first)] = min(dp_p2[h][max(0LL, t1 - kv.first)], kv.second + kv.first);
            }
        }
    }
    for (int h = 0; h <= h_f; h++){
        if (h + p1 - s >= h_f){
            for (auto kv : dp_p2[h]){
                ans = min(ans, kv.first + kv.second);
            }
            for (auto kv : dp_p1[h]){
                ans = min(ans, kv.second + t1);
            }
        }
        if (h + p2 - s >= h_f){
            for (auto kv : dp_p1[h]){
                ans = min(ans, kv.first + kv.second);
            }
            for (auto kv : dp_p2[h]){
                ans = min(ans, kv.second + t2);
            }
        }
        if (h + p1 + p2 - s >= h_f){
            for (auto kv : dp_p1[h]){
                ans = min(ans, kv.second + max(kv.first, t1));
            }
            for (auto kv : dp_p2[h]){
                ans = min(ans, kv.second + max(kv.first, t2));
            }
        }
    }
    for (auto elem : dp_p1[h_f]){
        ans = min(ans, elem.second);
    }
    for (auto elem : dp_p2[h_f]){
        ans = min(ans, elem.second);
    }
    cout << ans << "\n";
}