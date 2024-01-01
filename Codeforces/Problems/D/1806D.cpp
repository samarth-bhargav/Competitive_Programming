#include <bits/stdc++.h>

using namespace std;

#define int long long
const int M = 998244353;

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 1; i <= n-1; i++){
            cin >> a[i];
        }
        vector<int> b(n); b[0] = 1; b[1] = 1;
        for (int i = 2; i < n; i++){
            b[i] = (i-2) * b[i-1] + b[i-1] * (a[i-1] == 0);
            b[i] = (b[i] % M + M) % M;
        }
//        for (int i = 0; i < n; i++){
//            cout << b[i] << " ";
//        }
        int ans = (a[1] == 0);
        cout << ans << " ";
        for (int i = 2; i < n; i++){
            ans *= i;
            if (a[i] == 0) ans += b[i];
            ans = (ans % M + M) % M;
            cout << ans << " ";
        }
        cout << "\n";
    }
}