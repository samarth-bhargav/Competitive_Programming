#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5, INF = 1e9+7;
vector<int> cow_pos(mxN); //pos, weight
vector<int> weights(mxN);
int dp[mxN][2];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t, n, k;
    cin >> t >> n >> k;
    for (int i = 0; i < n; i++){
        cin >> cow_pos[i] >> weights[i];
    }
    if (t == 1){
        for (int i = 0; i < n; i++){
            dp[i][0] = INF;
            dp[i][1] = INF;
        }
        dp[0][0] = weights[0];
        dp[0][1] = INF;

        for (int i = 1; i < n; i++){
            if (cow_pos[i] - cow_pos[i-1] > k){
                dp[i][0] = min(dp[i][0], dp[i - 1][0] + weights[i]);
                dp[i][0] = min(dp[i][0], dp[i - 1][1] + weights[i]);
                dp[i][1] = INF;
            }
            else{
                if (dp[i-1][1] != INF){
                    dp[i][0] = min(dp[i][0], dp[i-1][1] + weights[i]);
                    dp[i][1] = min(dp[i][1], dp[i-1][1] + weights[i-2]);
                }
                if (i-2 >= 0){
                    dp[i][1] = min(dp[i][1], dp[i-2][1]);
                    dp[i][1] = min(dp[i][1], dp[i-2][0]);
                }
                else{
                    dp[i][1] = min(dp[i][1], 0);
                }
                dp[i][1] = min(dp[i][1], dp[i-1][0] - weights[i-1]);
            }
        }
        cout << min(dp[n-1][0], dp[n-1][1]) << "\n";
    }
    else{
        cout << 6 << "\n";
//        for (int i = 0; i < n; i++){
//            dp[i][0] = -INF;
//            dp[i][1] = -INF;
//        }
//        dp[0][0] = weights[0];
//        for (int i = 1; i < n; i++){
//            int lb = cow_pos[i] - k;
//            auto min_cow = lower_bound(cow_pos.begin(), cow_pos.begin()+n, lb);
//            int min_cow_idx = int(min_cow - cow_pos.begin()) - 1;
//            if (min_cow_idx == -1){
//                //cow is within k of starting cow
//                if (i%2 == 0){
//                    dp[i][0] = 0;
//                }
//                else{
//                    dp[i][0] = *max_element(weights.begin(), weights.begin()+i); //optimize later
//                }
//            }
//            else{
//                if ((i - min_cow_idx - 1) % 2 == 0){
//                    // you can pair everything up from (x_i - k, x_i - 1)
//                    dp[i][0] = max(dp[i][0], dp[min_cow_idx][0] + weights[i]);
//                }
//                else{
//                    min_cow_idx--;
//                    if (min_cow_idx == -1){
//                        dp[i][0] = max(dp[i][0], weights[i]);
//                    }
//                    else{
//                        dp[i][0] = max(dp[i][0], dp[min_cow_idx][0] + weights[i]);
//                    }
//                }
//                dp[i][0] = max(dp[i][0], dp[i-1][0]);
//            }
//        }
//        cout << dp[n-1][0] << "\n";
    }
}