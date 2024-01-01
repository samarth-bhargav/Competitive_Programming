#include <bits/stdc++.h>

using namespace std;

struct card{
    int idx, a, d;
    card(){}
    card(int idx, int a, int d){
        this->idx = idx;
        this->a = a;
        this->d = d;
    }
};

const int INF = 1e9;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<card> monocarp(n);
        for (int i = 0; i < n; i++){
            monocarp[i].idx = i;
            cin >> monocarp[i].a;
        }
        for (int i = 0; i < n; i++){
            cin >> monocarp[i].d;
        }
        int m; cin >> m;
        vector<card> bicarp(m);
        for (int i = 0; i < m; i++){
            bicarp[i].idx = n + i;
            cin >> bicarp[i].a;
        }
        for (int i = 0; i < m; i++){
            cin >> bicarp[i].d;
        }
        vector<card> monocarp_d = monocarp;
        vector<card> bicarp_d = bicarp;

        sort(monocarp.begin(), monocarp.end(), [&](card x, card y){
            return x.a < y.a;
        });
        sort(bicarp.begin(), bicarp.end(), [&](card x, card y){
            return x.a < y.a;
        });
        sort(monocarp_d.begin(), monocarp_d.end(), [&](card x, card y){
            return x.d < y.d;
        });
        sort(bicarp_d.begin(), bicarp_d.end(), [&](card x, card y){
            return x.d < y.d;
        });

        vector<int> highest_monocarp_d(m); //highest monocarp defense idx such that attack is greater than bicarp_d[i]
        vector<int> highest_bicarp_d(n); //highest bicarp defense idx such that attack is greater than monocarp_d[i]

        int curr_mono = n-1;
        card curr_best = card(-1, -INF, -INF);

        for (int i = m-1; i >= 0; i--){
            while (curr_mono >= 0 && monocarp[curr_mono].a > bicarp_d[i].d){
                if (monocarp[curr_mono].d > curr_best.d){
                    curr_best = monocarp[curr_mono];
                }
                curr_mono--;
            }
            highest_monocarp_d[i] = curr_best.idx;
        }

        curr_best = card(-1, -INF, -INF);

        int curr_bi = m-1;
        for (int i = n-1; i >= 0; i--){
            while (curr_bi >= 0 && bicarp[curr_bi].a > monocarp_d[i].d){
                if (bicarp[curr_bi].d > curr_best.d){
                    curr_best = bicarp[curr_bi];
                }
                curr_bi--;
            }
            highest_bicarp_d[i] = curr_best.idx;
        }
        vector<vector<int>> adj(n+m);
        for (int i = 0; i < n; i++){
            if (highest_bicarp_d[i] != -1){
                adj[monocarp_d[i].idx].push_back(highest_bicarp_d[i]);
            }
        }
        for (int i = 0; i < m; i++){
            if (highest_monocarp_d[i] != -1){
                adj[bicarp_d[i].idx].push_back(highest_monocarp_d[i]);
            }
        }

        vector<bool> active(n+m, false);
        vector<int> dp(n+m, -INF);

        //0 denotes monocarp, 1 denotes cycle, 2 denotes bicarp

        auto dfs = [&](auto self, int u) -> void{
            if (active[u]){
                dp[u] = 1; return;
            }
            active[u] = true;
            if (adj[u].empty()){
                dp[u] = (u >= n ? 2 : 0);
            }
            else{
                if (dp[adj[u][0]] == -INF){
                    self(self, adj[u][0]);
                }
                dp[u] = dp[adj[u][0]];
            }
            active[u] = false;
        };

        for (int i = 0; i < n+m; i++){
            dfs(dfs, i);
        }

        array<int, 3> ans = {0, 0, 0};

        for (int i = 0; i < n; i++){
            ans[dp[i]]++;
        }
        cout << ans[0] << " " << ans[1] << " " << ans[2] << "\n";
    }
}