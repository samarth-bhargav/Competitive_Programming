#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5 + 5;

vector<int> adj[mxN];
int type[mxN];
vector<int> height;
unordered_map<int,int> height_to_node;
unordered_map<int,int> node_to_first_height;

struct stmin{
    int sz;
    vector<int> t;
    vector<int> a;
    stmin(){}
    stmin(vector<int> a){
        this->a = a;
        this->sz = a.size();
        t.resize(4*sz+1);
        bld(1, 0, sz-1);
    }
    void bld(int v, int tl, int tr){
        if (tl == tr){
            t[v] = tl;
        }
        else{
            int tm = (tl + tr)/2;
            bld(v*2, tl, tm);
            bld(v*2+1, tm+1, tr);
            if (a[t[v*2]] < a[t[v*2+1]]){
                t[v] = t[v*2];
            }
            else{
                t[v] = t[v*2+1];
            }
        }
    }
    int qry(int l, int r){
        return qry(1, 0, sz-1, l, r);
    }
    int qry(int v, int tl, int tr, int l, int r){
        if (l > r){
            return 1e9;
        }
        if (l == tl && r == tr){
            return t[v];
        }
        int tm = (tl + tr)/2;
        int left_min = qry(v*2, tl, tm, l, min(tm, r));
        int right_min = qry(v*2+1, tm+1, tr, max(l, tm+1), r);
        if (right_min == 1e9){
            return left_min;
        }
        if (left_min == 1e9){
            return right_min;
        }
        if (a[left_min] < a[right_min]){
            return left_min;
        }
        return right_min;
    }
} height_st;

void lca_prep(int u, int v, int h){
    height.push_back(h);
    height_to_node[height.size()-1] = u;
    node_to_first_height[u] = height.size()-1;
    for (int node : adj[u]){
        if (node != v){
            lca_prep(node, u, h+1);
            height.push_back(h);
            height_to_node[height.size()-1] = u;
        }
    }
}

void lca_prep(){
    lca_prep(0, -1, 1);
    height_st = stmin(height);
}

int lca(int l, int r){
    int i_1 = node_to_first_height[l];
    int i_2 = node_to_first_height[r];
    if (i_2 < i_1){
        swap(i_1, i_2);
    }
    return height_to_node[height_st.qry(i_1, i_2)];
}

vector<int> et;
int first_occ_et[mxN];

void euler_tour(int u, int v){
    et.push_back(type[u]);
    first_occ_et[u] = et.size()-1;
    for (auto & node : adj[u]){
        if (node != v){
            euler_tour(node, u);
        }
    }
    et.push_back(-type[u]);
}

vector<int> instances[2*mxN];


void ett(){
    euler_tour(0, -1);
    for (int i = 0; i < et.size(); i++){
        instances[et[i]+100000].push_back(i);
    }
}

int oiet(int l, int r, int c){
    if (instances[c+100000].empty()){
        return 0;
    }
    if (l > r){
        swap(l, r);
    }
    return upper_bound(instances[c+100000].begin(), instances[c+100000].end(), r)
                - lower_bound(instances[c+100000].begin(), instances[c+100000].end(), l);
}
bool exists_on_path(int a, int b, int c){
    int ancestor = lca(a,b);
    int f1 = first_occ_et[a];
    int f2 = first_occ_et[b];
    int f3 = first_occ_et[ancestor];
    bool path1 = ((oiet(f1, f3, c)) - oiet(f1, f3, -c));
    bool path2 = ((oiet(f2, f3, c)) - oiet(f2, f3, -c));
    return path1 || path2;
}

int32_t main(){
    ifstream cin("milkvisits.in");
    ofstream cout("milkvisits.out");
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,m;
    cin >> n >> m;
    for (int i = 0; i < n; i++){
        cin >> type[i];
    }
    for (int i = 0; i < n-1; i++){
        int a,b;
        cin >> a >> b; a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    lca_prep();
    ett();
    for (int i = 0; i < m; i++){
        int a, b, c;
        cin >> a >> b >> c; a--; b--;
        cout << exists_on_path(a, b, c);
    }
    cout << "\n";
}
