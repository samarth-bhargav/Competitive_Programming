#include <bits/stdc++.h>
using namespace std;

struct dsu{
    int n;
    vector<int> p, in_deg;
    dsu(vector<int> in_deg, int n){
        this->n = n;
        p.resize(n);
        this->in_deg = in_deg;
        iota(p.begin(), p.end(), 0);
    }
    int find(int x){
        return x ^ p[x] ? p[x] = find(p[x]) : x;
    }
    void join(int a, int b){
        a = find(a);
        b = find(b);
        p[b] = a;
        in_deg[a] += in_deg[b];
    }
};

const int mxN = 3e5;
set<pair<int, int>> adj[mxN];

vector<int> tin(mxN), tout(mxN);
int timer = 0;

void dfs(int v, int p){
    tin[v] = ++timer;
    for (auto &u : adj[v]){
        if (u.first != p){
            dfs(u.first, v);
        }
    }
    tout[v] = ++timer;
}

int root = -1;

bool is_ancestor(int u, int v){
    //u is ancestor of v
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}


int main(){
    int n, k;
    cin >> n >> k;
    vector<int> direct_parent(n);
    vector<int> in_deg_0(n, 0), in_deg_1(n, 0), in_deg(n, 0);
    for (int i = 0; i < n; i++){
        in_deg_0[i]++;
        in_deg[i]++;
        int p; cin >> p; p--;
        direct_parent[i] = p;
        if (p == -1){
            root = i;
        }
        else{
            adj[p].insert({i, 0});
        }
    }
    dfs(root, -1);
    vector<pair<int, int>> edges;
    for (int i = 0; i < k; i++){
        int a, b;
        cin >> a >> b; a--; b--;
        edges.emplace_back(a, b);
        adj[a].insert({b, 1});
        if (adj[a].find({b, 0}) != adj[a].end()){
            adj[a].erase({b, 0});
            in_deg_1[b]++;
        }
        else{
            in_deg_1[b]++;
            in_deg[b]++;
        }
    }
    dsu d(in_deg, n);
    for (pair<int, int> edge : edges){
        d.join(edge.first, edge.second);
    }
    for (int i = 0; i < n; i++){
        for (auto &node : adj[i]){
            if (d.find(node.first) == d.find(i)){
                d.in_deg[d.find(i)]--;
            }
        }
    }
    //cycle check
    int cnt = 1;
    queue<int> bfs; vector<bool> visited(n, false);
    bfs.push(root);
    while (!bfs.empty()){
        int tp = bfs.front();
        bfs.pop();
        for (auto &node : adj[tp]){
            if (--in_deg[node.first] == 0){
                bfs.push(node.first);
                cnt++;
            }
        }
    }
    if (cnt != n){
        cout << 0 << "\n";
        exit(0);
    }
//    for (int i = 0; i < n; i++){
//        for (auto &node : adj[i]){
//            if (node.second == 1){
//                adj[i].erase({node.first, 0});
//            }
//        }
//    }
    for (int i = 0; i < n; i++){
        for (auto &node : adj[i]){
            if (node.second == 0){
                adj[d.find(i)].insert(node);
            }
        }
    }
    //find topological sort
    bfs.push(root);
    queue<int> top_sort;
    while (!bfs.empty()){
        int tp = bfs.front();
        if (d.find(tp) == tp){
            top_sort.push(tp);
        }
        for (auto &node : adj[tp]){
            if (node.second == 0){
                if (d.find(node.first) == d.find(tp)){
                    continue;
                }
                if (--d.in_deg[d.find(node.first)] == 0){
                    bfs.push(d.find(node.first));
                }
            }
        }
        bfs.pop();
    }
    //find top sort for individual cc
    vector<vector<int>> cc_top(n);
    set<int> roots;
    for (int i = 0; i < n; i++){
        roots.insert(d.find(i));
    }
    for (int node : roots){
        bfs.push(node);
        while (!bfs.empty()){
            int tp = bfs.front();
            cc_top[node].push_back(tp);
            for (auto &nbr : adj[tp]){
                if (nbr.second == 1){
                    if (--in_deg_1[nbr.first] == 0){
                        bfs.push(nbr.first);
                    }
                }
            }
            bfs.pop();
        }
    }
    //check if any elements of top sort violate
    //check if violates ancestor conditions
    vector<int> potential_sol;
    while (!top_sort.empty()){
        int cand = top_sort.front(); top_sort.pop();
        for (int node : cc_top[cand]){
            potential_sol.push_back(node);
        }
    }
    if (potential_sol.size() < n){
        cout << 0 << "\n";
        exit(0);
    }
    for (int i = 1; i < n; i++){
        if (is_ancestor(potential_sol[i-1], potential_sol[i])){
            if (direct_parent[potential_sol[i]] != potential_sol[i-1]){
                cout << 0 << "\n";
                exit(0);
            }
        }
    }
    for (int i = 0; i < n; i++){
        cout << potential_sol[i]+1 << " ";
    }
    cout << "\n";
}