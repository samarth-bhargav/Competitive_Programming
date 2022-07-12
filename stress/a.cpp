#include <bits/stdc++.h>
using namespace std;

#define mp make_pair

const int mxN = 2e5+1;
vector<int> adj[mxN], groups[mxN];

struct dsu{
    vector<int> p;
    dsu(int sz){
        p.resize(sz+1);
        for (int i = 0; i < sz+1; i++){
            p[i] = i;
        }
    }
    dsu(){}
    int find(int x){
        return p[x]==x ? x : p[x] = find(p[x]);
    }
    void join(int a, int b){
        a = find(a);
        b = find(b);
        if (a == b){
            return;
        }
        p[a] = b;
    }
};

int main() {
    ifstream cin("fcolor.in");
    ofstream cout("fcolor.out");
    int n,m;
    cin >> n >> m;
    dsu d(n);
    for (int i = 0; i < m; i++){
        int a,b;
        cin >> a >> b; a--; b--;
        adj[a].push_back(b);
    }
    //adj[x] holds all the cows that admire x
    queue<int> q;
    for (int i = 0; i < n; i++){
        if (adj[i].size() > 1){
            q.push(i);
        }
    }
    vector<bool> visited(n, false);
    vector<int> temp, temp1;
    while (!q.empty()){
        int node = q.front();
        visited[node] = true;
        if (adj[node].size() <= 1){
            q.pop(); continue;
        }
        int best_color = 0, best_size = -1;
        for (int &cow : adj[node]){
            int x = d.find(cow);
            if ((int)adj[x].size() > best_size){
                best_color = x;
                best_size = adj[x].size();
            }
        }
        //now merge all the cows into best_color
        temp = adj[node];
        for (int cow : temp){
            int x = d.find(cow);
            if (x != best_color){
                d.join(cow, best_color);
                temp1 = adj[x];
                for (auto c : temp1){
                    adj[best_color].push_back(c);
                }
                while (!adj[x].empty()){
                    adj[x].pop_back();
                }
            }
        }
        if (adj[best_color].size() != best_size || !visited[node]){
            //we modified something :D
            q.push(best_color);
        }
//        cerr << "front: " << q.front() << "\n";
//        for (int i = 0; i < n; i++){
//            cerr << i << ": {";
//            for (int j = 0; j < (int)(adj[i].size())-1; j++){
//                cerr << adj[i][j] << ", ";
//            }
//            if (adj[i].size() != 0){
//                cerr << adj[i][adj[i].size()-1] << "} \n";
//            }
//            else{
//                cerr << "} \n";
//            }
//        }
        q.pop();
    }
    for (int i = 0; i < n; i++){
        for (int j = 1; j < (int)adj[i].size(); j++){
            d.join(adj[i][j], adj[i][j-1]);
        }
    }
    int cnt = 1;
    vector<int> group(n, -1), ans(n);
    for (int i = 0; i < n; i++){
        int grp = d.find(i);
        if (group[grp] == -1){
            ans[i] = cnt;
            group[grp] = cnt;
            cnt++;
        }
        else{
            ans[i] = group[grp];
        }
    }
    for (int &cow : ans){
        cout << cow << "\n";
    }
}
