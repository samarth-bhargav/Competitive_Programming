#include <bits/stdc++.h>
using namespace std;

#define int long long
const int mxN = 2e5;
vector<int> adj[mxN], a(mxN);
bool depth = false;

struct node{
    int s, t, d;
    node (int s, int t, int d=0){
        this->s = s;
        this->t = t;
        this->d = d;
    }
    node(){}
    bool operator <(const node &o) const{
        if (depth){
            if (d > o.d) return false; //greater depth, process later
            if (d < o.d) return true;
        }
        return t * o.s < o.t * s;
    }
};

vector<pair<int, node>> normAns(mxN);

pair<int, node> dfs(int u, int v){
    //return {ans, (sum, time)}
    vector<node> children;
    int base = 0, s = 0, t = 0;
    for (int c : adj[u]){
        if (c != v){
            pair<int, node> res = dfs(c, u);
            base += res.first;
            children.push_back(node(res.second.s, res.second.t+2));
            s += res.second.s;
            t += res.second.t + 2;
        }
    }
    s += a[u];
    sort(children.begin(), children.end());
    int t_offset = 1;
    for (int i = 0; i < children.size(); i++){
        base += t_offset * children[i].s;
        t_offset += children[i].t;
    }
    normAns[u] = {base, node(s, t)};
    return {base, node(s, t)};
}

pair<int, node> dfs1(int u, int v, int d=0){
    //return {ans, (sum, time, maxDepth)}
    vector<pair<node, int>> children;
    int base = 0, s = 0, t = 0, maxD = 0;
    for (int c : adj[u]){
        if (c != v){
            pair<int, node> res = dfs1(c, u, d+1);
            base += res.first;
            children.push_back({node(res.second.s, res.second.t+2, res.second.d), c});
            s += res.second.s;
            t += res.second.t + 2;
            maxD = max(maxD, res.second.d);
        }
    }
    s += a[u];
    if (children.empty() && depth){
        return {base, node(s, t, d)};
    }
    depth = true;
    auto it = max_element(children.begin(), children.end());
    pair<node, int> mx = *it;
    children.erase(it);
    depth = false;
    //replace children with normal answer
    vector<pair<node, int>> acc_children;
    for (int i = 0; i < children.size(); i++){
        node chld = normAns[children[i].second].second;
        acc_children.push_back({node(chld.s, chld.t+2, chld.d), i});
    }
    children = acc_children;
    sort(children.begin(), children.end());
    depth = true;
    children.push_back(mx);

    int t_offset = 1;
    for (int i = 0; i < (int)(children.size()); i++){
        base += t_offset * children[i].first.s;
        t_offset += children[i].first.t;
    }
    return {base, node(s, normAns[u].second.t-(maxD-d), maxD)};
}

int32_t main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, t;
    cin >> n >> t;
    if (t == 1) depth = true;
    a[0] = 0;
    for (int i = 1; i < n; i++){
        int p;
        cin >> p >> a[i]; p--;
        adj[p].push_back(i);
        adj[i].push_back(p);
    }
    pair<int, node> res = dfs(0, -1);
    if (t == 0){
        cout << res.second.t << " " << res.first << "\n";
    }
    else{
        pair<int, node> result = dfs1(0, -1);
        cout << result.second.t << " " << result.first << "\n";
    }
}
