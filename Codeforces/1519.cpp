//babybeluga
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/
#define int ll

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--){
        int n;
        cin >> n;
        map<int,vector<int>>mp;
        for (int i = 0; i < n; i++){
            int x; cin >> x;
            mp[x].push_back(i);
        }
        vector<int>a;
        for (int i = 0; i < n; i++){
            int x; cin >> x;
            a.push_back(x);
        }
        for (auto & i : mp){
            for (auto & j : i.second){
                j = a[j];
            }
        }
        for (auto & i : mp){
            sort(i.second.rbegin(),i.second.rend());
        }
        vector<vector<int>>pref(n+1);
        for (auto & i : mp){
            pref[i.first].push_back(0);
            for (int j = 1; j <= i.second.size(); j++){
                pref[i.first].push_back(pref[i.first][j-1]+i.second[j-1]);
            }
        }
        bool bad[n+1]; memset(bad,false,sizeof(bad));
        for (int k = 1; k <= n; k++){
            int sum = 0;
            for (int i = 1; i <= n; i++){
                if (!bad[i]){
                    if (pref[i].size()==0||k>mp[i].size()){
                        bad[i] = true;
                    }
                }
            }
            for (int u = 1; u <= n; u++){
                if (bad[u]){
                    continue;
                }
                int last = mp[u].size()-mp[u].size()%k;
                sum += pref[u][last]-pref[u][0];
            }
            cout << sum << " ";
        }
        cout << "\n";
    }
}

