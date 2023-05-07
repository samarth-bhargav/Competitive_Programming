#include <bits/stdc++.h>
using namespace std;

const int mxN = 2e5;
vector<int> adj[mxN];
vector<int> children[mxN];
vector<bool> black(mxN);
vector<int> occ(mxN);
int dp[mxN];

bool dfs(int u, int v){
    for (int node : adj[u]){
        if (node != v){
            if (!dfs(node, u)){
                return false;
            }
            children[u].push_back(node);
        }
    }
    if (children[u].empty()){
        //base case
        if (black[u]){
            dp[u] = -occ[u];
            return true;
        }
        else{
            dp[u] = 1;
            return true;
        }
    }
    vector<int> cvals;
    for (int child : children[u]){
        cvals.push_back(dp[child]);
    }
    sort(cvals.begin(), cvals.end());
    if (black[u]){
        if (cvals[0] < 0) return false;
        if (cvals.back() >= occ[u]){
            dp[u] = 0; return true;
        }
        else{
            dp[u] = -occ[u]; return true;
        }
    }
    else{
        if (cvals[0] < 0){
            if (cvals.size() > 1 && cvals[1] < 0){
                return false;
            }
            int largest = cvals.back();
            if (-cvals[0] <= largest + 1){
                dp[u] = 0; return true;
            }
            else{
                dp[u] = cvals[0] + 1; return true;
            }
        }
        else{
            dp[u] = cvals.back() + 1; return true;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        for (int i = 0; i < n-1; i++){
            int a, b;
            cin >> a >> b; a--; b--;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        int k; cin >> k;
        vector<int> tokens;
        for (int i = 0; i < k; i++){
            int x; cin >> x;
            black[x-1] = true;
            tokens.push_back(x-1);
        }
        int lo = 0, hi = n;
        while (lo < hi){
            int mid = (lo + hi + 1) / 2;
            for (int i = 0; i < k; i++){
                occ[tokens[i]] = (mid / k + (mid % k > i));
            }
            if (!dfs(0, -1) || dp[0] < 0){
                hi = mid-1;
            }
            else{
                lo = mid;
            }
            for (int i = 0; i < n; i++){
                children[i].clear(); children[i].shrink_to_fit();
            }
        }
        cout << lo << "\n";
        for (int i = 0; i < n; i++){
            adj[i].clear(); adj[i].shrink_to_fit();
            black[i] = false;
        }
    }
}