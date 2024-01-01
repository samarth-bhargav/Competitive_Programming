#include <bits/stdc++.h>

using namespace std;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#define dbg(...) cerr << "LINE "<<__LINE__<<": -> [" << #__VA_ARGS__ << "]:", dbg_out(__VA_ARGS__)

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n, k;
        cin >> n >> k;
        vector<vector<int>> adj(n);
        vector<int> marked(k);
        for (int i = 0; i < k; i++){
            cin >> marked[i]; marked[i]--;
        }
        for (int i = 0; i < n-1; i++){
            int a, b; cin >> a >> b; a--; b--;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        vector<int> d(n);
        vector<int> p(n);
        vector<int> leaves;
        auto dfs = [&](auto self, int u, int v, int dep = 0) -> void{
            d[u] = dep;
            p[u] = v;
            if (adj[u].size() == 1 && dep != 0){
                leaves.push_back(u);
            }
            for (int child : adj[u]){
                if (child ^ v){
                    self(self, child, u, dep+1);
                }
            }
        };
        dfs(dfs, 0, -1);
        vector<array<int, 2>> sorted_dep;
        for (int i = 0; i < k; i++){
            sorted_dep.push_back({d[marked[i]], marked[i]});
        }
        sort(sorted_dep.begin(), sorted_dep.end());

//        dbg(sorted_dep);

        vector<bool> active(n, false);
        int ans = 0;

        auto mark_subtree = [&](auto self, int u, int v) -> void{
            active[u] = true;
            for (int child : adj[u]){
                if (child ^ v){
                    self(self, child, u);
                }
            }
        };

        for (int i = 0; i < k; i++){
            int dep = sorted_dep[i][0], node = sorted_dep[i][1];
            if (active[node]) continue;
            ans++;
            for (int j = 0; j < (dep >> 1); j++){
                if (active[p[node]]){
                    break;
                }
                node = p[node];
            }
            mark_subtree(mark_subtree, node, p[node]);
        }
        bool good = true;
        for (int x : leaves){
            if (!active[x]){
                good = false; break;
            }
        }
        if (!good){
            cout << "Yes" << "\n";
        }
        else{
            cout << "No" << "\n";
        }
    }
}