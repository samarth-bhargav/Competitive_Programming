/*
Dont raise your voice,improve your argument
--Desmond Tutu
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define all(x) x.begin(),x.end()
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

#define oset tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
/*
*/

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int>a(n+1);
    for (int i = 1;i <= n; i++){
        cin >> a[i];
    }
    map<int,vector<ll>>mp;
    for (int i = 1; i <= n; i++){
        mp[a[i]].push_back(i);
    }
    ll dp1[n+1]; dp1[1] = 0LL;
    oset seq; seq.insert(1);
    for (int i = 2; i <= n; i++){
        if (mp[a[i]][0] == i){
            dp1[i] = dp1[i-1]+seq.size();
        }
        else{
            auto it = prev(lower_bound(all(mp[a[i]]),i));
            dp1[i] = dp1[i-1]+(ll)((int)seq.size()-seq.order_of_key(*it))-1;
            seq.erase(*it);
        }
        seq.insert(i);
    }
    cout << dp1[n] << "\n";
}

