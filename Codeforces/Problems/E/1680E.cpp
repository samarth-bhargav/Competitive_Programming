#include <bits/stdc++.h>
using namespace std;

const int mxN = 2e5;
int dp[mxN][2], g[mxN][2];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--){
        int n; cin >> n;
        for (int r = 0; r < 2; r++){
            for (int c = 0; c < n; c++){
                char x; cin >> x;
                g[c][r] = (x == '*' ? 1 : 0);
            }
        }
        int start_col = -1;
        for (int c = 0; c < n; c++){
            if (g[c][0] || g[c][1]){
                if (g[c][0] ^ g[c][1]){
                    dp[c][0] = (g[c][0] ? 0 : 1);
                    dp[c][1] = (g[c][1] ? 0 : 1);
                }
                else{
                    dp[c][0] = 1;
                    dp[c][1] = 1;
                }
                start_col = c+1;
                break;
            }
        }
        int end_col = start_col-1;
        for (int c = start_col; c < n; c++){
            if (g[c][0] || g[c][1]){
                if (g[c][0] ^ g[c][1]){
                    if (g[c][0]){
                        dp[c][0] = min(dp[c-1][0]+1, dp[c-1][1]+2);
                        dp[c][1] = min(dp[c-1][0]+2, dp[c-1][1]+2);
                    }
                    else{
                        dp[c][0] = min(dp[c-1][0]+2, dp[c-1][1]+2);
                        dp[c][1] = min(dp[c-1][0]+2, dp[c-1][1]+1);
                    }
                }
                else{
                    dp[c][0] = min(dp[c-1][0]+2, dp[c-1][1]+2);
                    dp[c][1] = min(dp[c-1][0]+2, dp[c-1][1]+2);
                }
                end_col = c;
            }
            else{
                dp[c][0] = min(dp[c-1][0]+1, dp[c-1][1]+2);
                dp[c][1] = min(dp[c-1][1]+1, dp[c-1][0]+2);
            }
        }
        cout << min(dp[end_col][0], dp[end_col][1]) << "\n";
    }
}
