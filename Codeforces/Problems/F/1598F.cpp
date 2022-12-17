#include <bits/stdc++.h>
using namespace std;

const int mxN = 1 << 20;
int dp[mxN], ans[mxN], delta[mxN];

int main(){
    int n;
    cin >> n;
    vector<vector<int>>a(n);
    vector<int> sums(n);
    for (int i = 0; i < n; i++){
        string s; cin >> s;
        for (char c : s){
            if (c == '('){
                a[i].push_back(1);
            }
            else{
                a[i].push_back(-1);
            }
        }
        sums[i] = accumulate(a[i].begin(), a[i].end(), 0);
    }
    vector<map<int,int>> zeroes_achievable(n);
    for (int i = 0; i < n; i++){
        int min_presum = 0;
        int pre_sum = 0;
        for (int j = 0; j < a[i].size(); j++){
            pre_sum += a[i][j];
            if (pre_sum <= min_presum){
                min_presum = pre_sum;
                zeroes_achievable[i][-pre_sum]++;
            }
        }
    }
    memset(delta, 0, sizeof(delta));
    delta[0] = 0;
    for (int mask = 1; mask < (1 << n); mask++){
        for (int bit = 0; bit < n; bit++){
            if ((mask >> bit) & 1){
                delta[mask] += sums[bit];
            }
        }
    }
    memset(ans, 0, sizeof(ans));
    fill(dp, dp+mxN, -1e9);
    dp[0] = 0;
    for (int mask = 1; mask < (1 << n); mask++){
        for (int bit = 0; bit < n; bit++){
            if ((mask >> bit) & 1){
                if (zeroes_achievable[bit].find(delta[mask ^ (1 << bit)]) != zeroes_achievable[bit].end() && dp[mask ^ (1 << bit)] != -1){
                    ans[mask] = max(ans[mask], zeroes_achievable[bit][delta[mask ^ (1 << bit)]] + dp[mask ^ (1 << bit)]);
                    if (prev(zeroes_achievable[bit].end()) -> first == delta[mask ^ (1 << bit)]){
                        dp[mask] = max(dp[mask], zeroes_achievable[bit][delta[mask ^ (1 << bit)]] + dp[mask ^ (1 << bit)]);
                    }
                    else{
                        if (dp[mask] == -1e9){
                            dp[mask] = -1;
                        }
                    }
                }
                else{
                    if (zeroes_achievable[bit].empty()){
                        dp[mask] = max(dp[mask], dp[mask ^ (1 << bit)]);
                        continue;
                    }
                    if (delta[mask ^ (1 << bit)] - prev(zeroes_achievable[bit].end())->first < 0){
                        if (dp[mask ^ (1 << bit)] != -1){
                            ans[mask] = max(ans[mask], dp[mask ^ (1 << bit)] + zeroes_achievable[bit][delta[mask ^ (1 << bit)]]);
                        }
                        if (dp[mask] == -1e9){
                            dp[mask] = -1;
                        }
                    }
                    else{
                        dp[mask] = max(dp[mask], dp[mask ^ (1 << bit)]);
                    }
                }
            }
        }
    }
    cout << *max_element(ans, ans + mxN) << "\n";
}
