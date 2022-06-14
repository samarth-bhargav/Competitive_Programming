#include <bits/stdc++.h>
using namespace std;

const int mxN = 401;
int rmq[mxN][mxN], rsq[mxN][mxN], dp[mxN][mxN];

int main(){
    ifstream cin("snakes.in");
    ofstream cout("snakes.out");
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    for (int i = 0; i < n; i++){
        rmq[i][i] = a[i];
        rsq[i][i] = a[i];
    }
    for (int i = 0; i < n; i++){
        for (int j = i+1; j < n; j++){
            rmq[i][j] = max(rmq[i][j-1], a[j]);
            rsq[i][j] = rsq[i][j-1] + a[j];
        }
    }
    memset(dp, 0x3f, sizeof(dp));
    //dp[i][j] = optimal for splitting first i+1 elements into j groups
    for (int i = 0; i < n; i++){
        dp[i][1] = rmq[0][i] * (i+1) - rsq[0][i];
    }
    for (int i = 1; i < n; i++){
        for (int j = 2; j <= k+1; j++){
            //slider
            for (int l = 0; l < i; l++){
                //last group is from (i-l) to i
                dp[i][j] = min(dp[i][j], dp[i-l-1][j-1] + (rmq[i-l][i]*(l+1) - rsq[i-l][i]));
            }
            //take all elements
            dp[i][j] = min(dp[i][j], rmq[0][i]*(i+1) - rsq[0][i]);
        }
    }
    cout << dp[n-1][k+1] << "\n";
}
