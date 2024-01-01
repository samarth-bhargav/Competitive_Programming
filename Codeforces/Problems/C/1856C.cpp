#include <bits/stdc++.h>

using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n, k; cin >> n >> k;
        vector<int> a(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        int ans = 0;
        for (int mx = 0; mx < n; mx++){
            int lo = a[mx], hi = 1e10;
            int old_k = k;
            while (lo < hi){
                k = old_k;
                int mid = (lo + hi + 1) / 2;
                //mid is the max you're trying to achieve
                int lst = n;
                for (int i = mx+1; i < n; i++){
                    if (a[i] >= mid - (i - mx)){
                        lst = i; break;
                    }
                }
                if (lst == n){
                    hi = mid-1;
                    continue;
                }
                for (int j = lst-1; j >= mx; j--){
                    //set a[j] = mid - (j - mx)
                    k -= ((mid - (j - mx)) - a[j]);
                    if (k < 0) break;
                }
                if (k < 0){
                    hi = mid-1; continue;
                }
                else{
                    lo = mid;
                }
            }
            k = old_k;
            ans = max(ans, lo);
        }
        cout << ans << "\n";
    }
}