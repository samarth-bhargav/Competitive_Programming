#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;
vector<int> adj[mxN];

int dfs(int u, int v, int M){
    multiset<int> children;
    for (auto & edge : adj[u]){
        if (edge != v){
            int x = dfs(edge, u, M);
            if (x == -2){
                return -2;
            }
            children.insert(((x + 1)%M + M) % M);
        }
    }
    if (children.empty()){
        return 0;
    }
    if (children.find(-1) != children.end()){
        return -2;
    }
    children.erase(0);
    stack<int> alone;
    while (!children.empty()){
        int f = *children.begin();
        children.erase(children.begin());
        auto it = children.find(M - f);
        if (it == children.end()){
            alone.push(f);
            continue;
        }
        else{
            children.erase(it);
        }
    }
    if (alone.empty()){
        return 0;
    }
    return alone.size() == 1 ? alone.top() : -2;
}

int main(){
    ifstream cin("deleg.in");
    ofstream cout("deleg.out");
    int n;
    cin >> n;
    for (int i = 0; i < n-1; i++){
        int a, b;
        cin >> a >> b; a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> impossible;
    for (int k = 1; k < n; k++){
        if (k == 1){
            cout << 1;
        }
        else if ((n-1) % k != 0){
            cout << 0;
        }
        else{
            bool flag = false;
            for (int x : impossible){
                if (k % x == 0){
                    cout << 0;
                    flag = true;
                    break;
                }
            }
            if (flag){
                continue;
            }
            int res = dfs(0, -1, k);
            if (res != 0){
                impossible.push_back(k);
            }
            cout << (res == 0 ? 1 : 0);
        }
    }
}
