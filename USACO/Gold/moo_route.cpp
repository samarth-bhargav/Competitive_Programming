#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int M = 1e9+7;
const int mxF = 1100000;
int fact[mxF];

ll binpow(ll a, ll b) {
    a %= M;
    ll ret = 1;
    while (b > 0) {
        if (b % 2 == 1)
            ret = (ret * a) % M;
        a = (a * a) % M;
        b /= 2;
    }
    return (ret % M + M) % M;
}

ll nCr(ll a, ll b){
    ll ret = fact[a];
    ret *= binpow(fact[b], M-2);
    ret = ((ret % M) + M) % M;
    ret *= binpow(fact[a - b], M-2);
    ret = ((ret % M) + M) % M;
    return ret;
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    fact[0] = 1;
    for (int i = 1; i < mxF; i++){
        fact[i] = fact[i-1] * i;
        fact[i] = (fact[i] % M + M) % M;
    }
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
//    if (n == 2 && a[0] > a[1]){
//        assert(false);
//    }
    int ans = 1;
    int min_elem = *(min_element(a.begin(), a.end()));
    for (int i = 0; i < n; i++){
        ll y = (a[i] - min_elem) / 2;
        ll x;
        if (i == 0 || i == n-1){
            x = min_elem / 2 + (i == 0);
        }
        else{
            x = min_elem;
        }
        ans *= nCr(y + x - 1, x - 1);
        ans = (ans % M + M) % M;
    }
    cout << ans << "\n";
}
