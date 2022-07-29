#include <bits/stdc++.h>
using namespace std;

int main(){
    int n, k, m;
    cin >> n >> k >> m;
    vector<array<int,2>> p;
    for (int i = 0; i < k; i++){
        int a, b; cin >> a >> b; a--; b--;
        p.push_back({a,b});
    }
    vector<int> x(n);
    set<int> visited[n];
    for (int i = 0; i < n; i++){
        x[i] = i;
        visited[i].insert(i);
    }
    for (int i = 0; i < m; i++){
        int a = p[(i%k + k) % k][0];
        int b = p[(i%k + k) % k][1];
        visited[x[a]].insert(b);
        visited[x[b]].insert(a);
        swap(x[a], x[b]);
    }
    for (int i = 0; i < n; i++){
        cout << visited[i].size() << "\n";
    }
}