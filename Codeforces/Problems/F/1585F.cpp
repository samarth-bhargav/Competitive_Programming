#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    if (n == 1){
        cout << a[0] << "\n";
        return 0;
    }
    int dp[n][2], pref[n+1][2];
    stack<pair<int,int>> rmq; // {a, b} = {value, index}

    memset(dp, 0, sizeof(dp));
    memset(pref, 0, sizeof(pref));
    dp[0][0] = a[0];
    dp[1][1] = min(a[0], a[1]);
    pref[2][1] = dp[1][1];
    if (a[0] <= a[1]){
        rmq.push({a[0], 0});
    }
    else{
        rmq.push({a[1], 1});
    }

    for (int i = 2; i < n; i++){
        while (!rmq.empty() && rmq.top().first < a[i]){
            rmq.pop();
        }
        if (!rmq.empty()){
            int idx = rmq.top().second;
            dp[i][0] = dp[idx][1] + a[i] * (pref[i][1] - pref[idx+1][1]);
            dp[i][1] = dp[idx][0] + a[i] * (pref[i][0] - pref[idx+1][0]);
            if (rmq.top().first != a[i]){
                rmq.push({a[i], i});
            }
        }
        else{
            // a[i] is the minimum
            dp[i][0] = a[i] * pref[i][1];
            dp[i][1] = a[i] * pref[i][0];
            rmq.push({a[i], i});
        }
        pref[i+1][0] = pref[i][0] + dp[i][0];
        pref[i+1][1] = pref[i][1] + dp[i][1];
    }
    int prod = 1;
    for (int i = 0; i < n; i++){
        prod *= a[i];
    }
    cout << prod - (dp[n-1][1] - dp[n-1][0]) << "\n";
}
