#include <bits/stdc++.h>
using namespace std;

const int M = 998244353;

int main(){
    int n, m;
    cin >> n >> m;
    array<int, 2> ranges[n];
    for (int i = 0; i < n; i++){
        cin >> ranges[i][0] >> ranges[i][1];
    }
    vector<vector<vector<int>>> dp(2, vector<vector<int>> (m+1));
    vector<vector<vector<int>>> pref(2, vector<vector<int>> (m+1));
    for (int i = 0; i < 2; i++){
        for (int j = 1; j <= m; j++){
            dp[i][j] = vector<int> (m / j + 1, 0);
            pref[i][j] = vector<int> (m / j + 2, 0);
        }
    }
    // dp[i][j][k] denotes first i elements, sum equal to j*k, gcd is a MULTIPLE of j
    for (int mul = 1; mul <= m; mul++){
        for (int mul1 = (ranges[0][0] + mul - 1) / mul; mul1 <= ranges[0][1] / mul; mul1++){
            dp[0][mul][mul1] = 1;
        }
        pref[0][mul][0] = 0;
        for (int s = 1; s <= m / mul; s++){
            pref[0][mul][s] = ((pref[0][mul][s-1] + dp[0][mul][s-1]) % M + M) % M;
        }
    }

    for (int i = 1; i < n; i++){
        for (int mul = 1; mul <= m; mul++){
            for (int k = 0; k <= m / mul; k++){
                int mul1 = (ranges[i][0] + mul - 1) / mul;
                if (k-mul1 < 0){
                    continue;
                }
                int mul2 = min(ranges[i][1] / mul, k);
                //for every element dp[i][j][k], add dp[i-1][j][k-mul1], dp[i-1][j][k-mul1-1], ..., all the way up to dp[i-1][j][k-mul2]
                assert(k-mul1+1 >= 0);
                assert(k-mul2 >= 0);
                assert(k-mul1+1 >= k-mul2);

                dp[1][mul][k] = ((pref[0][mul][k-mul1+1] - pref[0][mul][k-mul2]) % M + M) % M;
//                cout << " i: " << i << " mul: " << mul << " sum: " << k << " dp[i][mul][sum]: " << dp[i][mul][k] << "\n";
            }
            pref[1][mul][0] = 0;
            for (int s = 1; s <= m / mul; s++){
                pref[1][mul][s] = ((pref[1][mul][s-1] + dp[1][mul][s-1]) % M + M) % M;
            }
        }
        for (int mul = 1; mul <= m; mul++){
            for (int k = 0; k <= m / mul; k++){
                pref[0][mul][k] = pref[1][mul][k];
                pref[1][mul][k] = 0;
                dp[0][mul][k] = dp[1][mul][k];
                dp[1][mul][k] = 0;
            }
            pref[0][mul][m / mul + 1] = pref[1][mul][m / mul + 1];
            pref[1][mul][m / mul + 1] = 0;
        }
    }

    int dp1[m+1];
    memset(dp1, 0, sizeof(dp1));
    for (int j = 1; j <= m; j++){
        for (int k = 0; k <= m / j; k++){
            dp1[j] = ((dp1[j] + dp[0][j][k]) % M + M) % M;
        }
    }
//    cout << dp1[1] << " " << dp1[2] << " " << dp1[3] << " " << dp1[4] << "\n";
    for (int mul = m; mul >= 1; mul--) {
        for (int mul1 = 2; mul1 <= m / mul; mul1++) {
            dp1[mul] = ((dp1[mul] - dp1[mul*mul1]) % M + M) % M;
        }
    }
    cout << dp1[1] << "\n";
}
