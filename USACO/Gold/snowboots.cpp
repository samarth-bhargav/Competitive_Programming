#include <bits/stdc++.h>

using namespace std;

struct boot{
    int id;
    int depth;
    int step;
    bool poss;
    bool operator <(const boot &o) const{
        return this->depth > o.depth;
    }
};
struct snow{
    int id;
    int depth;
    bool operator <(const snow &o) const{
        return this->depth < o.depth;
    }
};
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,b;
    cin >> n >> b;
    snow depths[n];
    int nxt[n],pre[n],curr[n];
    boot boots[b];
    for (int i = 0; i < n; i++){
        cin >> depths[i].depth;
        depths[i].id = i;
        curr[i] = depths[i].depth;
        if (i != 0){
            pre[i] = depths[i-1].id;
        }
    }
    for (int i = 0; i < b; i++){
       cin >> boots[i].depth >> boots[i].step;
       boots[i].id = i;
    }
    for (int i = 0; i < n-1; i++){
        nxt[i] = depths[i+1].id;
    }
    sort(boots,boots+n);
    sort(depths,depths+n);
    int sz = n-1;
    int max_gap = 1;
    for (int i = 0; i < b; i++){
        while (depths[sz].depth > boots[i].depth && sz > -1){
            max_gap = max(max_gap,nxt[depths[sz].id]-pre[depths[sz].id]);
            if (depths[sz].id > 0){
                nxt[depths[sz].id-1] = depths[sz].id+1;
            }
            if (depths[sz].id < sz-1){
                pre[depths[sz].id+1] = depths[sz].id-1;
            }
            sz--;
        }
        boots[i].poss = (max_gap <= boots[i].step);
    }
    bool ans[b];
    for (int i = 0; i < b; i++){
        ans[boots[i].id] = boots[i].poss;
    }
    for (int i = 0; i < b; i++){
        cout << ans[i] << "\n";
    }
}

