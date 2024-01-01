#include <bits/stdc++.h>

#define int long long
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n, k, a, b;
        cin >> n >> k >> a >> b; a--; b--;
        vector<array<int, 2>> major(k);
        vector<array<int, 2>> minor(n-k);

        auto dist = [&](array<int, 2> x, array<int, 2> y){
            return abs(x[0] - y[0]) + abs(x[1] - y[1]);
        };

        for (int i = 0; i < k; i++){
            cin >> major[i][0] >> major[i][1];
        }
        for (int i = 0; i < n-k; i++){
            cin >> minor[i][0] >> minor[i][1];
        }
        if (a < k && b < k){
            cout << 0 << "\n";
        }
        else{
            int a_dist = 1e18, b_dist = 1e18;
            if (a < k){
                a_dist = 0;
            }
            else{
                for (int i = 0; i < k; i++){
                    a_dist = min(a_dist, dist(major[i], minor[a - k]));
                }
            }
            if (b < k){
                b_dist = 0;
            }
            else{
                for (int i = 0; i < k; i++){
                    b_dist = min(b_dist, dist(major[i], minor[b - k]));
                }
            }
            int o_dist = 4e18;
            if (a >= k && b >= k){
                o_dist = min(o_dist, dist(minor[a-k], minor[b-k]));
            }
            cout << min(a_dist + b_dist, o_dist) << "\n";
        }
    }
}