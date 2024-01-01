#include <bits/stdc++.h>

using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int m, k, a1, ak;
        cin >> m >> k >> a1 >> ak;
        int up_mul = (a1 / k) * k + m % k;
        int down_mul;
        if (up_mul >= a1){
            down_mul = up_mul - k;
        }
        else{
            down_mul = up_mul + k;
        }
        if (down_mul < 0){
            down_mul = 1e18;
        }
        int k_burle_with_up = (m - up_mul) / k;
        int k_burle_with_down = (m - down_mul) / k;
        cout << min(max(0LL, k_burle_with_up - ak) + max(0LL, up_mul - a1), max(0LL, k_burle_with_down - ak) + max(0LL, down_mul - a1)) << "\n";
    }
}