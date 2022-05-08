//babybeluga
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
 * First determine the least cost to transform index i into the letter j (floyd warshall)
 * Then prefix sums this
 * dp array where dp[i][j] represents last k letters of i-letter string as j
 * dpmin array where dpmin[i] represents the min cost to make valid first i letters
 * dp[i][j] = min(prefix[i][j]-prefix[i-k][j]+dpmin[i-k],dp[i-1][j] + cst[i][j])
*/

const int mxN = 100005;
const int mxM = 26;

ll dp[mxN][mxM];
ll dpmin[mxN];
ll cost[mxM][mxM];
ll cst[mxN][mxM];
ll prf[mxN][mxM];
int n,m,k;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
//    freopen("cowmbat.in","r",stdin);
//    freopen("cowmbat.out","w",stdout);
    cin >> n >> m >> k;
    string s; cin >> s;
    for (int i = 0; i < m; i++){
        for (int j = 0; j < m; j++){
            cin >> cost[i][j];
        }
    }
    int ar[n];
    for (int i = 0; i < n; i++){
        ar[i] = s[i] - 'a';
    }
    memset(prf,0,sizeof(prf));
    memset(dp,0x3f,sizeof(dp));
    memset(dpmin,0x3f,sizeof(dpmin));
    //floyd warshall
    for (int i = 0; i < m; i++){
        //changing pivot
        for (int j = 0; j < m; j++){
            for (int p = 0; p < m; p++){
                cost[j][p] = min(cost[j][p],cost[j][i]+cost[i][p]);
            }
        }
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            cst[i][j] = cost[ar[i]][j];
        }
    }
    //prefix sums
    for (int i = 0; i < m; i++){
        prf[0][i] = cst[0][i];
        for (int j = 1; j < n; j++){
            prf[j][i] = prf[j-1][i] + cst[j][i];
        }
    }
    for (int i = 0; i < m; i++) {
        dp[0][i] = cst[0][i];
        dpmin[0] = min(dpmin[0],dp[0][i]);
    }
    //updating dp values
    for (int i = 1; i < n; i++){
        for (int j = 0; j < m; j++){
            if (i-k >= 0){
                dp[i][j] = min(dp[i][j],prf[i][j]-prf[i-k][j]+dpmin[i-k]);
            }
            dp[i][j] = min(dp[i][j],dp[i-1][j]+cst[i][j]);
            dpmin[i] = min(dpmin[i],dp[i][j]);
        }
    }
    cout << dpmin[n-1] << "\n";
}

