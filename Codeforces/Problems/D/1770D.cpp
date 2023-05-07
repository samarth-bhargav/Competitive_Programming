#include <bits/stdc++.h>
using namespace std;

#define int long long
const int M = 998244353;

struct dsu{
    vector<int> p, sz, edges;
    vector<bool> self_loop;
    int n;
    dsu(int n){
        this->n = n;
        p.resize(n);
        sz.resize(n, 1);
        edges.resize(n, 0);
        self_loop.resize(n, 0);
        iota(p.begin(), p.end(), 0);
    }
    int find(int x){
        return x==p[x] ? x : p[x] = find(p[x]);
    }
    void join(int a, int b){
        if (a == b){
            self_loop[find(a)] = 1;
            edges[find(a)]++;
            return;
        }
        a = find(a);
        b = find(b);
        if (a == b){
            edges[a]++;
            return;
        }
        self_loop[a] = (self_loop[a] | self_loop[b]);
        edges[a] += edges[b];
        edges[a]++;
        sz[a] += sz[b];
        p[b] = a;
    }
};

int32_t main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--){
        int n;
        cin >> n;
        vector<int> a(n), b(n);
        dsu d(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];
            a[i]--;
        }
        for (int i = 0; i < n; i++){
            cin >> b[i];
            b[i]--;
            d.join(a[i], b[i]);
        }
        bool bad = false;
        int ans = 1;
        set<int> roots;
        for (int i = 0; i < n; i++){
            //checking if each cc is ok
            if (d.edges[d.find(i)] != d.sz[d.find(i)]){
                bad = true;
                break;
            }
            roots.insert(d.find(i));
        }
        if (bad){
//            cerr << "hi\n";
            cout << 0 << "\n";
            continue;
        }
        for (int root : roots){
            if (d.sz[root] == 1){
                ans = ((ans * n) % M + M) % M;
            }
            else{
                if (!d.self_loop[root]){
                    ans = ((ans * 2) % M + M) % M;
                }
                else{
                    ans = ((ans * n) % M + M) % M;
                }
            }
        }
        cout << (ans % M + M) % M << "\n";
    }
}
