#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5, INF = 1e9;
map<int, int> loc;

struct st{
    int sz;
    vector<set<int>> t;
    vector<int> a;
    st(vector<int> a){
        sz = a.size();
        t.resize(4*sz);
        this->a = a;
        bld(1, 0, sz-1);
    }
    void bld(int v, int tl, int tr){
        if (tl == tr){
            t[v].insert(a[tl]);
            return;
        }
        int tm = (tl + tr) / 2;
        bld(v*2, tl, tm);
        bld(v*2+1, tm+1, tr);
        for (int elem : t[v*2]){
            t[v].insert(elem);
        }
        for (int elem : t[v*2+1]){
            t[v].insert(elem);
        }
    }
    int qry_HI(int l, int r, int x){
        return qry(1, 0, sz-1, l, r, x, 1);
    }
    int qry_LO(int l, int r, int x){
        return qry(1, 0, sz-1, l, r, x, 0);
    }
    int qry(int v, int tl, int tr, int l, int r, int x, bool HI){
        if (l > r){
            return -INF;
        }
        if (l == tl && r == tr){
            auto it = t[v].lower_bound(x);
            if (HI){
                return it == t[v].end() ? -INF : *it;
            }
            else{
                return it == t[v].begin() ? -INF : *prev(it);
            }
        }
        int tm = (tl + tr) / 2;
        int i1 = qry(v*2, tl, tm, l, min(r, tm), x, HI);
        int i2 = qry(v*2+1, tm+1, tr, max(l, tm+1), r, x, HI);
        if (i1 == -INF && i2 == -INF){
            return -INF;
        }
        if (i1 == -INF ^ i2 == -INF){
            return (i1 == -INF ? i2 : i1);
        }
        return loc[i1] < loc[i2] ? i2 : i1;
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
        loc[a[i]] = i;
    }
    loc[0] = -INF; loc[-INF] = -INF;
    st s_tree(a);
    int curr_ans = 0;
    cout << curr_ans << "\n";
    for (int i = 1; i <= n; i++){
        int location = loc[i];
        int one, two;
        if (location == 0){
            one = 0;
        }
        else{
            one = (loc[s_tree.qry_HI(0, location-1, i)] > loc[s_tree.qry_LO(0, location-1, i)] ? 1 : 0);
        }
        two = (loc[i-1] > location ? -1 : 0);
        cout << one + two + curr_ans << "\n";
        curr_ans += (one + two);
    }
}
