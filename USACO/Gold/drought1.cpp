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
        dp_pref[0][0] = 0;
        for (int i = 1; i <= a[0]+1; i++){
            dp_pref[0][i] = dp_pref[0][i-1] + dp[0][i-1];
            dp_pref[0][i] %= M;
        }
        for (int i = 1; i < n; i++){
            //for every v-j, you add dp[i-1][0], dp[i-1][1], etc. up till dp[i-1][v]
            for (int v = 0; v <= a[i]; v++){
                dp[i][v] = dp_pref[i-1][min(a[i-1]+1, a[i]-v+1)];
            }
            dp_pref[i][0] = 0;
            for (int v = 1; v <= a[i]+1; v++){
                dp_pref[i][v] = dp_pref[i][v-1] + dp[i][v-1];
                dp_pref[i][v] %= M;
            }
        }
        cout << ((dp[n-1][0] % M) + M) % M << "\n";
    }
    else{
        int ans = 0;
        for (int iv = 0; iv <= a[0]; iv++){
            for (int i = 0; i <= a[0]; i++){
                dp[0][i] = (i < iv ? 0 : 1);
            }
            dp_pref[0][0] = 0;
            for (int i = 1; i <= a[0]+1; i++){
                dp_pref[0][i] = dp_pref[0][i-1] + dp[0][i-1];
                dp_pref[0][i] %= M;
            }
            for (int i = 1; i < n; i++){
                for (int j = 0; j <= a[i]+1; j++){
                    dp[i][j] = 0;
                }
                for (int v = 0; v <= a[i]; v++){
                    if (i%2 == 0){
                        if (v < iv){
                            dp[i][v] = 0;
                        }
                        else{
                            dp[i][v] = dp_pref[i-1][min(a[i-1]+1, a[i]-v+1)];
                        }
                    }
                    else{
                        dp[i][v] = dp_pref[i-1][min(a[i-1]+1, a[i]-v+1)];
                    }
                }
                dp_pref[i][0] = 0;
                for (int v = 1; v <= a[i]+1; v++){
                    dp_pref[i][v] = dp_pref[i][v-1] + dp[i][v-1];
                    dp_pref[i][v] %= M;
                }
            }
            ans = ((ans + dp[n-1][iv]) % M + M) % M;
        }
        cout << ((ans % M) + M) % M << "\n";
    }
}

