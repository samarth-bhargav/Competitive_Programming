#include <bits/stdc++.h>

using namespace std;

#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
#include <ext/pb_ds/detail/standard_policies.hpp>

using namespace __gnu_pbds;

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<array<int, 2>> intervals;
        for (int i = 0; i < n; i++){
            int a, b; cin >> a >> b;
            intervals.push_back({a, b});
        }
        sort(intervals.begin(), intervals.end());
        ordered_set oset;
        int ans = 0;
        for (int i = 0; i < n; i++){
            auto it = oset.lower_bound(intervals[i][1]);
            int val = oset.size();
            if (it != oset.end()){
                val = oset.order_of_key(*it);
            }
            ans += (oset.size() - val);
            oset.insert(intervals[i][1]);
        }
        cout << ans << "\n";
    }
}