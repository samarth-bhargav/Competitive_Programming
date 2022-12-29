#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e18;

int32_t main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    while (T--){
        int n, m;
        cin >> n >> m;
        vector<int> times(n);
        for (int i = 0; i < n; i++){
            cin >> times[i];
        }
        assert(is_sorted(times.begin(), times.end()));
        vector<vector<array<int, 3>>> options(n);
        for (int i = 0; i < m; i++){
            int e, t, p;
            cin >> e >> t >> p; e--;
            options[e].push_back({t, p, i+1});
        }
        vector<int> min_times(n);
        vector<vector<int>> constructions(n);
        for (int i = 0; i < n; i++){
            pair<int, vector<int>> dp[201];
            dp[0] = {0, {}};
            for (int j = 1; j <= 200; j++){
                dp[j] = {INF, {}};
            }
            for (int j = 0; j < options[i].size(); j++){
                deque<int> updates;
                for (int k = 0; k < 100; k++){
                    if (dp[k+options[i][j][1]].first > dp[k].first + options[i][j][0]){
                        updates.push_front(k);
                    }
                }
                for (int k : updates){
                    dp[k+options[i][j][1]].first = dp[k].first + options[i][j][0];
                    dp[k+options[i][j][1]].second = dp[k].second;
                    dp[k+options[i][j][1]].second.push_back(options[i][j][2]);
                }
            }
            int pmt = 100;
            for (int p = 101; p <= 200; p++){
                if (dp[p].first < dp[pmt].first){
                    pmt = p;
                }
            }
            min_times[i] = dp[pmt].first;
            constructions[i] = dp[pmt].second;
        }
        //check if possible
        int pref_min_times[n+1];
        pref_min_times[0] = 0;
        for (int i = 1; i <= n; i++){
            pref_min_times[i] = pref_min_times[i-1] + min_times[i-1];
        }
        bool bad = false;
        for (int i = 0; i < n; i++){
            if (pref_min_times[i+1] > times[i]){
                cout << "-1\n";
                bad = true;
                break;
            }
        }
        if (bad){
            continue;
        }
        vector<int> final_sol;
        for (int i = 0; i < n; i++){
            for (int j : constructions[i]){
                final_sol.push_back(j);
            }
        }
        cout << final_sol.size() << "\n";
        for (int x : final_sol){
            cout << x << " ";
        }
        cout << "\n";
    }
}
