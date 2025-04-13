#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#define dbg(...) cerr << "LINE "<<__LINE__<<": -> [" << #__VA_ARGS__ << "]:", dbg_out(__VA_ARGS__)
#else
#define dbg(...) 7;
#endif

int main(){
    int t; cin >> t;
    while (t--){
        int n, m; cin >> n >> m;
        int g[n][m];

        for (int r = 0; r < n; r++){
            for (int c = 0; c < m; c++){
                cin >> g[r][c];
            }
        }

        vector<vector<int>> adj(n * m); //(r, c) -> r * m + c

        for (int c = 0; c < m; c++){
            for (int r = 0; r < n; r++){
                if (c != m-1){
                    if (g[r][c] == 0 && g[(r+1) % n][c+1] == 0){
                        adj[r * m + c].push_back(((r+1) % n) * m + c + 1);
                    }
                }
                if (g[r][c] == 0 && g[(r + 1) % n][c] == 0 && g[(r + 2) % n][c] == 0){
                    adj[r * m + c].push_back(((r + 2) % n) * m + c);
                }
            }
        }

        queue<int> q;
        vector<bool> vis(n * m, false);
        vector<int> dist(n * m, -1);

        q.push(0); vis[0] = true; dist[0] = 0;
        while (!q.empty()){
            int tp = q.front(); q.pop();
            for (int x : adj[tp]){
                if (!vis[x]){
                    dist[x] = dist[tp] + 1;
                    vis[x] = true;
                    q.push(x);
                }
            }
        }

//        dbg(dist);

        int ans = 1e9;

        for (int r = 0; r < n; r++){
            if (dist[r * m + m - 1] != -1){
                int shift = ((r - dist[r * m + m - 1]) % n + n) % n; //current position
                ans = min(ans, dist[r * m + m - 1] + ((shift + 1) % n + n) % n);
            }
        }

        if (ans == 1e9){
            cout << -1 << "\n";
            continue;
        }

        cout << ans << "\n";
    }
}