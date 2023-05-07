#include <bits/stdc++.h>
using namespace std;

#define int long long

int mod(int x, int m){
    return x % m == 0 ? m : x % m;
}

int32_t main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int l, r; cin >> l >> r;
        int lsqrt = sqrt(l) + 1;
        vector<array<int, 2>> ranges;
        for (int k = 1; k <= lsqrt; k++){
            int left = (l + k - 1) / k;
            int right = r / (k + 1);
            if (left <= right){
                ranges.push_back({left, right});
            }
        }
        for (int x = 1; x <= lsqrt; x++){
            if (2*x + l - mod(l, x) <= r){
                ranges.push_back({x, x});
            }
        }
        sort(ranges.begin(), ranges.end());
        //merge all ranges
        vector<array<int, 2>> rngs;
        if (ranges.empty()){
            cout << 0 << "\n";
            continue;
        }
        rngs.push_back(ranges.front());
        for (int i = 1; i < ranges.size(); i++){
            if (rngs.back()[1] >= ranges[i][0]){
                int old_f = rngs.back()[0], old_b = rngs.back()[1];
                rngs.pop_back();
                rngs.push_back({old_f, max(ranges[i][1], old_b)});
            }
            else{
                rngs.push_back(ranges[i]);
            }
        }
        int ans = 0;
        for (int i = 0; i < rngs.size(); i++){
            ans += rngs[i][1] - rngs[i][0] + 1;
        }
        cout << ans << "\n";
    }
}
