#include <bits/stdc++.h>

using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define int long long
using namespace __gnu_pbds;
typedef tree<pair<int,int>,null_type,less<pair<int,int>>,rb_tree_tag,tree_order_statistics_node_update> oset;

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n, k; cin >> n >> k;
        map<int,int> freq;
        vector<pair<int,int>> vals;
        for (int i = 0; i < n; i++){
            int x; cin >> x;
            if (freq.count(x)){
                vals.emplace_back(x, freq[x]+1);
                freq[x] += 1;
            }
            else{
                vals.emplace_back(x, 1);
                freq[x] = 2;
            }
        }
        int ans = 1e18;
        for (int tt = 0; tt < 2; tt++){
            oset start, finish;
            for (int i = 0; i < n; i++){
                finish.insert(vals[i]);
            }
            int n1 = 0, n2 = k, s1 = 0, s2 = 0;
            auto it = finish.begin();
            for (int i = 0; i < k; i++){
                s2 += it->first; it++;
            }
            int i;
            for (i = 0; s1 < s2; i++){
                if (vals[i].first < finish.find_by_order(n2-1)->first){
                    s2 -= vals[i].first;
                }
                else{
                    s2 -= finish.find_by_order(n2-1)->first;
                }
                finish.erase(vals[i]);
                s1 += vals[i].first;
                start.insert(vals[i]);
                n1++; n2--;
            }
            ans = min(ans, max(s1, s2));
            for (; i < n; i++){
                bool changed = false;
                if (n2 != 0){
                    if (vals[i].first <= finish.find_by_order(n2-1)->first){
                        changed = true;
                        s2 -= vals[i].first;
                    }
                }
                finish.erase(vals[i]);
                if (changed){
                    if (finish.size() >= n2 && !finish.empty()){
                        s2 += finish.find_by_order(n2-1)->first;
                    }
                    else if (finish.size() < n2){
                        n2--;
                    }
                }
                if (vals[i].first < start.find_by_order(n1-1)->first){
                    s1 += vals[i].first;
                    s1 -= start.find_by_order(n1-1)->first;
                }
                start.insert(vals[i]);
                while (n1 + n2 < k){
                    s1 += start.find_by_order(n1)->first; n1++;
                }
                while (s1 < s2 && n2 > 0){
                    s1 += start.find_by_order(n1)->first;
                    s2 -= finish.find_by_order(n2-1)->first;
                    n1++; n2--;
                }
                ans = min(ans, max(s1, s2));
            }
            reverse(vals.begin(), vals.end());
        }
        cout << ans << "\n";
    }
}