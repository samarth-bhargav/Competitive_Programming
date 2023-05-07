#include <bits/stdc++.h>
using namespace std;

const int mxN = 6e3;
typedef long long ll;
vector<int> adj0[mxN], adj2[mxN];

struct dsu{
    vector<int> p;
    vector<int> sz;
    dsu (int n){
        p.resize(n);
        iota(p.begin(), p.end(), 0);
        sz.resize(n);
        fill(sz.begin(), sz.end(), 1);
    }
    int find(int x){
        return x == p[x] ? x : p[x] = find(p[x]);
    }
    bool join(int a, int b){
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz[a] > sz[b]) swap(a, b);
        p[a] = b;
        sz[b] += sz[a];
        return true;
    }
};

int bndry(array<int, 2> a, array<int, 2> b){
    int slpx = b[1] - a[1], slpy = b[0] - a[0];
    if (slpx == 0) return abs(slpy);
    else if (slpy == 0) return abs(slpx);
    int gcd = __gcd(abs(slpx), abs(slpy));
    slpx /= gcd; slpy /= gcd;
    return min(abs((b[0] - a[0]) / slpy), abs((b[1] - a[1]) / slpx));
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    vector<array<int, 2>> pts(n);
    for (int i = 0; i < n; i++){
        cin >> pts[i][0] >> pts[i][1];
    }
    int num_0 = 0;
    vector<array<int, 2>> edges_2, edges_0;
    for (int i = 0; i < n; i++){
        for (int j = i+1; j < n; j++){
            if (bndry(pts[i], pts[j]) % 4 == 0){
                edges_0.push_back({i, j});
                num_0++;
            }
            else{
                edges_2.push_back({i, j});
            }
        }
    }
    dsu d1(n), d2(n);
    for (array<int, 2> edge : edges_0){
        if (d1.join(edge[0], edge[1])){
            adj0[edge[0]].push_back(edge[1]);
            adj0[edge[1]].push_back(edge[0]);
        }
    }
    for (array<int, 2> edge : edges_2){
        if (d2.join(edge[0], edge[1])){
            adj2[edge[0]].push_back(edge[1]);
            adj2[edge[1]].push_back(edge[0]);
        }
    }
    ll num_000 = num_0 * (n - 2);
    ll ans = num_0 * (n - 2);
    //basically counting num_2 = 1, num_0 = 2
    for (array<int, 2> edge : edges_2){
        int comp = (n - (adj2[edge[0]].size() + adj2[edge[1]].size()));
        ans -= comp;
        num_000 -= comp;
    }
    //basically counting num_2 = 2, num_1 = 1
    for (array<int, 2> edge : edges_0){
        int comp = (n - (adj0[edge[0]].size() + adj0[edge[1]].size()));
        num_000 -= comp;
    }
    cout << ans - 2 * (num_000) / 3 << "\n";

//    for (int i = 0; i < n; i++){
//        for (int j = i+1; j < n; j++){
//            for (int k = j+1; k < n; k++){
//                cout << "Triangle: " << i << " " << j << " " << k << " Boundaries: " << bnd[i][j] << " " << bnd[j][k] << " " << bnd[i][k] << "\n";
//            }
//        }
//    }

}
