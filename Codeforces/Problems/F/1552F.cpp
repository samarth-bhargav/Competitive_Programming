#include <bits/stdc++.h>
using namespace std;

#define int long long
const int M = 998244353;

int32_t main(){
    int n;
    cin >> n;
    vector<array<int, 3>> portals(n);

    for (int i = 0; i < n; i++){
        cin >> portals[i][0] >> portals[i][1] >> portals[i][2];
    }

    int dp[n], dp1[n], pref[n+1];
    dp[0] = (portals[0][2] ? portals[0][0] + (portals[0][0] - portals[0][1] + 1) : portals[0][0] + 1);
    dp[0] = ((dp[0]) % M + M) % M;
    dp1[0] = portals[0][0] - portals[0][1] + 1;
    dp1[0] = ((dp1[0]) % M + M) % M;
    pref[0] = 0;
    pref[1] = dp1[0]+portals[1][0]-portals[0][0]-1;

    for (int i = 1; i < n; i++){
        array<int, 3> lb_ar = {portals[i][1], -1, -1};
        int np = lower_bound(portals.begin(), portals.end(), lb_ar) - portals.begin();
        if (np == i){
            dp1[i] = portals[i][0] - portals[i][1] + 1;
        }
        else{
            //pref[i] - pref[np] should represent
            //dp1[np] + dist(x_np+1, x_{np+1}) + dp1[np+1] + dist(x_{np+1}+1, x_{np+2}) + ... + dp1[i-1] + dist(x_{i-1}+1, x_i)
            //(dp1[0]+dist(4,6)+dp1[1]+dist(7,7)) - (dp1[0]+dist(4,6)) = dp1[1]+dist(7,7)
            dp1[i] = (portals[np][0] - portals[i][1]) + (pref[i] - pref[np]) + 1;
        }
        dp1[i] = ((dp1[i] % M) + M) % M;
        if (portals[i][2]){
            //portal is active
            dp[i] = dp[i-1] + portals[i][0] - portals[i-1][0] - 1 + dp1[i];
        }
        else{
            dp[i] = dp[i-1] + portals[i][0] - portals[i-1][0];
        }
        dp[i] = ((dp[i] % M) + M) % M;
        if (i < n-1){
            pref[i+1] = pref[i] + dp1[i] + portals[i+1][0] - portals[i][0] - 1;
        }
        pref[i+1] = ((pref[i+1] % M) + M) % M;
//        cout << "i: " << i << " dp[i]: " << dp[i] << " dp1[i]: " << dp1[i] << "\n";
    }

    cout << dp[n-1] << "\n";
}
