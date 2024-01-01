#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n, k; cin >> n >> k;
        vector<int> a(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        vector<int> diff(n-1);
        for (int i = 0; i < n-1; i++){
            diff[i] = abs(a[i+1] - a[i]);
        }
        sort(diff.rbegin(), diff.rend());
        int ans = 0;
        for (int i = 0; i < k-1; i++){
            ans += diff[i];
        }
        cout << accumulate(diff.begin(), diff.end(), 0) - ans << "\n";
    }
}