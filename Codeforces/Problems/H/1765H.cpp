#include <bits/stdc++.h>
using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    vector<int> p(n);
    vector<int> to_add[n];
    for (int i = 0; i < n; i++){
        cin >> p[i]; p[i]--;
        to_add[p[i]].push_back(i);
    }
    vector<int> deg(n, 0), original_deg(n);
    set<int> adj[n];
    for (int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b; a--; b--;
        adj[b].insert(a);
        deg[a]++;
    }
    original_deg = deg;
    for (int i = 0; i < n; i++){
        priority_queue<pair<int,int>> pq; //(max time, node)
        int ans = -1;
        for (int j = n-1; j >= 0; j--){
            for (int x : to_add[j]){
                if (deg[x] == 0 && x != i){
                    pq.push({p[x], x});
                }
            }
            if (pq.empty()){
                ans = j; break;
            }
            pair<int,int> tp = pq.top();
            pq.pop();
            for (int k : adj[tp.second]){
                deg[k]--;
                if (deg[k] == 0 && k != i && p[k] >= j){
                    pq.push({p[k], k});
                }
            }
        }
        cout << ans+1 << " ";
        deg = original_deg;
    }
    cout << "\n";
}