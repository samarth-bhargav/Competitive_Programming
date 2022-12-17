#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int tc; cin >> tc;
    while (tc--){
        int n;
        cin >> n; int c[2*n][2*n];
        for (int i = 0; i < 2*n; i++){
            for (int j = 0; j < 2*n; j++){
                cin >> c[i][j];
            }
        }
        ll ans = 0;
        for (int i = n; i < 2*n; i++){
            for (int j = n; j < 2*n; j++){
                ans += c[i][j];
                c[i][j] = 0;
            }
        }
        //dijkstra
        set<pair<ll,int>> pq; //cost, coord
        ll cost[4*n*n];
        ll grid_ans = 1e18;
        set<int> bc;
        bc.insert(n-1);
        bc.insert((n-1) * (2*n) + (n-1));
        bc.insert((n-1) * (2*n));
        bc.insert(0);
        //iterate through boundary cells
        for (int i : bc){
            memset(cost, 0x3f, sizeof(cost));
            // (0, i)
            cost[i] = 0;
            pq.insert({0LL, i});
            while (!pq.empty()){
                ll cst = pq.begin()->first, idx = pq.begin()->second;
                int row = idx / 2*n, col = idx % (2 * n);
                for (int j = 0; j < 4; j++){
                    int nbr_row = ((row + dx[j])%(2*n) + (2*n)) % (2*n);
                    int nbr_col = ((col + dy[j])%(2*n) + (2*n)) % (2*n);
                    if (nbr_row < n && nbr_col < n){
                        continue;
                    }
                    int nbr = nbr_row * (2*n) + nbr_col;
                    if (cst + c[nbr_row][nbr_col] < cost[nbr]){
                        pq.erase({cost[nbr], nbr});
                        cost[nbr] = cst + c[nbr_row][nbr_col];
                        pq.insert({cost[nbr], nbr});
                    }
                }
                pq.erase(pq.begin());
            }
            for (int j = n; j < 2*n; j++){
                for (int k = n; k < 2*n; k++){
                    grid_ans = min(grid_ans, cost[j*(2*n) + k]);
                }
            }
        }
        cout << ans + grid_ans << "\n";
    }
}