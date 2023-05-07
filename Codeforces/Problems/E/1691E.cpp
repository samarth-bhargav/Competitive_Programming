#include <bits/stdc++.h>
using namespace std;

struct dsu{
    vector<int> p; int sz;
    dsu(int n){
        this->sz = n;
        p.resize(n);
        iota(p.begin(), p.end(), 0);
    }
    int find(int x){
        return x==p[x] ? x : p[x] = find(p[x]);
    }
    bool join(int x, int y){
        x = find(x);
        y = find(y);
        if (x == y){
            return false;
        }
        p[x] = y;
        return true;
    }
};


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--){
        int n; cin >> n;
        vector<array<int, 3>> segments(n);
        map<int, int> l;
        for (int i = 0; i < n; i++){
            cin >> segments[i][0] >> segments[i][1] >> segments[i][2];
            l[i] = segments[i][1];
        }
        set<array<int, 4>> pts; //pos, start(0)/end(1), red(0)/blue(1), start(0)/end(1)
        for (int i = 0; i < n; i++){
            pts.insert({segments[i][1], 0, segments[i][0], i});
            pts.insert({segments[i][2], 1, segments[i][0], i});
        }
        set<pair<int,int>> active_red, active_blue;
        dsu d(n);
        for (array<int, 4> pt : pts){
            if (pt[1] == 1){
                if (pt[2] == 0) active_red.erase({l[pt[3]], pt[3]});
                else active_blue.erase({l[pt[3]], pt[3]});
            }
            else{
                if (pt[2] == 0){
                    if (active_blue.empty()){
                        active_red.insert({pt[0], pt[3]});
                        continue;
                    }
                    d.join(prev(active_blue.end())->second, pt[3]);
                    for (auto it = prev(active_blue.end()); it != active_blue.begin(); it--){
                        if (!d.join(it->second, prev(it)->second)){
                            break;
                        }
                    }
                    active_red.insert({pt[0], pt[3]});
                }
                else{
                    if (active_red.empty()){
                        active_blue.insert({pt[0], pt[3]});
                        continue;
                    }
                    d.join(prev(active_red.end())->second, pt[3]);
                    for (auto it = prev(active_red.end()); it != active_red.begin(); it--){
                        if (!d.join(it->second, prev(it)->second)){
                            break;
                        }
                    }
                    active_blue.insert({pt[0], pt[3]});
                }
            }
        }
        set<int> roots;
        for (int i = 0; i < n; i++){
            roots.insert(d.find(i));
        }
        cout << roots.size() << "\n";
    }
}
