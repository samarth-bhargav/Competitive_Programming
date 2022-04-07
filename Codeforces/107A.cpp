#include <bits/stdc++.h>

using namespace std;

struct node{
    int diameter;
    int id;
};
const int mxN = 1e3+5;
vector <node> adj[mxN+1];
int n, p;
bool vis[mxN+1] = {0};
node ar[mxN+1];
vector <int> tanks;
vector <tuple<int,int,int>> ans;
void dfs(int child, int init, int mincnt){
    vis[child] = true;
    mincnt = min(mincnt, ar[child].diameter);
    for (auto & i : adj[child]){
        if (!vis[i.id]){
            dfs(i.id, init, mincnt);
        }
    }
    if (adj[child].empty()){
        ans.emplace_back(init,child,mincnt);
    }
}

int main(){
    cin >> n >> p;
    map <int,int> nottanks;
    bool exists[mxN];
    if (p == 0) {
        cout << 0 << "\n";
        return 0;
    }
    for (int i = 0; i < p; i++){
        int housea, houseb, diameter;
        cin >> housea >> houseb >> diameter;
        node x; x.id = houseb; x.diameter = diameter;
        adj[housea].push_back(x);
        ar[houseb] = x;
        exists[housea] = true; exists[houseb] = true;
        nottanks.insert(make_pair(houseb,1));
    }
    for (int i = 1; i <= n; i++){
        if (nottanks.find(i) == nottanks.end() && exists[i]){
            tanks.push_back(i);
        }
    }
    for (int i : tanks){
        ar[i].diameter = 1e9;
        dfs(i, i, 1e9);
    }
    if (!ans.empty()){
        cout << ans.size() << "\n";
        for (auto & i : ans){
            cout << get<0>(i) << " " << get<1>(i) << " " << get<2>(i) << "\n";
        }
    }
    else{
        cout << 0 << "\n";
    }
}
