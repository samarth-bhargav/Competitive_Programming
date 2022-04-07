#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int mxN = 2e5;

struct dsu{
    vector<int> p;
    void init(int n){
        p.resize(n);
        for (int i = 0; i < n; i++){
            p[i] = i;
        }
    }
    int find(int x){
        return (p[x] == x ? x : p[x] = find(p[x]));
    }
    void join(int a, int b){
        a = find(a);
        b = find(b);
        p[a] = b;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    dsu d; d.init(n);
    vector<int> nodes(n);
    for (int i = 0; i < n; i++){
        cin >> nodes[i];
    }
    for (int i = 0; i < n-1; i++){
        int u, v;
        cin >> u >> v; u--; v--;
        if (nodes[u] == nodes[v]){
            d.join(u, v);
        }
    }
//    for (int i = 0; i < n; i++){
//        cerr << d.find(i) << "\n";
//    }
    set<int> parents;
    for (int i = 0; i < n; i++){
        if (parents.find(d.find(i)) == parents.end()){
            parents.insert(d.find(i));
        }
    }
    int black = 0, white = 0;
    for (int p : parents){
        if (nodes[p] == 0){
            white++;
        }
        else{
            black++;
        }
    }
    cout << min(white, black) << "\n";
}

