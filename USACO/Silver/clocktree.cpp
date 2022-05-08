#include <bits/stdc++.h>

using namespace std;

const int mxN = 2.5e3+5;
vector <int> adj[mxN];
int n,currtime[mxN],cpy[mxN];

//dfs returns number of times needed to be incremented
int dfs(int e, int a, int init){
    //base case for recursion
    e != init ? currtime[e] = (currtime[e]+1)%12 : e;
    if (adj[e].size() == 1 && e != init){
        return currtime[e];
    }
    for (auto & i : adj[e]){
        if (i != a){
            currtime[e] = (currtime[e] + (12-dfs(i,e,init)))%12;
            currtime[e] = (currtime[e]+1)%12;
        }
    }
    return currtime[e];
}

int main() {
    freopen("clocktree.in", "r", stdin);
    freopen("clocktree.out", "w", stdout);
    cin >> n;
    for (int i = 1; i <= n; i++){
        cin >> currtime[i];
        cpy[i] = currtime[i];
    }
    for (int i = 0; i < n-1; i++){
        int a,b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    int ans = 0;
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            currtime[j] = cpy[j];
        }
        int x = dfs(i,0,i);
        if (x == 0 || x == 1){
            cerr << i << "\n";
            ans++;
        }
    }
    cout << ans << "\n";
}

