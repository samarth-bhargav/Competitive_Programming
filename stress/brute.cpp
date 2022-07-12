#include <bits/stdc++.h>
using namespace std;

struct dsu{
    vector<int> p;
    dsu(int sz){
        p.resize(sz+1);
        for (int i = 0; i < sz+1; i++){
            p[i] = i;
        }
    }
    dsu(){}
    int find(int x){
        return p[x]==x ? x : p[x] = find(p[x]);
    }
    void join(int a, int b){
        a = find(a);
        b = find(b);
        if (a == b){
            return;
        }
        p[a] = b;
    }
};


int main(){
    int n, m;
    cin >> n >> m;
    dsu d(n);
    vector<pair<int,int>> edges;
    for (int i = 0; i < m; i++){
        int a,b;
        cin >> a >> b; a--; b--;
        edges.emplace_back(a,b);
    }
    auto it1 = unique(edges.begin(), edges.end());
    edges.resize(distance(edges.begin(), it1));
    while (true){
        bool flag = false;
        auto it = unique(edges.begin(), edges.end());
        edges.resize(distance(edges.begin(), it));
        for (int i = 0; i < edges.size(); i++){
            for (int j = i+1; j < edges.size(); j++){
                if (d.find(edges[i].first) == d.find(edges[j].first)){
                    flag = true;
                    int x = edges[i].second;
                    int y = edges[j].second;
                    for (int k = 0; k < edges.size(); k++){
                        if (d.find(edges[k].first) == y){
                            edges[k].first = x;
                        }
                        if (d.find(edges[k].second) == y){
                            edges[k].second = x;
                        }
                    }
                    d.join(x,y);
                    edges.erase(edges.begin() + j);
                    auto it2 = unique(edges.begin(), edges.end());
                    edges.resize(distance(edges.begin(), it2));
                }
                auto it3 = unique(edges.begin(), edges.end());
                edges.resize(distance(edges.begin(), it3));
            }
        }
        if (!flag){
            break;
        }
    }
    int cnt = 1;
    vector<int> group(n, -1), ans(n);
    for (int i = 0; i < n; i++){
        int grp = d.find(i);
        if (group[grp] == -1){
            ans[i] = cnt;
            group[grp] = cnt;
            cnt++;
        }
        else{
            ans[i] = group[grp];
        }
    }
    for (int &cow : ans){
        cout << cow << "\n";
    }
}
