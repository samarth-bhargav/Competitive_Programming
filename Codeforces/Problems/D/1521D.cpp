#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;
const int INF = 1e9;
vector<int> adj[mxN];
set<int> adj_cpy[mxN];
vector<array<int, 2>> leaf_nodes(mxN);
vector<array<int, 4>> ops;
int root = 0;

int timer = 0;
vector<int> tin(mxN), tout(mxN);

void dfs2(int v, int p){
    tin[v] = ++timer;
    for (int u : adj[v]) {
        if (u != p)
            dfs2(u, v);
    }
    tout[v] = ++timer;
}

bool is_ancestor(int u, int v){
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

void upd(int a, int b, int c, int d){
    adj_cpy[a].erase(b);
    adj_cpy[b].erase(a);
    adj_cpy[c].insert(d);
    adj_cpy[d].insert(c);
}

void dfs(int e, int v){
    int curr_leaf = -1;
    int first_node = -1;
    if (e != root){
        adj[e].erase(find(adj[e].begin(), adj[e].end(), v));
        adj_cpy[e].erase(v);
    }
    for (int i = 0; i < (int)(adj[e].size()); i++){
        int node = adj[e][i];
        dfs(node, e);
        if (curr_leaf == -1){
            first_node = node;
            curr_leaf = leaf_nodes[node][0];
            leaf_nodes[e][0] = leaf_nodes[node][1];
        }
        else{
            if (i == adj[e].size() - 1){
                continue;
            }
            if (adj_cpy[node].size() == 1){
                ops.push_back({e, node, curr_leaf, leaf_nodes[node][0]});
                upd(e, node, curr_leaf, leaf_nodes[node][0]);
                curr_leaf = node;
                leaf_nodes[e][0] = curr_leaf;
            }
            else{
                ops.push_back({e, node, curr_leaf, leaf_nodes[node][0]});
                upd(e, node, curr_leaf, leaf_nodes[node][0]);
                curr_leaf = leaf_nodes[node][1];
                leaf_nodes[e][0] = curr_leaf;
            }
        }
    }

    if (first_node != -1 && adj_cpy[first_node].size() == 2){
        int other;
        if (is_ancestor(*adj_cpy[first_node].begin(), leaf_nodes[e][0])){
            other = *adj_cpy[first_node].begin();
        }
        else{
            other = *next(adj_cpy[first_node].begin());
        }
        ops.push_back({first_node, other, leaf_nodes[e][0], curr_leaf});
        upd(first_node, other, leaf_nodes[first_node][0], curr_leaf);
        leaf_nodes[e][0] = curr_leaf;
    }
    if (adj[e].size() > 0){
        int last_leaf = leaf_nodes[adj[e][int(adj[e].size())-1]][0];
        int last_node = adj[e][int(adj[e].size())-1];
        if (adj_cpy[last_node].size() == 2){
            int other;
            if (is_ancestor(*adj_cpy[last_node].begin(), last_leaf)){
                other = *next(adj_cpy[last_node].begin());
            }
            else{
                other = *adj_cpy[last_node].begin();
            }
            ops.push_back({last_node, other, leaf_nodes[last_node][1], leaf_nodes[last_node][0]});
            upd(last_node, other, leaf_nodes[last_node][1], leaf_nodes[last_node][0]);
            leaf_nodes[e][1] = other;
        }
        else{
            leaf_nodes[e][1] = leaf_nodes[last_node][0];
        }
    }
    //base case of if it's a leaf node
    if (adj[e].size() == 0){
        leaf_nodes[e][0] = e;
        leaf_nodes[e][1] = e;
    }
}



int main(){
    int t;
    cin >> t;
    while (t--){
        int n; cin >> n;
        for (int i = 0; i < n-1; i++){
            int a, b;
            cin >> a >> b; a--; b--;
            adj[a].push_back(b);
            adj[b].push_back(a);
            adj_cpy[a].insert(b);
            adj_cpy[b].insert(a);
        }
        dfs2(root, -1);
        dfs(root, -1);
        cout << ops.size() << "\n";
        for (array<int, 4> op : ops){
            cout << op[0]+1 << " " << op[1]+1 << " " << op[2]+1 << " " << op[3]+1 << "\n";
        }
        for (int i = 0; i < n; i++){
            adj[i].clear();
            tin[i] = 0; tout[i] = 0; timer = 0;
            adj_cpy[i].clear();
        }
        ops.clear();
    }
}
