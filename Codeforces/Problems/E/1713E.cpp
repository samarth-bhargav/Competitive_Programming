#include <bits/stdc++.h>
using namespace std;

struct dsu{
    vector<int> p;
    vector<vector<int>> cc;
    int sz;
    dsu(int n){
        sz = n >> 1;
        p.resize(n);
        cc.resize(n);
        iota(p.begin(), p.end(), 0);
        for (int i = 0; i < n; i++){
            cc[i] = {i};
        }
    }
    int find(int x){
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    int conj(int x){
        return x >= sz ? x - sz : x + sz;
    }
    bool join(int a, int b){
        a = find(a); b = find(b);
        if (a == b) return true;
        if (cc[a].size() < cc[b].size()) swap(a,b);
        for (int elem : cc[b]){
            if (find(conj(elem)) == a){
                return false;
            }
        }
        for (int elem : cc[b]){
            cc[a].push_back(elem);
        }
        cc[b].clear();
        cc[b].shrink_to_fit();
        p[b] = a;
        return true;
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<vector<int>> a(n, vector<int>(n));
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                cin >> a[i][j];
            }
        }
        dsu d(2 * n);
        bool works[n][n];
        memset(works, 0, sizeof(works));
        for (int i = 0; i < n; i++){
            for (int j = i+1; j < n; j++){
                if (a[i][j] < a[j][i]){
                    if (d.join(i, j) && d.join(d.conj(i), d.conj(j))){
                        works[i][j] = true;
                    }
                }
                else if (a[i][j] > a[j][i]){
                    if (d.join(i, d.conj(j)) && d.join(d.conj(i), j)){
                        works[i][j] = true;
                    }
                }
            }
        }
        for (int i = 0; i < n; i++){
            for (int j = i+1; j < n; j++){
                if (works[i][j]){
                    if (a[i][j] > a[j][i]) swap(a[i][j], a[j][i]);
                }
                else{
                    if (a[i][j] < a[j][i]) swap(a[i][j], a[j][i]);
                }
            }
        }
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                cout << a[i][j] << " ";
            }
            cout << "\n";
        }
    }
}