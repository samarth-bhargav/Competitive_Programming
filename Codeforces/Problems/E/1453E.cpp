#include <bits/stdc++.h>
using namespace std;

const int mxN = 2e5;
const int mxL = 20;
const int INF = 1e9;

vector<int> adj[mxN];
vector<vector<int>> vals(mxN, vector<int>());
int anc[mxN][mxL];

struct st_max{
    int sz;
    vector<int> t;
    vector<int> a;
    st_max(){}
    st_max(vector<int> d){
        a = d;
        this->sz = d.size();
        a.push_back(-1);
        t.resize(4*sz);
        bld(1, 0, sz-1);
    }
    void bld(int v, int tl, int tr){
        if (tl == tr){
            t[v] = tl;
            return;
        }
        int tm = (tl + tr) / 2;
        bld(v*2, tl, tm);
        bld(v*2+1, tm+1, tr);
        if (a[t[v*2]] > a[t[v*2+1]]){
            t[v] = t[v*2];
        }
        else{
            t[v] = t[v*2+1];
        }
    }
    int qry(int v, int tl, int tr, int l, int r){
        if (l > r) return sz;
        if (l == tl && r == tr){
            return t[v];
        }
        int tm = (tl + tr) / 2;
        int q1 = qry(v*2, tl, tm, l, min(r, tm));
        int q2 = qry(v*2+1, tm+1, tr, max(tm+1, l), r);
        if (a[q1] > a[q2]){
            return q1;
        }
        return q2;
    }
    int qry(int l, int r){
        return qry(1, 0, sz-1, l, r);
    }
    void upd(int v, int tl, int tr, int pos, int new_val){
        if (tl == tr){
            a[pos] = new_val;
            t[v] = pos;
            return;
        }
        int tm = (tl + tr) / 2;
        if (pos <= tm){
            upd(v*2, tl, tm, pos, new_val);
        }
        else{
            upd(v*2+1, tm+1, tr, pos, new_val);
        }
        if (a[t[v*2]] > a[t[v*2+1]]){
            t[v] = t[v*2];
        }
        else{
            t[v] = t[v*2+1];
        }
    }
    void upd(int pos, int new_val){
        upd(1, 0, sz-1, pos, new_val);
    }
} st;

vector<int> ett_to_idx;
vector<int> tin(2*mxN+5), tout(2*mxN+5), ett;
vector<bool> active(mxN, true);

void dfs1(int u, int v, int d=0){
    if (adj[u].size() == 1 && u != 0){
        ett.push_back(d);
    }
    else{
        ett.push_back(-1);
    }
    ett_to_idx.push_back(u);
    tin[u] = ett.size()-1;
    anc[u][0] = v;
    for (int i = 1; i < mxL; i++){
        if (anc[u][i-1] == -1) break;
        anc[u][i] = anc[anc[u][i-1]][i-1];
    }
    for (int c : adj[u]){
        if (c != v) dfs1(c, u, d+1);
    }
    if (adj[u].size() == 1 && u != 0){
        ett.push_back(d);
    }
    else{
        ett.push_back(-1);
    }
    ett_to_idx.push_back(u);
    tout[u] = ett.size()-1;
}

bool bad = false;

int dfs2(int u, int v){
    if (adj[u].size() == 1 && u != 0){
        //leaf node case
        return 1;
    }
    int curr = 0;
    for (int c : adj[u]){
        if (c != v){
            curr += dfs2(c, u);
        }
    }
    //need to take out nodes alr not used
    bool one_active = false;
    for (int node : vals[u]){
        if (active[node]){
            if (u == 0 && !one_active){
                one_active = true;
            }
            else{
                active[node] = false;
                st.upd(tin[node], -1);
                st.upd(tout[node], -1);
                curr--;
            }
        }
    }
    curr += one_active;
    int to_subtract = (u == 0 ? adj[u].size() : adj[u].size() - 2);
    for (int i = 0; i < to_subtract; i++){
        //deepest active node
        int deep = st.qry(tin[u], tout[u]);
        if (st.a[deep] == -1){
            //no leaf nodes left
            bad = true;
            break;
        }
        active[ett_to_idx[deep]] = false;
        st.upd(tin[ett_to_idx[deep]], -1);
        st.upd(tout[ett_to_idx[deep]], -1);
        curr--;
    }
    if (bad){
        return -1;
    }
    return curr;
}

int par(int x, int d){
    for (int b = 0; b < mxL; b++){
        if ((d >> b) & 1){
            x = anc[x][b];
            if (x == -1) return -1;
        }
    }
    return x;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        for (int i = 0; i < n-1; i++){
            int a, b; cin >> a >> b; a--; b--;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        for (int i = 0; i < n; i++){
            for (int j = 0; j < mxL; j++){
                anc[i][j] = -1;
            }
        }
        dfs1(0, -1);
        int lo = 1, hi = n;
        while (lo < hi){
            bad = false;
            fill(vals.begin(), vals.begin()+n, vector<int>());
            fill(active.begin(), active.begin()+n, true);
            st = st_max(ett);
            int mid = (lo + hi) / 2;
            for (int i = 1; i < n; i++){
                if (adj[i].size() == 1){
                    //mark anc
                    int p = par(i, mid);
                    if (p != -1){
                        vals[par(i, mid)].push_back(i);
                    }
                }
            }
            dfs2(0, -1);
            if (bad){
                lo = mid+1;
            }
            else{
                hi = mid;
            }
        }
        cout << lo << "\n";
        for (int i = 0; i < n; i++){
            adj[i].clear();
        }
        ett.clear();
        ett_to_idx.clear();
        for (int i = 0; i < n; i++){
            for (int l = 0; l < mxL; l++){
                anc[i][l] = -1;
            }
        }
    }
}
