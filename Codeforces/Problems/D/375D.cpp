#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct node{
    int color;
    int index;
    node (int color, int index){
        this->color = color;
        this->index = index;
    }
    node (){}
};

const int mxN = 1e5;
node nodes[mxN];
vector<node> adj[mxN];
unordered_map<int, vector<pair<int,int>>> qrs;


pair<map<int,int>, multiset<int>> merge(pair<map<int,int>, multiset<int>> a1, pair<map<int, int>, multiset<int>> a2){
    //merge a2 into a1
    if (a2.first.size() > a1.first.size()){
        swap(a1, a2);
    }
    for (auto &key : a2.first){
        int color = key.first;
        int val = key.second;
        if (a1.first.find(color) == a1.first.end()){
            a1.first.insert({color, 0});
            a1.second.insert(0);
        }
        a1.second.erase(a1.second.find(a1.first[color]));
        a1.first[color] += val;
        a1.second.insert(a1.first[color]);
    }
    return a1;
}

pair<map<int,int>, multiset<int>> subtree(node edge, node parent){
    pair<map<int,int>, multiset<int>> ret = {{edge.color, 1}, {1}};
    for (node child : adj[edge.index]){
        if (child.index != parent.index){
            ret = merge(ret, subtree(child, edge));
        }
    }
    if (qrs.find(edge.index) != qrs.end()){
        for (auto &qry : qrs[edge.index]){
            int kj = qry.first;

        }
    }
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n,m;
    cin >> n >> m;
    for (int i = 0; i < n; i++){
        int c; cin >> c;
        nodes[i] = node(c, i);
    }
    for (int i = 0; i < n-1; i++){
        int i1, i2;
        cin >> i1 >> i2; i1--; i2--;
        node a = nodes[i1], b = nodes[i2];
        adj[a.index].push_back(b);
        adj[b.index].push_back(a);
    }
    for (int i = 0; i < m; i++){
        int vj, kj;
        cin >> vj >> kj;
        qrs[vj].emplace_back(kj, i);
    }

}

