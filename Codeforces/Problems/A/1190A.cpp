#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll find(ll x, ll k){
    if (x%k == 0){
        return x-k+1;
    }
    return x-x%k+1;
}
int main(){
    ll n,m,k;
    cin >> n >> m >> k;
    set<ll>positions;
    for (int i = 0; i < m; i++){
        ll x; cin >> x;
        positions.insert(x);
    }
    ll offset = 0;
    ll ans = 0;
    while (!positions.empty()){
        ll bottom = find(*positions.begin()-offset,k);
        set<ll>::iterator upper = positions.lower_bound(bottom+offset+k);
        int x = positions.size();
        positions.erase(positions.begin(),upper);
        offset += x - positions.size();
        ans++;
    }
    cout << ans << "\n";
}