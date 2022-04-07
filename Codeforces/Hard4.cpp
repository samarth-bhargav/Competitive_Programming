//babybeluga
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/

bool dp[20210425],dp1[20210425];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    dp[20210301] = true;
    dp[20210423] = true;
    dp[20210424] = true;
    for (int i = 20210301; i <= 20210424; i++){
        dp1[i] = true;
    }
    for (int i = 20210300; i >= 0; i--){
        dp[i] = !(dp1[i+1] && dp1[i+123]);
        dp1[i] = !(dp[i+1] && dp[i+123]);
    }
    int t; cin >> t;
    for (int i = 0; i < t; i++){
        int x;
        cin >> x;
        cout << (dp[x]?"Yes\n":"No\n");
    }
}


