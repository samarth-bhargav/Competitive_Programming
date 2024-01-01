#include <bits/stdc++.h>

using namespace std;

#define int long long

const int mxN = 5000;
vector<int> adj[mxN];
int ans;

int dfs(int u, int p = -1){
    //returns size of subtree
    vector<int> sizes;
    for (int neighbor : adj[u]){
        if (neighbor != p){
            sizes.push_back(dfs(neighbor, u));
        }
    }
    int sm = accumulate(sizes.begin(), sizes.end(), 0LL);
    ans -= sm; //(child, parent)
    vector<bool> dp(sm+1, false);
    dp[0] = true;
    for (int i = 0; i < sizes.size(); i++){
        vector<bool> ndp = dp;
        for (int j = 0; j < dp.size(); j++){
            if (dp[j]){
                ndp[j + sizes[i]] = true;
            }
        }
        swap(ndp, dp);
    }
    for (int i = 0; i < sizes.size(); i++){
        for (int j = i+1; j < sizes.size(); j++){
            ans -= sizes[i] * sizes[j];
        }
    }
    int op = 0;
    for (int i = 0; i < dp.size(); i++){
        if (dp[i]){
            op = max(op, i * (sm - i));
        }
    }
    ans += op;
    return accumulate(sizes.begin(), sizes.end(), 0LL) + 1;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    for (int i = 1; i < n; i++){
        int x; cin >> x; x--;
        adj[i].push_back(x);
        adj[x].push_back(i);
    }
    ans = n * (n-1) / 2;
    dfs(0);
    cout << ans << "\n";
}