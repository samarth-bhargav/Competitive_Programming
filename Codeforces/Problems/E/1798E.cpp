#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<int> a(n+1);
        vector<vector<int>> adj(n+1);
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        vector<int> nxt(n, -1);
        vector<bool> has_in(n, false);
        for (int i = 0; i < n; i++){
            if (i + a[i] + 1 <= n){
                nxt[i] = i + a[i] + 1;
                adj[i + a[i] + 1].push_back(i);
                has_in[i] = true;
            }
        }
        vector<pair<int, bool>> num_tests(n); //num_tests, last one incomplete
        for (int i = n-1; i >= 0; i--) {
            int next = i + a[i] + 1;
            if (next > n) {
                //out of bounds
                num_tests[i] = {1, 1};
            } else if (next == n) {
                num_tests[i] = {1, 0};
            } else {
                num_tests[i] = {num_tests[next].first + 1, num_tests[next].second};
            }
        }
        vector<int> depth(n);
        queue<pair<int,int>> bfs;
        for (int i = 0; i <= n; i++){
            if (!has_in[i]){
                bfs.push({i, 0});
//                cerr << i << endl;
            }
        }
        while (!bfs.empty()){
            pair<int,int> top = bfs.front(); bfs.pop();
            depth[top.first] = top.second;
            if (adj[top.first].empty()) continue;
            for (int neighbor : adj[top.first]){
                bfs.push({neighbor, top.second+1});
            }
        }
//        for (int i = 0; i <= n; i++){
//            cerr << depth[i] << " ";
//        }
//        cerr << endl;
        vector<int> depth_suffmax(n, -INF);
        for (int i = n-1; i >= 0; i--){
            if (i != n-1) depth_suffmax[i] = depth_suffmax[i+1];
            depth_suffmax[i] = max(depth_suffmax[i], depth[i]);
        }
        //dp[i] is largest maxsuff[nxt[ancestor]+1] - depth[ancestor]
        vector<int> dp(n+1, -1);
        dp[n] = 0;
        for (int i = n-1; i >= 0; i--){
            if (nxt[i] == -1){
                dp[i] = depth_suffmax[i+1];
                continue;
            }
            if (nxt[i] + 1 <= n){
                dp[i] = max(dp[nxt[i]], depth_suffmax[nxt[i]+1] - depth[i]);
            }
        }
        for (int i = 0; i < n; i++){
            cerr << dp[i] << " ";
        }
        cerr << endl;
        vector<int> ans(n-1);
        for (int i = 0; i < n-1; i++){
            int tests = a[i];
            if (num_tests[i+1] == make_pair(tests, false)){
                ans[i] = 0;
                continue;
            }
            else if (!num_tests[i+1].second || tests <= num_tests[i+1].first || dp[i+1] + depth[i+1] + 1 >= tests){
                ans[i] = 1;
                continue;
            }
            else{
                ans[i] = 2;
            }
        }
        for (int i = 0; i < n-1; i++) {
            cout << ans[i] << " ";
        }
        cout << "\n";
    }
}