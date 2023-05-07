#include <bits/stdc++.h>
using namespace std;

const int M = 1e9+7;
#define int long long

typedef long long ll;
const int mxF = 1100000;
int fact[mxF];

ll binpow(ll a, ll b) {
    if (b == 0) return 1;
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

    int n; cin >> n;
    int a; cin >> a;
    fact[0] = 1;
    for (int i = 1; i < mxF; i++){
        fact[i] = fact[i-1] * i;
        fact[i] = (fact[i] % M + M) % M;
    }
    int ans = 1;
    for (int i = 1; i < n; i++){
        int b; cin >> b;
        if (a < b){
            ans *= nCr(b-1, a-1);
        }
        else{
            ans *= nCr(a, b);
        }
        ans = (ans % M + M) % M;
        a = b;
    }
    cout << ans << "\n";
}
