#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--){
        int n, m;
        cin >> n >> m;
        vector<int> adj[n];
        for (int i = 0; i < m; i++){
            int a, b;
            cin >> a >> b; a--; b--;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        int f; cin >> f;
        vector<int> friends(f);
        for (int i = 0; i < f; i++){
            cin >> friends[i];
            friends[i]--;
        }
        int k; cin >> k;
        vector<int> no_car(k);
        map<int, int> house_no_car;
        for (int i = 0; i < k; i++){
            cin >> no_car[i]; no_car[i]--;
            if (house_no_car.find(friends[no_car[i]]) == house_no_car.end()){
                house_no_car[friends[no_car[i]]] = (1 << i);
            }
            else{
                house_no_car[friends[no_car[i]]] |= (1 << i);
            }
        }
        queue<array<int, 2>> bfs; bfs.push({0, 0}); //node, depth
        vector<int> visited(n, -1);
        vector<unordered_set<int>> poss(n, unordered_set<int>(0));
        while (!bfs.empty()){
            int node = bfs.front()[0];
            int depth = bfs.front()[1];
            bfs.pop();
            if (visited[node] != -1 && visited[node] < depth){
                continue;
            }
            visited[node] = depth;
            for (auto v : adj[node]){
//                if (v == 5){
//                    cerr << "hi\n";
//                }
                if (visited[v] == -1 || visited[v] == depth+1){
                    if (visited[v] == -1){
                        bfs.push({v, depth+1});
                    }
                    visited[v] = depth+1;
                    int curr = 0;
                    if (house_no_car.find(v) != house_no_car.end()){
                        curr = house_no_car[v];
                    }
                    if (poss[node].empty()){
                        poss[v].insert(curr);
                    }
                    for (int possible : poss[node]){
                        poss[v].insert(possible | curr);
                    }
                }
            }
        }
//        for (int i = 0; i < n; i++){
//            cout << i+1 << " ";
//            for (int x : poss[i]){
//                cout << bitset<6>(x) << " ";
//            }
//            cout << "\n";
//        }
        bool dp[1 << k];
        memset(dp, false, sizeof(dp)); dp[0] = true;
        for (int i = 0; i < f; i++){
            if (find(no_car.begin(), no_car.end(), i) == no_car.end()){
                for (int j = (1 << k)-1; ~j; j--){
                    if (dp[j]){
                        for (int l : poss[friends[i]]){
                            dp[j | l] = true;
                        }
                    }
                }
            }
        }
        int ans = k;
        for (int i = 0; i < (1 << k); i++){
            if (dp[i]){
                ans = min(ans, k - __builtin_popcount(i));
            }
        }
        cout << ans << "\n";
    }
}
