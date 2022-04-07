/*
Dont raise your voice,improve your argument
--Desmond Tutu
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;


#define int ll

const int M = 1e9+7;
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    int fac[200005]; fac[0] = 1;
    for (int i = 1; i <= 200000; i++){
        fac[i] = (fac[i-1]*i)%M;
    }
    while (t--){
        int n;
        cin >> n;
        vector<int>a(n);
        map<int,int>mp;
        for (int i = 0; i < n; i++){
            cin >> a[i];
            mp[a[i]]++;
        }
        int ans = 0;
        for (auto & i : mp){
            if (i.second >= 2){
                ans += ((i.second*(i.second-1)) * fac[n-2])%M;
            }
        }
        cout << ans << "\n";
    }
}

