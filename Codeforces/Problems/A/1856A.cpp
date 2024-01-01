#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        if (is_sorted(a.begin(), a.end())){
            cout << 0 << "\n";
            continue;
        }
        int ans = 0;
        for (int i = 0; i < n-1; i++){
            if (a[i] > a[i+1]){
                ans = max(ans, a[i]);
            }
        }
        cout << ans << "\n";
    }
}