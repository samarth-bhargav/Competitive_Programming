#include <bits/stdc++.h>

using namespace std;

const int mxN = 5001;
bitset<mxN> precedable[mxN];
vector<int> adj[mxN], rev_adj[mxN];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int m, n; cin >> m >> n;
    vector<int> prices(n);
    for (int i = 0; i < n; i++){
        cin >> prices[i];
    }
    vector<vector<pair<int, int>>> ratings(m, vector<pair<int, int>>(n));
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            int rating; cin >> rating;
            ratings[i][j] = {rating, j};
        }
    }
    for (int i = 0; i < n; i++){
        precedable[i].set();
    }
    for (int i = 0; i < m; i++){
        sort(ratings[i].begin(), ratings[i].end());
        bitset<mxN> p_able; p_able.set();
        int first_neq_idx = 0;
        for (int j = 0; j < n; j++){
            while (first_neq_idx < n && ratings[i][first_neq_idx].first == ratings[i][j].first){
                p_able.set(ratings[i][first_neq_idx].second, 0);
                first_neq_idx++;
            }
            precedable[ratings[i][j].second] &= p_able;
        }
    }
    for (int i = 0; i < n; i++){
        for (int b = 0; b < n; b++){
            if (b != i && precedable[i].test(b)){
                adj[i].push_back(b);
                rev_adj[b].push_back(i);
            }
        }
    }
    vector<int> top_sort;
    vector<int> in_deg(n);
    queue<int> indeg_0;
    for (int i = 0; i < n; i++){
        if (rev_adj[i].empty()){
            indeg_0.push(i);
        }
        in_deg[i] = rev_adj[i].size();
    }
    while (!indeg_0.empty()){
        int top = indeg_0.front();
        indeg_0.pop();
        top_sort.push_back(top);
        for (int model : adj[top]){
            in_deg[model]--;
            if (in_deg[model] == 0){
                indeg_0.push(model);
            }
        }
    }
    vector<long long> dp(n, 0);
    for (int i = 0; i < top_sort.size(); i++){
        dp[top_sort[i]] = prices[top_sort[i]];
        for (int precede : rev_adj[top_sort[i]]){
            dp[top_sort[i]] = max(dp[top_sort[i]], (long long)(dp[precede] + prices[top_sort[i]]));
        }
    }
    cout << *max_element(dp.begin(), dp.end()) << "\n";
}