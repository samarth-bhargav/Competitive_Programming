#include <bits/stdc++.h>
using namespace std;

const int mxN = 2e5;
const int mxL = 20;
vector<int> adj[mxN];
unordered_map<int, int> tin, tout, depth;
unordered_map<int, int> ett_to_idx;
vector<int> ett;
int par[mxN][mxL];

struct st_min{
    vector<int> t, a;
    int sz;
    st_min(int n){
        if (n == 0) return;
        t.resize(4*n);
        a.resize(n);
        this->sz = n;
        bld(1, 0, sz-1);
    }
    void bld(int v, int tl, int tr){
        if (tl == tr){
            a[tl] = mxN+1;
            t[v] = mxN+1;
            return;
        }
        int tm = (tl + tr) / 2;
        bld(v*2, tl, tm);
        bld(v*2+1, tm+1, tr);
        t[v] = min(t[v*2], t[v*2+1]);
    }
    void upd(int pos, int new_val){
        upd(1, 0, sz-1, pos, new_val);
    }
    void upd(int v, int tl, int tr, int pos, int new_val){
        if (tl == tr){
            a[tl] = new_val;
            t[v] = new_val;
            return;
        }
        int tm = (tl + tr) / 2;
        if (pos <= tm){
            upd(v*2, tl, tm, pos, new_val);
        }
        else{
            upd(v*2+1, tm+1, tr, pos, new_val);
        }
        t[v] = min(t[v*2], t[v*2+1]);
    }
    int qry(int l, int r){
        return qry(1, 0, sz-1, l, r);
    }
    int qry(int v, int tl, int tr, int l, int r){
        if (l > r) return mxN;
        if (tl == l && tr == r){
            return t[v];
        }
        int tm = (tl + tr) / 2;
        return min(qry(v*2, tl, tm, l, min(tm, r)),
                   qry(v*2+1, tm+1, tr, max(l, tm+1), r));
    }
} st(0);

void dfs(int u, int v, int d=0){
    par[u][0] = v;
    for (int i = 1; i < mxL; i++){
        if (par[u][i-1] == -1) break;
        par[u][i] = par[par[u][i-1]][i-1];
    }
    ett.push_back(d);
    depth[u] = d;
    tin[u] = ett.size() - 1;
    ett_to_idx[ett.size() - 1] = u;
    for (int nbr : adj[u]){
        if (nbr != v){
            dfs(nbr, u, d+1);
        }
    }
    ett.push_back(d);
    tout[u] = ett.size() - 1;
    ett_to_idx[ett.size() - 1] = u;
}

int anc(int x, int d){
    int ans = x;
    for (int b = 0; b < mxL; b++){
        if ((d >> b) & 1){
            ans = par[ans][b];
        }
    }
    return ans;
}

int min_child(int x){
    return st.qry(tin[x], tout[x]);
}

void upd_node(int x){
    st.upd(tin[x], depth[x]);
    st.upd(tout[x], depth[x]);
}


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n, b; cin >> n >> b; b--;
        for (int i = 0; i < n; i++){
            for (int l = 0; l < mxL; l++){
                par[i][l] = -1;
            }
        }
        vector<int> c(n);
        for (int i = 0; i < n-1; i++){
            cin >> c[i]; c[i]--;
        }
        for (int i = 0; i < n-1; i++){
            int u, v; cin >> u >> v; u--; v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        dfs(0, -1);
        st = st_min(ett.size());
        st.upd(tin[b], depth[b]);
        st.upd(tout[b], depth[b]);
        int ans = mxN;
        for (int i = 0; i < n-1; i++){
            int q = c[i];
            int ans_root = min_child(0) + depth[q];
            int lo = 0, hi = depth[q];
            while (lo < hi){
                int mid = (lo + hi) / 2;
                int ancestor = anc(q, mid);
                if ((min_child(ancestor) - depth[ancestor]) + (depth[q] - depth[ancestor]) <= ans_root - (depth[ancestor])){
                    hi = mid;
                }
                else{
                    lo = mid+1;
                }
            }
            int curr_ans = min_child(q) - depth[q];
            curr_ans = min(curr_ans, min_child(anc(q, lo)) - depth[anc(q, lo)] + (depth[q] - depth[anc(q, lo)]));
            cout << min(ans, curr_ans) << " ";
            ans = min(ans, curr_ans);
            upd_node(q);
        }
        cout << "\n";
        for (int i = 0; i < n; i++){
            adj[i].clear();
        }
        ett.clear();
        tout.clear();
        tin.clear();
        ett_to_idx.clear();
    }
}