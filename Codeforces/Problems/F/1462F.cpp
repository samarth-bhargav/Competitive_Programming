#pragma optimize("O3")
#pragma target("sse4")
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

#define ordered_set tree<pair<pair<int,bool>,int>, null_type,less<pair<pair<int,bool>,int>>, rb_tree_tag,tree_order_statistics_node_update>


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--){
        int n;
        cin >> n;
        ordered_set events;
        vector<pair<int,int>>pnts;
        for (int i = 0; i < n; i++){
            int a,b;
            cin >> a >> b;
            pnts.emplace_back(a,b);
        }
        for (int i = 0; i < n; i++){
            events.insert({{pnts[i].first,0},i});
            events.insert({{pnts[i].second,1},i});
        }
        set<int>active;
        int ar[n];
        memset(ar,0,sizeof(ar));
        int prefix[2*n+1];
        memset(prefix,0,sizeof(prefix));
        auto it = events.begin();
        for (int i = 1; i <= 2*n; i++) {
            prefix[i] = prefix[i - 1] + !it->first.second;
            it++;
        }
        int pos = 0;
        for (auto & i : events){
            if (!i.first.second){
                ar[i.second] += active.size();
                active.insert(i.second);
            }
            else{
                ar[i.second] += prefix[pos] - prefix[events.order_of_key({{pnts[i.second].first,0},i.second})];
                active.erase(i.second);
            }
            pos++;
        }
        int ans = 0;
        for (int i = 0; i < n; i++){
            ans = max(ans,ar[i]);
        }
        cout << n-ans << "\n";
    }
}
