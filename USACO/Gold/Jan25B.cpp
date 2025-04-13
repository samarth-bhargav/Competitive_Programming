#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m; cin >> n >> m;
    vector<bool> phantom(n);
    for (int i = 0; i < n; i++){
        char c; cin >> c;
        phantom[i] = c - '0';
    }
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++){
        int a, b; cin >> a >> b; a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    struct dsu{
        vector<int> p;
        vector<int> sz;
        int ans = 0;
        dsu (int n, vector<bool> phantom){
            p.resize(n); sz.resize(n);
            iota(p.begin(), p.end(), 0);
            for (int i = 0; i < n; i++){
                if (phantom[i]){
                    sz[i] = 0;
                }
                else{
                    sz[i] = 1;
                }
            }
        }
        int find(int x){
            return p[x] == x ? x : p[x] = find(p[x]);
        }
        void make_alive(int a){
            a = find(a);
            ans -= (sz[a] * (sz[a] - 1)) / 2;
            sz[a]++;
            ans += (sz[a] * (sz[a] - 1)) / 2;
        }
        void join(int a, int b){
            a = find(a); b = find(b);
            if (a == b){
                return;
            }
            ans -= (sz[a] * (sz[a] - 1)) / 2;
            ans -= (sz[b] * (sz[b] - 1)) / 2;
            sz[a] += sz[b];
            ans += (sz[a] * (sz[a] - 1)) / 2;
            p[b] = a;
        }
    };

    dsu d(n, phantom);

    for (int i = 0; i < n; i++){
        if (phantom[i]){
            for (int x : adj[i]){
                if (phantom[x]){
                    d.join(i, x);
                }
            }
        }
    }

    vector<int> answers;

    for (int i = n-1; i >= 0; i--){
        if (phantom[i]){
            d.make_alive(i);
        }
        else{
            for (int x : adj[i]){
                if (x > i || phantom[x]){
                    d.join(i, x);
                }
            }
        }
        answers.push_back(d.ans);
    }
    reverse(answers.begin(), answers.end());
    for (int x : answers){
        cout << x << "\n";
    }
}