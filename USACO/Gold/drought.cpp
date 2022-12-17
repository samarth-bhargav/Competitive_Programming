#include <bits/stdc++.h>
using namespace std;

const int mxN = 100, mxH = 1000, M = 1000000007;
int dp[mxN][mxH+1], dp_pref[mxN][mxH+2];

int32_t main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n; vector<int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    memset(dp, 0, sizeof(dp));
    if (n%2 == 0){
        for (int i = 0; i <= a[0]; i++){
            dp[0][i] = 1;
        }
        for (int i = 1; i < n; i++){
            //for every v-j, you add dp[i-1][0], dp[i-1][1], etc.
            for (int v = 0; v <= a[i]; v++){
                for (int j = 0; j <= v; j++){
                    dp[i][v-j] = (((dp[i][v-j] + dp[i-1][j]) % M) + M) % M;
                }
            }
        }
        cout << ((dp[n-1][0] % M) + M) % M << "\n";
        cout << dp[1][1] << "\n";
    }
    else{
        int ans = 0;
        for (int iv = 0; iv <= a[0]; iv++){
            for (int i = 0; i <= a[0]; i++){
                dp[0][i] = (i < iv ? 0 : 1);
            }
            for (int i = 1; i < n; i++){
                for (int j = 0; j <= a[i]; j++){
                    dp[i][j] = 0;
                }
                for (int v = 0; v <= a[i]; v++){
                    for (int j = 0; j <= v - (i%2 == 0 ? iv : 0); j++){
                        dp[i][v-j] = ((dp[i][v-j] + dp[i-1][j]) % M + M) % M;
                    }
                }
            }
            ans = ((ans + dp[n-1][iv]) % M + M) % M;
        }
        cout << ((ans % M) + M) % M << "\n";
    }
}