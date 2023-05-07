#include <bits/stdc++.h>
using namespace std;

const int mxN = 2e5;
vector<int> adj[mxN], num_children(mxN, 0);
vector<bool> n_ref(mxN, false);

int ans = 0;

bool dfs(int u, int v){
    vector<int> children;
    int res_true = 0;
    for (int nbr : adj[u]){
        if (nbr != v){
            res_true += dfs(nbr, u);
            num_children[u]++;
            children.push_back(nbr);
        }
    }
    if (children.size() == 0) return false; //you dont auto activate leaf nodes
    if (children.size() > 2){
        if (res_true == children.size()){
            n_ref[u] = true;
        }
        //do n-1 strat
        ans += (max(int(children.size() - 1) - res_true, 0));
        return true;
    }
    else if (children.size() == 2){
        //we still need a reference point...
        if (res_true == 2){
            //we have two reference pts
            n_ref[u] = true;
            return true;
        }
        else if (res_true == 1){
            if (n_ref[children[0]] || n_ref[children[1]]){
                return true;
            }
            ans++; n_ref[u] = true;
            return true;
        }
        else{
            ans += (max(int(children.size() - 1) - res_true, 0));
            return true;
        }
    }
    else{
        //do n strat if first such instance
        if (!n_ref[children[0]]){
            //do n-strat
            ans++;
            n_ref[u] = true;
            return true;
        }
        else{
            //we alr have n-strat
            n_ref[u] = true;
            return true;
        }
    }
}

int main(){
    int t;
    cin >> t;
    while (t--){
        int n; cin >> n;
        for (int i = 0; i < n-1; i++){
            int u, v;
            cin >> u >> v; u--; v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        dfs(0, -1);
        cout << ans << "\n";
        for (int i = 0; i < n; i++){
            adj[i].clear();
            num_children[i] = 0;
            n_ref[i] = false;
        }
        ans = 0;
    }
}