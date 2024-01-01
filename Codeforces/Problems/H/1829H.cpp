#include <bits/stdc++.h>

using namespace std;

#define int long long
const int M = 1e9+7;

long long binpow(int base, int exp){
    int res = 1, curr = base;
    while (exp){
        if (exp & 1){
            res *= curr; res %= M;
        }
        curr = curr * curr; curr %= M;
        exp >>= 1;
    }
    return res;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n, k; cin >> n >> k;
        vector<int> a(n);
        vector<int> occ(64, 0);
        for (int i = 0; i < n; i++){
            cin >> a[i];
            occ[a[i]]++;
        }
        vector<int> super_occ(64, 1);
        for (int mask = 0; mask < 64; mask++){
            for (int super_mask = 0; super_mask < 64; super_mask++){
                if ((super_mask & mask) == mask){
                    super_occ[mask] *= binpow(2, occ[super_mask]);
                    super_occ[mask] %= M;
                }
            }
            super_occ[mask]--;
            super_occ[mask] %= M;
        }
        vector<int> ans(64, 0); ans[63] = super_occ[63];
        for (int mask = 62; ~mask; mask--){
            ans[mask] = super_occ[mask];
            for (int super_mask = 0; super_mask < 64; super_mask++){
                if ((super_mask & mask) == mask && super_mask != mask){
                    ans[mask] -= ans[super_mask];
                    ans[mask] %= M;
                }
            }
        }
        int answer = 0;
        for (int i = 0; i < 64; i++){
            if (__builtin_popcount(i) == k){
                answer += ans[i];
                answer %= M;
            }
        }
        cout << (answer + M) % M << "\n";
    }
}