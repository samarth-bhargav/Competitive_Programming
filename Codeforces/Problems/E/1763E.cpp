#include <bits/stdc++.h>
using namespace std;

const int mxN = 2e5+1;
const int mxK = 650;
int dp[mxN], prod[mxN], nc2[mxK];

int main(){
    int p; cin >> p;
    for (int i = 2; i < mxK; i++){
        nc2[i] = (i * (i - 1)) / 2;
    }
    memset(prod, -1, sizeof(prod));
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0; prod[0] = 0;
    for (int i = 1; i <= p; i++){
        for (int k = 2; nc2[k] <= i; k++){
            if (dp[i] > dp[i - nc2[k]] + k){
                dp[i] = dp[i - nc2[k]] + k;
                prod[i] = prod[i - nc2[k]] + dp[i - nc2[k]] * k;
            }
            else if (dp[i] == dp[i - nc2[k]] + k){
                prod[i] = max(prod[i], prod[i - nc2[k]] + dp[i - nc2[k]] * k);
            }
        }
    }
    cout << dp[p] << " " << prod[p] << "\n";
}
