#include <bits/stdc++.h>

using namespace std;

#define int long long

const int mxN = 1e5, M = 998244353;
vector<array<int, 2>> adj[mxN];

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    for (int i = 0; i < n; i++){
        int k; cin >> k;
        for (int j = 0; j < k; j++){
            int a, w; cin >> a >> w; a--;
            adj[i].push_back({a, w});
        }
    }

    map<int, array<int, 3>> dp_cache;

    auto dfs = [&](auto self, int u) -> array<int, 3>{
        int zeros = 0, ones = 0, inversions = 0;
        for (array<int, 2> x : adj[u]){
            if (x[1] == 0){
                zeros++;
                zeros %= M;
                inversions += ones;
                inversions %= M;
            }
            else{
                ones++;
                ones %= M;
            }
            array<int, 3> res;
            if (dp_cache.count(x[0])){
                res = dp_cache[x[0]];
            }
            else{
                res = self(self, x[0]);
            }
            inversions += res[2];
            inversions %= M;
            inversions += ones * res[0];
            inversions %= M;
            zeros += res[0];
            zeros %= M;
            ones += res[1];
            ones %= M;
        }
        dp_cache[u] = {zeros, ones, inversions};
        return {zeros, ones, inversions};
    };
    array<int, 3> res = dfs(dfs, 0);
    cout << (res[2] % M + M) % M << "\n";
}