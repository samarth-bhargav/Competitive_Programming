#include <bits/stdc++.h>
using namespace std;

#define int long long
const int mxN = 401;
int nCr[mxN][mxN], pow2[mxN], dp[mxN][mxN];

int32_t main(){
    int n, M;
    cin >> n >> M;
    memset(nCr, 0, sizeof(nCr));
    pow2[0] = 1;
    for (int i = 1; i <= n; i++){
        pow2[i] = pow2[i-1] * 2;
        pow2[i] = ((pow2[i] % M) + M) % M;
        nCr[i][0] = 1;
        nCr[i][1] = i;
    }
    for (int i = 1; i <= n; i++){
        for (int j = 2; j <= i; j++){
            nCr[i][j] = nCr[i-1][j-1] + nCr[i-1][j];
            nCr[i][j] = ((nCr[i][j]) % M + M) % M;
        }
    }
//    cerr << pow2[20] << "\n";
    //dp[i][j] represents using first i elements, having j manual, one afterward automatic
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < n; i++){
        //all manual
        dp[i][i+1] = pow2[i];
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j <= i+1; j++){
            //have first i elements, j manual, i+1 is automatic
            for (int k = 3; i+k <= n+1; k++){
                //i+2 to i+k-1 is manual, i+k is automatic, so there are k-2 additional manuals
                assert(i+k-1 <= n);
                assert(j+k-2 <= n);
//                cerr << i+k-1 << "\n";
//                cerr << j+k-2 << "\n";
                int add = (dp[i][j] * nCr[j+k-2][k-2]);
                add = ((add % M) + M) % M;
                add = add * pow2[k-3];
                add = ((add % M) + M) % M;
                dp[i+k-1][j+k-2] += add;
                dp[i+k-1][j+k-2] = ((dp[i+k-1][j+k-2] % M) + M) % M;
            }
        }
    }
    int ans = 0;
    for (int i = 0; i <= n; i++){
        ans += dp[n-1][i];
        ans = ((ans % M) + M) % M;
    }
    cout << ans << "\n";
}
