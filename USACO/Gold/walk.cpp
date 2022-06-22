// 10/15
#include <bits/stdc++.h>
using namespace std;

const int M = 2019201997;

struct edge{
    int dist;
    int x;
    int y;
    edge(int d, int a, int b){
        dist = d;
        x = a;
        y = b;
    }
    edge(){}
    bool operator <(const edge &o) const{
        return dist < o.dist;
    }
};

struct dsu{
    int n;
    vector<int> p;
    vector<int> sizes;
    void init(int sz){
        this->n = sz;
        for (int i = 0; i <= n; i++){
            p.push_back(i);
            sizes.push_back(1);
        }
    }
    int find(int a){
        return p[a] ^ a ? p[a] = find(p[a]) : a;
    }
    void join(int a, int b){
        a = find(a);
        b = find(b);
        if (a == b){
            return;
        }
        if (sizes[b] < sizes[a]){
            swap(a,b);
        }
        p[a] = b;
        sizes[b] += sizes[a];
        n--;
    }
    int size(){
        return n;
    }
};

int main(){
//    ifstream cin("walk.in");
//    ofstream cout("walk.out");
    int n,k;
    cin >> n >> k;
    priority_queue<edge> res;
    for (int i = 1; i <= n; i++){
        for (int j = i+1; j <= n; j++){
            res.push(edge(7*i+4*j, i, j));
        }
    }
    dsu d;
    d.init(n);
    edge t;
    while (d.n != k-1){
        t = res.top();
        int x = t.x;
        int y = t.y;
        d.join(x,y);
        res.pop();
    }
    cout << M - 12*t.dist << "\n";
}
