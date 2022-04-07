/*
Dont raise your voice,improve your argument
--Desmond Tutu
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define all(x) x.begin(),x.end()

/*
*/

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int>a(n+1);
    for (int i = 1;i <= n; i++){
        cin >> a[i];
    }
    map<int,vector<ll>>mp;
    for (int i = 1; i <= n; i++){
        mp[a[i]].push_back(i);
    }
    ll dp[n+1]; memset(dp,0,sizeof(dp));
    for (int i = 2; i <= n; i++){
        if (mp[a[i]][0] == i){
            dp[i] = dp[i-1];
        }
        else{
            dp[i] = max(dp[i-1],*prev(lower_bound(all(mp[a[i]]),i)));
        }
    }
    ll dp1[n+1]; dp1[1] = 0LL;
    for (int i = 2; i <= n; i++){
        dp1[i] = dp1[i-1]+(i-dp[i])-1;
    }
    for (int i = 1; i <= n; i++){
        cerr << dp1[i] << " ";
    }
    cerr << "\n";
//    cout << dp1[n] << "\n";
}

