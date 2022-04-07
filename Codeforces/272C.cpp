#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int mxN = 1e5+5;
int n,m; ll t[4*mxN];


void bld(int a[], int v, int tl, int tr){
    if (tl == tr){
        t[v] = a[tl];
    }
    else{
        int tm = (tl+tr)/2;
        bld(a, v*2, tl, tm);
        bld(a, v*2+1, tm+1, tr);
        t[v] = max(t[v*2],t[v*2+1]);
    }
}
void upd(int v, int tl, int tr, int pos, ll val){
    if (tl == tr){
        t[v] = val;
    }
    else{
        int tm = (tl+tr)/2;
        if (pos <= tm){
            upd(v*2, tl, tm, pos, val);
        }
        else{
            upd(v*2+1,tm+1,tr,pos,val);
        }
        t[v] = max(t[v*2],t[v*2+1]);
    }
}
ll gm(int v, int tl, int tr, int l, int r){
    if (l > r){
        return 0;
    }
    if (l == tl && r == tr){
        return t[v];
    }
    int tm = (tl+tr)/2;
    return max(gm(v*2, tl, tm, l, min(r,tm)),gm(v*2+1, tm+1, tr, max(l,tm+1), r));
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n; int a[n];
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    bld(a,1,0,n-1);
    cin >> m;
    for (int i = 0; i < m; i++){
        int w; ll h;
        cin >> w >> h; w--;
        ll x = gm(1,0,n-1,0,w);
        cout << x << "\n";
        upd(1,0,n-1,w,x+h);
        upd(1,0,n-1,0,x+h);
    }
}

