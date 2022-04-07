/*
Author: treewave
orz
*/
#include <bits/stdc++.h>

using namespace std;

const int mxN = 1e5+5;
int n;

struct coordinate{
    int x,y,id;
};

vector <coordinate> ar(mxN);

struct dsu{
    int parent[mxN];
    void init(){
        for (int i = 1; i <= n; i++){
            parent[i] = i;
        }
    }
    int find(int a){
        return a==parent[a]?a:parent[a]=find(a);
    }
    void join(coordinate a, coordinate b){
        int l = find(a.id);
        int r = find(b.id);
        parent[l] = r;
    }
}ans;

bool cmp(coordinate a, coordinate b){
    if (a.x < b.x){
        return true;
    }
    else if (a.x == b.x){
        return a.y < b.y;
    }
    return false;
}

int main() {
    //setIO();
    cin >> n;
    for (int i = 1; i <= n; i++){
        int a,b;
        cin >> a >> b;
        coordinate x;x.x=a;x.y=b;x.id=i;
        ar[i] = x;
    }
    sort(ar.begin(),ar.end(),cmp);
    while (true){
        for (int i = 1; i < n; i++){
            if ()
        }
    }
}

