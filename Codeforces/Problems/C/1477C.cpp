#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int mxN = 5000;
vector<int> adj[mxN];

ll sqr_dst(array<int, 2> a, array<int, 2> b){
    return (ll)(b[1] - a[1]) * (b[1] - a[1]) + (b[0] - a[0]) * (ll)(b[0] - a[0]);
}

bool ang(array<int, 2> a, array<int, 2> b, array<int, 2> c){
    if (sqr_dst(a, b) > sqr_dst(a, c) - sqr_dst(b, c)){
        return true;
    }
    return false;
}

struct dsu{
    vector<int> sz;
    vector<int> p;
    dsu (int n){
        this->p.resize(n);
        this->sz.resize(n, 1);
        iota(p.begin(), p.end(), 0);
    }
    int find(int x){
        return x == p[x] ? x : p[x] = find(p[x]);
    }
    bool join(int a, int b){
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]){
            swap(a,b);
        }
        p[a] = b;
        sz[b] += sz[a];
        return true;
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    vector<array<int, 2>> nodes(n);
    for (int i = 0; i < n; i++) {
        cin >> nodes[i][0] >> nodes[i][1];
    }
    vector<pair<ll, array<int, 2>>> edges;
    edges.reserve(n * (n-1) / 2);
    for (int i = 0; i < n; i++){
        for (int j = i+1; j < n; j++){
            edges.push_back({-sqr_dst(nodes[i], nodes[j]), {i, j}});
        }
    }
    for (int i = 0; i < n; i++){
        adj[i].reserve(2);
    }
    sort(edges.begin(), edges.end());
    int edges_added = 0;
    dsu d(n);
    for (auto edge : edges){
        //make sure outdegree sufficient
        if (adj[edge.second[0]].size() >= 2){
            continue;
        }
        if (!adj[edge.second[0]].empty() && !ang(nodes[adj[edge.second[0]][0]], nodes[edge.second[0]], nodes[edge.second[1]])){
            continue;
        }
        if (adj[edge.second[1]].size() >= 2){
            continue;
        }
        if (!adj[edge.second[1]].empty() && !ang(nodes[adj[edge.second[1]][0]], nodes[edge.second[1]], nodes[edge.second[0]])){
            continue;
        }

        if (d.join(edge.second[0], edge.second[1])){
            adj[edge.second[0]].push_back(edge.second[1]);
            adj[edge.second[1]].push_back(edge.second[0]);
            edges_added++;
            if (edges_added == n-1){
                break;
            }
        }
    }
    int leaf = -1;
    for (int i = 0; i < n; i++){
        if (adj[i].size() == 1){
            leaf = i;
            break;
        }
    }
    if (leaf == -1){
        cout << -1 << "\n";
        exit(0);
    }
    vector<int> path; path.push_back(leaf);
    int curr = leaf, nex = adj[leaf][0];
    while (true){
        path.push_back(nex);
        if (adj[nex].size() == 1){
            break;
        }
        int temp = nex;
        nex = adj[nex][0] == curr ? adj[nex][1] : adj[nex][0];
        curr = temp;
    }
    if (path.size() != n){
        cout << "-1\n";
        exit(0);
    }
    for (int x : path){
        cout << x+1 << " ";
    }
    cout << "\n";
}
