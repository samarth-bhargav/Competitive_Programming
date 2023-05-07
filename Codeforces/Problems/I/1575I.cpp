#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;
typedef long long ll;
#define int ll
vector<int> adj[mxN];
vector<int> a(mxN);
vector<int> tin(mxN), tout(mxN);
map<int, int> tin_to_pos, tout_to_pos, depths_to_pos, depths_in;
vector<int> ett, depths;
int rmq[2*mxN][20];

struct st_sum{
    int sz;
    vector<ll> t;
    st_sum(){}
    st_sum(int n){
        sz = n;
        t.resize(4*sz);
        bld(1, 0, sz-1);
    }
    void bld(int v, int tl, int tr){
        if (tl == tr){
            t[v] = ett[tl];
            return;
        }
        int tm = (tl + tr) / 2;
        bld(v*2, tl, tm);
        bld(v*2+1, tm+1, tr);
        t[v] = t[v*2] + t[v*2+1];
    }
    void upd(int pos, int new_val){
        upd(1, 0, sz-1, pos, new_val);
    }
    void upd(int v, int tl, int tr, int pos, int new_val){
        if (tl == tr){
            ett[tl] = new_val;
            t[v] = ett[tl];
            return;
        }
        int tm = (tl + tr) / 2;
        if (pos <= tm){
            upd(v*2, tl, tm, pos, new_val);
        }
        else{
            upd(v*2+1, tm+1, tr, pos, new_val);
        }
        t[v] = t[v*2] + t[v*2+1];
    }
    int qry(int l, int r){
        return qry(1, 0, sz-1, l, r);
    }
    ll qry(int v, int tl, int tr, int l, int r){
        if (l > r) return 0;
        if (tl == l && tr == r){
            return t[v];
        }
        int tm = (tl + tr) / 2;
        return qry(v*2, tl, tm, l, min(r, tm))
             + qry(v*2+1, tm+1, tr, max(l, tm+1), r);
    }
} st;

void dfs(int u, int v, int d){
    ett.push_back(a[u]);
    depths.push_back(d);
    depths_to_pos[depths.size()-1] = u;
    depths_in[u] = depths.size()-1;
    tin[u] = ett.size() - 1;
    tin_to_pos[ett.size() - 1] = u;
    for (int node : adj[u]){
        if (node != v){
            dfs(node, u, d+1);
            depths.push_back(d);
            depths_to_pos[depths.size()-1] = u;
        }
    }
    ett.push_back(-a[u]);
    tout[u] = ett.size() - 1;
    tout_to_pos[ett.size() - 1] = u;
}

int rm_q(int l, int r){
    int d = (r - l + 1);
    int ret = -1;
    for (int L = 0; L < 20; L++){
        if ((d >> L) & 1){
            if (ret == -1 || depths[rmq[l][L]] < depths[ret]){
                ret = rmq[l][L];
            }
            l += (1 << L);
        }
    }
    return ret;
}

bool is_ancestor(int u, int v){
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}
int lca(int u, int v){
    int in1 = depths_in[u], in2 = depths_in[v];
    if (in1 > in2) swap(in1, in2);
    return depths_to_pos[rm_q(in1, in2)];
}

ll sum(int u, int v){
    if (is_ancestor(u, v)){
        return 2 * st.qry(tin[u], tin[v]) - ett[tin[u]] - ett[tin[v]];
    }
    if (is_ancestor(v, u)){
        return 2 * st.qry(tin[v], tin[u]) - ett[tin[v]] - ett[tin[u]];
    }
    int anc = lca(u, v);
    return 2 * st.qry(tin[anc], tin[u]) + 2 * st.qry(tin[anc], tin[v]) - 2 * ett[tin[anc]] - ett[tin[u]] - ett[tin[v]];
}

int32_t main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++){
        cin >> a[i];
        a[i] = abs(a[i]);
    }
    for (int i = 0; i < n-1; i++){
        int u, v;
        cin >> u >> v; u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0, -1, 0);
    st = st_sum(ett.size());
    for (int i = 0; i < depths.size(); i++){
        rmq[i][0] = i;
    }
    for (int L = 1; L < 20; L++){
        for (int i = 0; i < depths.size(); i++){
            if (i + (1 << L) >= depths.size()){
                continue;
            }
            if (depths[rmq[i][L-1]] < depths[rmq[i + (1 << (L-1))][L-1]]){
                rmq[i][L] = rmq[i][L-1];
            }
            else{
                rmq[i][L] = rmq[i + (1 << (L-1))][L-1];
            }
        }
    }
//    cout << lca(1, 2) << "\n";
    for (int i = 0; i < q; i++){
        int t, u, v;
        cin >> t >> u >> v;
        if (t == 1){
            u--;
            st.upd(tin[u], abs(v));
            st.upd(tout[u], -abs(v));
        }
        else{
            u--; v--;
            cout << sum(u, v) << "\n";
        }
    }
}
