#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    vector<int> a(n+1);
    for (int i = 1; i <= n; i++){
        cin >> a[i];
    }

    int ans = 1e9;

    auto sorted_suffix = [&](int m){
        int lo = 1, hi = m;
        while (lo < hi){
            int mid = (lo + hi) / 2;
            if (is_sorted(a.begin() + mid, a.begin() + m + 1)){
                hi = mid;
            }
            else{
                lo = mid+1;
            }
        }
        return lo;
    };

    for (int y = 0; y <= n; y++){
        set<int> lis;
        for (int x = sorted_suffix(n-y); x <= n-y; x++){
            //LIS on a[1:x-1]
            if (x-1 >= 1 && a[x-1] >= a[n]){
                auto it = lis.upper_bound(a[x-1]);
                if (it == lis.end()){
                    lis.insert(a[x-1]);
                }
                else{
                    lis.erase(it);
                    lis.insert(a[x-1]);
                }
            }
            ans = min(ans, y + x - 1 + (x - 1 - (int)lis.size()));
        }
    }

    cout << ans << "\n";

}
