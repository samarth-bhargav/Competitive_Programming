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
int n,q,k;
int main() {
    //setIO();
    cin >> n >> k >> q;
    int ar[200005] = {0};
    for (int i = 0; i < n; i++){
        int x,y;
        cin >> x >> y;
        ar[x]++; ar[y+1]--;
    }
    for (int i = 1; i < 200005; i++){
        ar[i] = ar[i-1] + ar[i];
    }
    for (int & i : ar){
        if (i >= k){
            i = 1;
        }
        else{
            i = 0;
        }
    }
    for (int i = 1; i < 200005; i++){
        ar[i] = ar[i-1] + ar[i];
    }
    while (q--){
        int a,b;
        cin >> a >> b;
        cout << ar[b] - ar[a-1] << "\n";
    }
}

