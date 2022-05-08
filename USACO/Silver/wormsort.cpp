/*
Author: treewave
orz
*/
#include <bits/stdc++.h>

using namespace std;

const int mxN = 1e5+5;
int n,m;
vector<pair<pair<int,int>,int>>wormholes;
int loc[mxN];

struct dsu{
    int parent[mxN];
    void init(){
        for (int i = 1; i <= n; i++){
            parent[i] = i;
        }
    }
    int find(int x){
        return parent[x]^x?parent[x]=find(parent[x]):x;
    }
    void join(int a, int b){
        int c = find(a);
        int d = find(b);
        parent[c] = d;
    }
};

bool ok(int x){
    dsu d;
    d.init();
    for (auto & i : wormholes){
        if (i.second >= x){
            d.join(i.first.first,i.first.second);
        }
    }
    for (int i = 1; i <= n; i++){
        int l = loc[d.parent[i]];
        if (d.find(l) != d.find(i)){
            return false;
        }
    }
    return true;
}

int main() {
    ifstream cin("wormsort.in");
    ofstream cout("wormsort.out");
    cin >> n >> m;
    for (int i = 1; i <= n; i++){
        cin >> loc[i];
    }
    if (is_sorted(loc+1,loc+n+1)){
        cout << -1 << "\n";
        return 0;
    }
    for (int i = 0; i < m; i++){
        int a,b,c;
        cin >> a >> b >> c;
        wormholes.push_back({{a,b},c});
    }
    int lo = 0;
    int hi = 1e9;
    while (hi-lo > 1){
        int mid = (lo+hi)/2;
        if (ok(mid)){
            lo = mid;
        }
        else{
            hi = mid-1;
        }
    }
    cout << (ok(hi)?hi:lo) << "\n";
}

