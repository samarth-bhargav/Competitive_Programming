#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e4;
const int mxA = 2e3+1;
const int INF = 1e9;
int dp[mxN][mxA];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int tc; cin >> tc;
    while (tc--){
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        for (int i = 0; i < n; i++){
            for (int j = 0; j <= 2000; j++){
                dp[i][j] = INF;
            }
        }
        //base cases
        for (int i = 0; i < a[n-1]; i++){
            dp[n-1][i] = a[n-1];
        }
        for (int i = a[n-1]; i <= 2000; i++){
            dp[n-1][i] = i - a[n-1];
        }
        //actual dp
        for (int i = n-2; i >= 0; i--){
            for (int j = 0; j <= 2000; j++){
                if (j + a[i] <= 2000){
                    dp[i][j] = dp[i+1][j+a[i]] + a[i];
                }
                if (j >= a[i]){
                    //we can go backward
                    dp[i][j] = min(dp[i][j], max(dp[i+1][j-a[i]] - a[i], 0));
                }
            }
            //do suffix min
            int min_val = INF;
            for (int j = 0; j <= 2000; j++){
                if (dp[i][j] < min_val){
                    min_val = dp[i][j];
                }
                else{
                    dp[i][j] = min_val;
                }
            }
        }
        //compute answer
        int ans = INF;
        for (int i = 0; i <= 2000; i++){
            ans = min(ans, i + dp[0][i]);
        }
        cout << ans << "\n";
    }
}