#include <bits/stdc++.h>

using namespace std;

#define dbg(x) cout << #x << ": " << x << "\n";

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m; cin >> n >> m;
    vector<int> a(n), c(m);
    for (int i = 0; i < n; i++){
        cin >> a[i]; a[i]--;
    }
    for (int i = 0; i < m; i++){
        cin >> c[i];
    }
    if (m == 1){
        cout << c[0] << "\n";
        return 0;
    }
    set<int> already_resolved;
    already_resolved.insert(a[0]);
    already_resolved.insert(a[n-1]);
    for (int i = 1; i < n-1; i++){
        if (a[i] == a[i+1]){
            already_resolved.insert(a[i]);
        }
    }
    vector<unordered_set<int>> adj(m);
    for (int i = 1; i < n-1; i++){
        if (already_resolved.count(a[i]) || already_resolved.count(a[i+1])){
            continue;
        }
        adj[a[i]].insert(a[i+1]);
        adj[a[i+1]].insert(a[i]);
    }
    vector<int> first_part, second_part;
    int first_part_full_msk = 0;
    for (int i = 0; i < m / 2; i++){
        first_part.push_back(i);
        first_part_full_msk ^= (1 << i);
    }
    for (int i = m / 2; i < m; i++){
        second_part.push_back(i);
    }
    int dp[1 << (first_part.size())];
    //dp[msk] is the minimum weighted vertex cover of msk
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;
    for (int msk = 1; msk < (1 << (first_part.size())); msk++){
        unordered_set<int> part; //current mask's elements
        for (int b = 0; b < first_part.size(); b++){
            if ((msk >> b) & 1){
                part.insert(b);
                assert(first_part[b] == b);
            }
        }
        int origin = *part.begin();
        vector<int> vt_to_upd;
        int to_upd = 0;
        for (int x : adj[origin]){
            if (part.contains(x)){
                vt_to_upd.push_back(x);
                to_upd ^= (1 << x);
            }
        }
        int rest = msk ^ (1 << origin);
        for (int msk1 = 0; msk1 < 2; msk1++){
            int sum = 0;
            if (msk1 == 0){
                for (int x : vt_to_upd){
                    sum += c[x];
                }
                sum += dp[rest ^ to_upd];
                dp[msk] = min(dp[msk], sum);
            }
            else{
                sum += c[origin];
                sum += dp[rest];
                dp[msk] = min(dp[msk], sum);
            }
        }
//        dbg(msk);
//        dbg(dp[msk]);
//        cout << "\n";
    }
    //now take all possible vertex covers of the second part
    vector<array<int, 2>> second_part_edges;
    for (int i = 0; i < second_part.size(); i++){
        for (int j = i+1; j < second_part.size(); j++){
            if (adj[second_part[i]].contains(second_part[j])){
                second_part_edges.push_back({i, j});
            }
        }
    }
    int ans = 0;
    for (int x : already_resolved){
        ans += c[x];
    }
    int c_ans = 1e9;
    for (int msk = 0; msk < (1 << (second_part.size())); msk++){
        bool good = true;
        for (array<int, 2> edge : second_part_edges){
            if (((msk >> edge[0]) & 1) | ((msk >> edge[1]) & 1)){}
            else{
                good = false;
                break;
            }
        }
        if (!good) continue;
        int sum = 0;
        int first_part_msk = 0; //if smth from the first part must be 1
        for (int b = 0; b < second_part.size(); b++){
            if ((msk >> b) & 1){
                sum += c[second_part[b]];
            }
            else{
                for (int x : adj[second_part[b]]){
                    if (x < m / 2){
                        if (~(first_part_msk >> x) & 1){
                            first_part_msk ^= (1 << x);
                            sum += c[x];
                        }
                    }
                }
            }
        }
        sum += dp[first_part_full_msk ^ first_part_msk];
        c_ans = min(c_ans, sum);
//        if (c_ans == 9){
//            dbg(msk);
//        }
    }
    cout << ans + c_ans << "\n";
}