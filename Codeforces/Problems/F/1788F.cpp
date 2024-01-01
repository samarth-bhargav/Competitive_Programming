#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;

const int mxN = 250010;
vector<int> adj[mxN];
vector<int> p;
vector<int> ans;

struct dsu{
    int n;
    vector<int> sz;
    vector<int> p;
    dsu (int n){
        this->n = n;
        p.resize(n);
        sz.resize(n);
        iota(p.begin(), p.end(), 0);
        fill(sz.begin(), sz.end(), 1);
    }
    int find(int x){
        return x ^ p[x] ? p[x] = find(p[x]) : p[x];
    }
    int conj(int x){
        return x < (n / 2) ? x + (n / 2) : x - (n / 2);
    }
    int norm(int x){
        return x >= (n / 2) ? conj(x) : x;
    }
    void join(int a, int b){
        a = find(a); b = find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, q; cin >> n >> q;
    vector<array<int,2>> edges;
    for (int i = 0; i < n-1; i++){
        int u, v; cin >> u >> v; u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
        edges.push_back({u, v});
    }
    vector<int> leaf_nodes;
    for (int i = 0; i < n; i++){
        if (adj[i].size() % 2 == 1){
            leaf_nodes.push_back(i);
        }
    }
    vector<array<int, 3>> restrictions(q);
    for (int i = 0; i < q; i++){
        cin >> restrictions[i][0] >> restrictions[i][1] >> restrictions[i][2];
        restrictions[i][0]--; restrictions[i][1]--;
    }
    p.resize(n, 0);
    for (int b = 0; b < 30; b++){
        dsu d(2 * n);
        dsu acc(n);
        for (int i = 0; i < q; i++){
            acc.join(restrictions[i][0], restrictions[i][1]);
            if ((restrictions[i][2] >> b) & 1){
                //p[r[i][0]] and p[r[i][1]] are opposite
                d.join(restrictions[i][0], d.conj(restrictions[i][1]));
                d.join(restrictions[i][1], d.conj(restrictions[i][0]));
            }
            else{
                //p[r[i][0]] and p[r[i][1]] are same
                d.join(restrictions[i][0], restrictions[i][1]);
                d.join(d.conj(restrictions[i][0]), d.conj(restrictions[i][1]));
            }
        }
        vector<int> f(2 * n);
        for (int i = 0; i < 2 * n; i++){
            f[i] = d.find(i);
        }
        for (int i = 0; i < n; i++){
            if (f[i] == f[d.conj(i)]){
                cout << "No\n";
                return 0;
            }
        }
        //check in actual connected components for parity
        gp_hash_table<int, array<int, 2>> components;
//        unordered_map<int, array<int, 2>> components; //{par, {tot, pos}}
        gp_hash_table<int, int> dcs;
        vector<vector<int>> ccs(2 * n, vector<int>());
        for (int i = 0; i < 2 * n; i++){
            ccs[f[i]].push_back(i);
        }
        for (int i = 0; i < leaf_nodes.size(); i++){
            int par = acc.find(leaf_nodes[i]);
            dcs[f[par]] = 1;
            if (components.find(par) == components.end()){
                components[par] = {0, 0};
            }
            components[par][0]++;
            if (f[leaf_nodes[i]] == f[par]){
                //positive version stored
                components[par][1]++;
            }
        }
        int tot = 0;
        pair<int, array<int, 2>> if_exists = {-1, {-1, -1}};
        bool set_one;
        for (auto pp : components){
            if ((pp.second[0] - pp.second[1]) % 2 != pp.second[1] % 2){
                //opposite parity YAYAYAYYAYAY
                if_exists = pp;
            }
            else{
                tot ^= (pp.second[1] % 2);
            }
        }
        if (tot == 0){
            //need to set pp to 0
            set_one = false;
        }
        else{
            set_one = true;
        }
        for (auto pp : components){
            if (pp.first == if_exists.first && pp.second == if_exists.second){
                int parent = pp.first;
                if (set_one ^ (if_exists.second[1] % 2)){
                    //its opposite of what we want, so impose dual
                    parent = d.conj(pp.first);
                }
                for (int val : ccs[f[parent]]){
                    if (val < n){
                        p[val] ^= (1 << b);
                    }
                }
            }
            else{
                //just impose 0 if you can
                int parent = pp.first;
                if (pp.second[1] % 2 == 1){
                    parent = d.conj(pp.first);
                }
                for (int val : ccs[f[parent]]){
                    if (val < n){
                        p[val] ^= (1 << b);
                    }
                }
            }
        }
        //just set random stuff for rest lmao
        for (int i = 0; i < n; i++){
            if (!(ccs[i].size() == 1) && dcs.find(i) == dcs.end() && dcs.find(f[i + n]) == dcs.end()){
                for (int val : ccs[i]){
                    if (val < n){
                        p[val] ^= (1 << b);
                        dcs[i] = 1;
                    }
                }
            }
        }
    }
    //bro i am stupid
    ans.resize(n-1, 0);
    cout << "Yes\n";
    for (int i = 0; i < n-1; i++){
        cout << (p[edges[i][0]] ^ p[edges[i][1]]) << " ";
    }
    cout << "\n";
    for (int i = 0; i < q; i++){
        assert((p[restrictions[i][0]] ^ p[restrictions[i][1]]) == restrictions[i][2]);
    }
}