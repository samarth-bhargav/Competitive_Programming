#include <bits/stdc++.h>
using namespace std;

const int mxN = 300;
int dp[mxN][mxN];

int main(){
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 0; i < n; i++){
        dp[i][i] = 1;
    }
    int first_instance = -1, last_instance = -1;
    for (int len = 2; len <= n; len++){
        for (int i = 0; i + len <= n; i++){
            int j = i + len - 1;
            //base case
            dp[i][j] = 1 + dp[i+1][j]; //just paint[i, i+1]
            for (int k = i+1; k <= j; k++){
                if (a[i] == a[k]){
                    if (len == 2){
                        dp[i][j] = 1;
                        continue;
                    }
                    //calculate with overlapping
                    dp[i][j] = min(dp[i][j], (i+1 > k-1 ? 0 : dp[i+1][k-1]) + (k+1 > j ? 0 : dp[k+1][j]) + 1);
                    if (first_instance == -1){
                        first_instance = k;
                    }
                    else{
                        //calculate without overlapping
                        dp[i][j] = min(dp[i][j], (i+1 > first_instance - 1 ? 0 : dp[i+1][first_instance-1])
                        + dp[first_instance][last_instance] +
                                (last_instance+1 > k-1 ? 0 : dp[last_instance+1][k-1]) + (k+1 > j ? 0 : dp[k+1][j]));
                    }
                    last_instance = k;
                }
            }
            first_instance = -1;
            last_instance = -1;
        }
    }
    cout << dp[0][n-1] << "\n";
}
