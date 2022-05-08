#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll

int n, d;
const int M = 1e9+7;
const int mxN = 2000;

int accessNodes[mxN];
vector<int> adj[mxN];
set<pair<int, int>> nodes; // value, index
bool currNodes[mxN];

int dfs(int node, int p){
    int ret = 1;
    for (auto &i : adj[node]){
        if (currNodes[i] && i != p){
            ret = (ret * (1 + dfs(i, node)))%M;
        }
    }
    return ret;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> d >> n;

    for (int i = 0; i < n; i++){
        int a; cin >> a;
        accessNodes[i] = a;
        nodes.insert({a, i});
    }
    for (int i = 0; i < n-1; i++){
        int u, v;
        cin >> u >> v; u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    ll answer = 0;

    //Iterating Over Maximum Value
    for (int m = 0; m < n; m++){
        int val = accessNodes[m];
        set<pair<int, int>>::iterator it =
                lower_bound(nodes.begin(), nodes.end(), make_pair(val - d, -1LL));
        for (; it -> second != m; it++){
            currNodes[it -> second] = true;
        }
        currNodes[m] = true;
        answer = (answer + dfs(m, -1)) % M;
        for (int i = 0; i < n; i++){
            currNodes[i] = false;
        }
    }
    cout << ((answer+M)%M) << "\n";
}

