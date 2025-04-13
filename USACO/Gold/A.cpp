#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;

    vector<vector<int>> p(n, vector<int>(n, 0));

    for (int i = 0; i < n-1; i++){
        for (int j = 0; j < n-i-1; j++){
            char c; cin >> c;
            p[i][i+j+1] = c - '0';
        }
    }

    vector<vector<int>> curr_par(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++){
        curr_par[i][i] = 1;
    }
    vector<vector<int>> adj(n);

    for (int d = 1; d < n; d++){
        for (int s = 0; s + d < n; s++){
            curr_par[s][s+d] = 0;
            for (int x : adj[s]){
                curr_par[s][s+d] ^= curr_par[x][s+d];
            }
        }
        for (int s = 0; s + d < n; s++){
            int e = s+d;
            if (p[s][e] != curr_par[s][e]){
                adj[s].push_back(e);
                curr_par[s][e] ^= 1;
            }
        }
//        for (int d1 = d; d1 < n; d1++){
//            for (int s = 0; s + d1 < n; s++){
//                curr_par[s][s+d1] = 0;
//                for (int x : adj[s]){
//                    curr_par[s][s+d1] ^= curr_par[x][s+d1];
//                }
//            }
//        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++){
        ans += adj[i].size();
    }
    cout << ans << "\n";

}