#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5+5;
vector <int> adj[mxN];
vector <int> timein, timeout;
int n,m,l,root, cnt = 1;
vector <vector<int>> dp;

struct node{
    int id;
    bool guersney;
    pair <int,int> cows; //cows.first = guersney, cows.second = holstein
};
node ar[mxN];
void dfs(int child, int ancestor){
    timein[child] = ++cnt;
    dp[child][0] = ancestor;
    ar[child].cows = make_pair(ar[ancestor].cows.first+ar[child].guersney, ar[ancestor].cows.second+!ar[child].guersney);
    for (int i = 1; i <= l; i++){
        dp[child][i] = dp[dp[child][i-1]][i-1];
        //2^{i-1}+2^{i-1} = 2^{i}
    }
    for (int i : adj[child]){
        if (i != ancestor){
            dfs(i, child);
        }
    }
    timeout[child] = ++cnt;
}
bool is_ancestor(int u, int v){
    return timein[u] <= timein[v] && timeout[u] >= timeout[v];
}
void preprocess(){
    l = 20;
    timein.resize(n+1);
    timeout.resize(n+1);
    dp.resize(n+1);
    for (int i = 1; i <= n; i++){
        dp[i].resize(l);
    }
}
int lca(int u, int v){
    if (is_ancestor(u,v)){
        return u;
    }
    if (is_ancestor(v,u)){
        return v;
    }
    for (int i = l; i >= 0; i--){
        if (!is_ancestor(dp[u][i],v)){
            u = dp[u][i];
        }
    }
    return dp[u][0];
}
int main() {
    freopen("milkvisits.in", "r", stdin);
    freopen("milkvisits.out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        char c;
        cin >> c;
        ar[i].guersney = (c == 'G');
        ar[i].id = i;
    }
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    ar[1].cows = make_pair(ar[1].guersney, (!ar[1].guersney));
    preprocess();
    dfs(1, 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        char c;
        cin >> a >> b >> c;
        if (a == b) {
            if (c == 'G') {
                cout << (ar[a].guersney);
                continue;
            } else {
                cout << (!ar[a].guersney);
                continue;
            }
        } else {
            if (c == 'G') {
                int lc = lca(a, b);
                if (ar[lc].cows.first == ar[a].cows.first && ar[lc].cows.first == ar[b].cows.first) {
                    if (!ar[lc].guersney) {
                        cout << 0;
                    } else {
                        cout << 1;
                    }
                } else {
                    cout << 1;
                }
            }
            if (c == 'H') {
                int lc = lca(a, b);
                if (ar[lc].cows.second == ar[a].cows.second && ar[lc].cows.second == ar[b].cows.second) {
                    if (ar[lc].guersney) {
                        cout << 0;
                    } else {
                        cout << 1;
                    }
                } else {
                    cout << 1;
                }
            }
        }
    }
    cout << "\n";
}
