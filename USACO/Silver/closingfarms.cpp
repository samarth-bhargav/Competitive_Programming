/*
Author: treewave
orz
*/
#include <bits/stdc++.h>

using namespace std;

const int mxN = 2e5+3;
vector <int> adj[mxN], order(mxN), answers;
set <int> active;
int n,m;

class dsu{
    int parent[mxN];
    public:
        void init(){
            for (int i = 1; i <= n; i++){
                parent[i] = i;
            }
        }
        void join(int a, int b){
            int c = find(a);
            int d = find(b);
            parent[c] = d;
        }
        bool is_connected(){
            int init = find(*active.begin());
            for (auto & i : active){
                if (find(i) != init){
                    return false;
                }
            }
            return true;
        }
    private:
        int find(int a){
            if (parent[a] == a){
                return a;
            }
            return parent[a] = find(parent[a]);
        }
}d;

int main() {
    ifstream cin("closing.in");
    ofstream cout("closing.out");
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < m; i++){
        int a,b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    d.init();
    order.resize(n);
    for (int i = n-1; i >= 0; i--){
        cin >> order[i];
    }
    for (int i = 0; i < n; i++){
        if (active.empty()){
            answers.push_back(1);
            active.insert(order[i]);
            continue;
        }
        for (auto & x : adj[order[i]]){
            if (active.find(x) != active.end()){
                d.join(x,order[i]);
            }
        }
        active.insert(order[i]);
        answers.push_back(d.is_connected()?1:0);
    }
    for (int i = answers.size()-1; i >= 0; i--){
        cout << (answers[i] == 1 ? "YES" : "NO") << "\n";
    }
}

