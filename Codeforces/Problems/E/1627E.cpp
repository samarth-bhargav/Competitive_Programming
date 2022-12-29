#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int long long
ll INF = 1e18;

int32_t main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tc;
    cin >> tc;
    while (tc--){
        int n, m, k;
        cin >> n >> m >> k;
        unordered_map<ll, vector<pair<ll,ll>>> adj; //node, health
        vector<ll> floor_dmg(n);
        for (int i = 0; i < n; i++){
            cin >> floor_dmg[i];
        }
        vector<ll> ladders_on_floor[n];
        for (int i = 0; i < k; i++){
            int a, b, c, d, h;
            cin >> a >> b >> c >> d >> h;
            a--; b--; c--; d--;
            adj[a*m+b].push_back({c*m+d, -h});
            ladders_on_floor[a].push_back(b);
            ladders_on_floor[c].push_back(d);
        }
        for (int i = 0; i < n; i++){
            sort(ladders_on_floor[i].begin(), ladders_on_floor[i].end());
            auto last = unique(ladders_on_floor[i].begin(), ladders_on_floor[i].end());
            ladders_on_floor[i].erase(last, ladders_on_floor[i].end());
        }
        ladders_on_floor[0].push_back(0);
        ladders_on_floor[n-1].push_back(m-1);
        map<ll, ll> dp;
        for (int i = 0; i < n; i++){
            for (int j : ladders_on_floor[i]){
                dp[i * m + j] = INF;
            }
        }
        dp[0] = 0;
        for (int i = 0; i < n; i++){
            sort(ladders_on_floor[i].begin(), ladders_on_floor[i].end());
            for (int j = 1; j < ladders_on_floor[i].size(); j++){
                dp[i * m + ladders_on_floor[i][j]] = min(dp[i * m + ladders_on_floor[i][j]],
                                                         dp[i * m + ladders_on_floor[i][j-1]] + floor_dmg[i] * (ladders_on_floor[i][j] - ladders_on_floor[i][j-1]));
            }
            for (int j = ladders_on_floor[i].size()-2; j >= 0; j--){
                dp[i * m + ladders_on_floor[i][j]] = min(dp[i * m + ladders_on_floor[i][j]],
                                                         dp[i * m + ladders_on_floor[i][j+1]] + floor_dmg[i] * (ladders_on_floor[i][j+1] - ladders_on_floor[i][j]));
            }
            for (int j = 0; j < ladders_on_floor[i].size(); j++){
                if (dp[i * m + ladders_on_floor[i][j]] == INF){
                    continue;
                }
                for (auto l : adj[i * m + ladders_on_floor[i][j]]){
                    dp[l.first] = min(dp[l.first], dp[i * m + ladders_on_floor[i][j]] + l.second);
                }
            }
        }
        if (dp[(n-1) * m + m - 1] == INF){
            cout << "NO ESCAPE\n";
            continue;
        }
        cout << dp[(n-1) * m + m - 1] << "\n";
    }
}