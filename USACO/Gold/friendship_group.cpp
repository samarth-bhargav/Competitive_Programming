#include <bits/stdc++.h>
using namespace std;

const int mxN = 1001;
unordered_set<int> adj[mxN];

stack<int> changed;
bool visited[mxN];
unordered_set<int> nums_left;

int cnt = 0;

void dfs(int x){
    changed.push(x);
    cnt++;
    visited[x] = true;
    for (auto &nbr : adj[x]){
        if (!visited[nbr]){
            dfs(nbr);
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b; a--; b--;
        adj[a].insert(b);
        adj[b].insert(a);
    }
    for (int i = 0; i < n; i++){
        nums_left.insert(i);
    }

    int ans = -1;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i);
            ans = max(ans, cnt);
            cnt = 0;
        }
    }

    bool processed[n];
    for (int min_friends = 2; min_friends <= sqrt(2*m+1); min_friends++){
        memset(processed, 0, sizeof(processed));
        unordered_set<int> to_process;
        for (int i = 0; i < n; i++){
            if (adj[i].size() < min_friends){
                to_process.insert(i);
            }
        }
        while (!to_process.empty()){
            int tp = *to_process.begin();
            to_process.erase(tp);
            processed[tp] = true;
            for (int nbr : adj[tp]){
                adj[nbr].erase(tp);
                if (adj[nbr].size() < min_friends && !processed[nbr]){
                    to_process.insert(nbr);
                    processed[nbr] = true;
                }
            }
            nums_left.erase(tp);
        }
        int bst = -1;
        while (!changed.empty()){
            visited[changed.top()] = false;
            changed.pop();
        }
        for (int i : nums_left){
            cnt = 0;
            if (!visited[i]){
                dfs(i);
                bst = max(bst, cnt);
            }
        }
        if (min_friends * bst > ans){
            ans = min_friends * bst;
        }
    }
    cout << ans << "\n";
}
