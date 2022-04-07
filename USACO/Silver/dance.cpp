/*
Dont raise your voice,improve your argument
--Desmond Tutu
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
 * build directed graph after k, find cycles and make those common
*/
const int mxN = 2e5+5;

int n,k;
int ar[mxN];
vector<int>ans(mxN);
vector<pair<int,int>>swaps(mxN);
vector<set<int>>vis(mxN);
vector<int>adj[mxN];
bool visited[mxN];
vector<int>curr;

void dfs(int e, int u){
    curr.push_back(e);
    for (auto & i : vis[u]){
        vis[e].insert(i);
    }
    visited[e] = true;
    for (auto & i : adj[e]){
        if (!visited[i]){
            dfs(i,e);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= n; i++){
        ar[i] = i;
    }
    for (int i = 0; i < k; i++){
        cin >> swaps[i].first >> swaps[i].second;
    }
    for (int i =1 ; i <= n; i++){
        vis[i].insert(i);
    }
    for (int i = 0; i < k; i++){
        swap(ar[swaps[i].first],ar[swaps[i].second]);
        vis[ar[swaps[i].first]].insert(swaps[i].first);
        vis[ar[swaps[i].second]].insert(swaps[i].second);
    }
    for (int i = 1; i <= n; i++){
        adj[ar[i]].push_back(i);
    }
    for (int i = 1; i <= n; i++){
        if (!visited[i]){
            dfs(i,i);
        }
        int val = -1e9;
        for (auto & j : curr){
            val = max(val,(int)vis[j].size());
        }
        for (auto & j : curr){
            ans[j] = val;
        }
        curr.clear();
    }
    for (int i = 1; i <= n; i++){
        cout << ans[i] << "\n";
    }
}

