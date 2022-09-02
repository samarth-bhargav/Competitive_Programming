#include <bits/stdc++.h>
using namespace std;


struct st{
    vector<int> t;
    vector<int> a;
    int sz;
    st(int sz){
        this->sz = sz;
        a.resize(sz);
        fill(a.begin(), a.end(), 0);
        t.resize(4*sz);
        bld(1, 0, sz-1);
    }
    void bld(int v, int tl, int tr){
        if (tl == tr){
            t[v] = a[tl];
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
            a[pos] = new_val;
            t[v] = new_val;
            return;
        }
        int tm = (tl + tr) / 2;
        if (tm >= pos){
            //it's within [tl, tm]
            upd(v*2, tl, tm, pos, new_val);
        }
        else{
            upd(v*2+1, tm+1, tr, pos, new_val);
        }
        t[v] = min(t[v*2], t[v*2+1]);
    }
    int qry_1(int l, int r){
        return qry_1(1, 0, sz-1, l, r);
    }
    int qry_1(int v, int tl, int tr, int l, int r){
        if (t[v] == 1){
            return tl;
        }
        if (a[r] == 0){
            return 1e9;
        }
        int x,y = 1e9;
        int tm = (tl + tr) / 2;
        x = qry_1(v*2, tl, tm, l, tm);
        if (tm < r){
            //consider right child too
            y = qry_1(v*2+1, tm+1, tr, tm+1, r);
        }
        return min(x, y);
    }
    int qry_2(int l, int r){
        return qry_2(1, 0, sz-1, l, r);
    }
    int qry_2(int v, int tl, int tr, int l, int r){
        if (t[v] == 1){
            return tr;
        }
        if (a[l] == 0){
            return 1e9;
        }
        int x, y = 1e9;
        int tm = (tl + tr) / 2;
        x = qry_2(v*2+1, tm+1, tr, tm+1, r);
        if (tm+1 > l){
            y = qry_2(v*2, tl, tm, l, tm);
        }
        return min(x,y);
    }
};

int main(){
    st t(9);
    t.upd(2,1);
    t.upd(4,1);
    t.upd(5,1);
    t.upd(6,1);
    t.upd(8,1);
    //[0, 0, 1, 0, 1, 1, 1, 0, 1]
    cout << t.qry_1(0, 5) << "\n";
    cout << t.qry_2(5, 8) << "\n";
}