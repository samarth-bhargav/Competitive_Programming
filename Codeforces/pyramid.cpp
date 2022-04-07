/*
Dont raise your voice,improve your argument
--Desmond Tutu
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/
bool ok(ll x, ll n, ll m){
    ll blocks = 0;
    ll lim = (n+x-1)/x;
    blocks += x*(lim*(lim-1))/2;
    if (x == 1){
        blocks += lim;
    }
    else{
        blocks += (n-((lim-1)*x))*(lim);
    }
    return blocks <= m;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--){
        ll n,m;
        cin >> n >> m;
        if (n > m|| m > (n*(n+1))/2){
            cout << -1 << "\n";
            continue;
        }
        ll lo = 1; ll hi = n;
        while (hi-lo>1){
            ll mid = lo+(hi-lo)/2;
            if (ok(mid,n,m)){
                hi = mid;
            }
            else{
                lo = mid+1;
            }
        }
        cout << (ok(lo,n,m)?lo:hi) << "\n";
    }
}

