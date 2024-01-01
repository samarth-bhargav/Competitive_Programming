#include <bits/stdc++.h>

using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int s, k; cin >> s >> k;
        if (s % 10 == 5){
            cout << max(s * k, (s + 5) * (k - 1)) << "\n";
            continue;
        }
        else if (s % 10 == 0){
            cout << s * k << "\n";
            continue;
        }
        int ans = 0;
        while (s % 10 != 2 && k >= 0){
            ans = max(ans, s * k);
            s += s % 10; k--;
        }
        ans = max(ans, s * k);
        //(s + 20n) * (k - 4n) = (s * k - 4ns + 20nk - 80n^2)
        //differentiate to get -4s + 20k - 160n = 0, n ~ (20k - 4s) / 160
        for (int i = 0; i < 4; i++){
            int n = (20 * k - 4 * s) / 160;
            if (n * 4 >= k){
                ans = max(ans, (s + 20 * (k / 4)) * (k - 4 * (k / 4)));
                continue;
            }
            else if (n < 0){
                ans = max(ans, s * k);
                continue;
            }
            for (int nd = -2; nd <= 2; nd++){
                if (0 <= n + nd && n + nd <= k / 4){
                    ans = max(ans, (s + 20 * (n+nd)) * (k - 4 * (n+nd)));
                }
            }
            s += s % 10; k--;
        }
        cout << ans << "\n";
    }
}