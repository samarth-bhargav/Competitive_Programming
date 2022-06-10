#include <bits/stdc++.h>
using namespace std;

#define int long long
struct st{
    int n;
    vector<int> ar;
    vector<int> t;
    int type; //0 = xor, 1 = min
    st(){}
    st(vector<int> ar, int type){
        this->ar = ar;
        this->type = type;
        this->n = ar.size();
        t.resize(4*n);
        bld();
    }
    void bld(){
        bld(1, 0, n-1);
    }
    void bld(int v, int tl, int tr){
        if (tl == tr){
            if (type){
                t[v] = tl;
            }
            else{
                t[v] = ar[tl];
            }
        }
        else{
            int tm = (tl + tr) / 2;
            bld(v*2, tl, tm);
            bld(v*2+1, tm+1, tr);
            if (type){
                t[v] = (ar[t[v*2]] > ar[t[v*2+1]] ? t[v*2+1] : t[v*2]);
            }
            else{
                t[v] = t[v*2] ^ t[v*2+1];
            }
        }
    }
    int qry(int l, int r){
        return qry(1, 0, n-1, l, r);
    }
    int qry(int v, int tl, int tr, int l, int r){
        if (l > r){
            if (type){
                return -1;
            }
            else{
                return 0;
            }
            return 0;
        }
        if (l == tl && r == tr){
            return t[v];
        }
        int tm = (tl + tr)/2;
        if (type){
            int i1 = qry(v*2, tl, tm, l, min(r, tm));
            int i2 = qry(v*2+1, tm+1, tr, max(l, tm+1), r);
            if (i1 == -1 || ar[i1] > ar[i2]){
                return i2;
            }
            return i1;
        }
        else{
            return qry(v*2, tl, tm, l, min(r, tm))
                   ^ qry(v*2+1, tm+1, tr, max(l, tm+1), r);
        }
    }
    void upd(int pos, int new_val){
        upd(1, 0, n-1, pos, new_val);
        ar[pos] = new_val;
    }
    void upd(int v, int tl, int tr, int pos, int new_val){
        if (tl == tr){
            t[v] = new_val;
        }
        else{
            int tm = (tl + tr) / 2;
            if (pos <= tm){
                upd(v*2, tl, tm, pos, new_val);
            }
            else{
                upd(v*2+1, tm+1, tr, pos, new_val);
            }
            if (type){
                if (ar[t[v*2]] > ar[t[v*2+1]]){
                    t[v] = t[v*2+1];
                }
                else{
                    t[v] = t[v*2];
                }
            }
            else{
                t[v] = t[v*2] ^ t[v*2+1];
            }
        }
    }
};


st xortree, mintree;
vector<int> e, e2, ar;
const int mxN = 1e5;
vector<int> adj[mxN];
unordered_map<int,int> hitn;
int tin[mxN], tout[mxN], height[mxN], f[mxN];

void dfs(int u, int v, int h){
    e.push_back(ar[u]);
    e2.push_back(h);
    hitn[e2.size()-1] = u;
    f[u] = e2.size()-1;
    tin[u] = e.size()-1;
    for (auto & edge : adj[u]){
        if (edge != v){
            dfs(edge, u, h+1);
            e2.push_back(h);
            hitn[e2.size()-1] = u;
        }
    }
    e.push_back(ar[u]);
    tout[u] = e.size()-1;
}

int query(int u, int v){
    int lca = hitn[mintree.qry(min(f[u], f[v]), max(f[u], f[v]))];
//    cerr << "lca of " << u+1 << " and " << v+1 << " = " << lca+1 << "\n";
    int lbranch = xortree.qry(tin[lca], tin[u]);
    int rbranch = xortree.qry(tin[lca], tin[v]);
    return lbranch ^ rbranch ^ ar[lca];
}


int32_t main(){
    ifstream cin("cowland.in");
    ofstream cout("cowland.out");
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        ar.push_back(x);
    }
    for (int i = 0; i < n-1; i++){
        int a,b;
        cin >> a >> b; a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(0, -1, 0);
    xortree = st(e, 0);
    mintree = st(e2, 1);
//    cerr << "Query of 2 & 5: " << query(1,4) << "\n";
    for (int i = 0; i < q; i++){
        int a, b, c;
        cin >> a >> b >> c;
        b--;
        if (a == 1){
            //update
            ar[b] = c;
            xortree.upd(tin[b], c);
            xortree.upd(tout[b], c);
        }
        else{
            c--;
            //query
            cout << query(b, c) << "\n";
        }
    }
}
