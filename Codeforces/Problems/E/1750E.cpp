#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define int ll
const int mxN = 2e5+1;
vector<int> arr(mxN);
vector<int> adj[mxN];
ll ans = 0;

pair<ll, int> dfs(int u){
    //returns mult, num_children
    int mult = 0;
    int num_children = 0;
    for (int node : adj[u]){
        pair<ll, int> ret;
        if (arr[node] == -1){
            mult--;
            num_children++;
            continue;
        }
        else{
            ret = dfs(node);
        }
        ans += (ret.first + ret.second) * (u - node);
        mult += (ret.first + ret.second);
        num_children += ret.second;
    }
    num_children++;
    return {mult, num_children};
}

struct node{
    vector<int> vals;
    vector<int> p;
    node(){}
    node(int x){
        vals = {x};
        p = {0, x};
    }
};

node merge(node a, node b){
    node c;
    if (a.vals.size() < b.vals.size()){
        c.vals = b.vals;
        for (int x : a.vals){
            c.vals.push_back(x);
        }
    }
    else{
        c.vals = a.vals;
        for (int x : b.vals){
            c.vals.push_back(x);
        }
    }
    sort(c.vals.begin(), c.vals.end());
    c.p = vector<int> (c.vals.size() + 1);
    c.p[0] = 0;
    for (int i = 1; i <= c.vals.size(); i++){
        c.p[i] = c.p[i-1] + c.vals[i-1];
    }
    return c;
}

ll sum_l(node &a, int x){
    ll ret = 0;
    int idx = lower_bound(a.vals.begin(), a.vals.end(), x) - a.vals.begin();
    ret -= a.p[idx];
    ret += x * (idx);
    return ret;
}

struct st{
    int sz;
    vector<node> t;
    vector<int> a;

    st(vector<int> p){
        a = p;
        sz = p.size();
        t.resize(4*sz);
        bld(1, 0, sz-1);
    }
    void bld(int v, int tl, int tr){
        if (tl == tr){
            t[v] = node(a[tl]);
            return;
        }
        int tm = (tl + tr) / 2;
        bld(v*2, tl, tm);
        bld(v*2+1, tm+1, tr);
        t[v] = merge(t[v*2], t[v*2+1]);
    }
    ll qry(int l, int r, int x){
        return qry(1, 0, sz-1, l, r, x);
    }
    ll qry(int v, int tl, int tr, int l, int r, int x){
        if (tl == l && tr == r){
            return sum_l(t[v], x);
        }
        if (l > r) return 0;
        int tm = (tl + tr) / 2;
        return qry(v*2, tl, tm, l, min(r, tm), x)
             + qry(v*2+1, tm+1, tr, max(l, tm+1), r, x);
    }
};

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        string s; cin >> s;
        for (int i = 0; i < n; i++){
            arr[i] = (s[i] == ')' ? 1 : -1);
        }
        vector<int> p(n+1);
        p[0] = 0;
        for (int i = 1; i <= n; i++){
            p[i] = p[i-1] + arr[i-1];
        }
        //next greater idx
        vector<int> ng(n, n);
        stack<array<int, 2>> stk; //val, pos
        for (int i = 1; i <= n; i++){
            if (stk.empty()){
                stk.push({p[i], i-1});
                continue;
            }
            while (!stk.empty() && stk.top()[0] < p[i]){
                ng[stk.top()[1]] = i-1;
                stk.pop();
            }
            stk.push({p[i], i-1});
        }
        //make graph
        for (int i = 0; i < n; i++){
            adj[ng[i]].push_back(i);
        }
        dfs(n);
        st st_sum(p);
        for (int i = 0; i < n; i++){
            ans += st_sum.qry(i+1, n, p[i]);
        }
        cout << ans << "\n";
        ans = 0;
        for (int i = 0; i <= n; i++){
            adj[i].clear();
            adj[i].shrink_to_fit();
        }
    }
}