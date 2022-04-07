/*
ID: samarth10
LANG: C++11
TASK: 
*/
#include <bits/stdc++.h>

using namespace std;


void setIO(string name) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen((name + ".in").c_str(), "r", stdin);
    freopen((name + ".out").c_str(), "w", stdout);
}
struct cow{
    int id;
    int pos;
};
bool compare(cow a, cow b){
    if (a.id > b.id){
        return true;
    }
    else if(a.id == b.id){
        return a.pos < b.pos;
    }
    return false;
}
int main() {
    setIO("proximity");
    int n,k;
    cin >> n >> k;
    cow ar[n];
    for (int i = 0; i < n; i++){
        cin >> ar[i].id;
        ar[i].pos = i;
    }
    sort(ar, ar+n, compare);
    for (int i = 0; i < n; ++i){
        if (ar[i].id == ar[i+1].id){
            if (ar[i+1].pos - ar[i].pos <= k){
                cout << ar[i].id << "\n";
                break;
            }
        }
        else{
            continue;
        }
    }
}

