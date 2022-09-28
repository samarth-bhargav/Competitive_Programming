#include <bits/stdc++.h>
using namespace std;

#define int long long

const int mxN = 2e5;
vector<int> adj[mxN], anc(mxN), depth(mxN);
priority_queue<int> values;

int dfs(int u, int v, int d){
    bool leaf = true;
    priority_queue<int> pile;
    for (auto & node : adj[u]){
        if (node != v){
            leaf = false;
            pile.push(dfs(node, u, d+1));
        }
    }
    if (leaf){
        return d;
    }
    int ret = pile.top();
    pile.pop();
    while (!pile.empty()){
        values.push(pile.top() - d);
        pile.pop();
    }
    return ret;
}

int32_t main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n-1; i++){
        int a, b;
        cin >> a >> b; a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    anc[0] = -1;
    values.push(dfs(0, -1, 1));
    int red = 0, blue = n, ans = -1e18;
    ans = max(ans, (n - red - n / 2) * (red - n / 2));
    while (!values.empty() && red < k){
        red++; blue -= values.top(); values.pop();
        int actual_blue = (blue > n / 2 ? n / 2 : blue);
        ans = max(ans, (n - red - actual_blue) * (red - actual_blue));
    }
    while (red < k){
        red++;
        ans = max(ans, (n - red - blue) * (red - blue));
    }
    cout << ans << "\n";
}
