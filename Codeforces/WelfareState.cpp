/*
ID: samarth10
LANG: C++11
TASK: 
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    //setIO();
    int n;
    cin >> n;
    map <int,int> mp;
    for (int i = 1; i <= n; i++){
        int x;
        cin >> x;
        mp.insert(make_pair(i,x));
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++){
        int x;
        cin >> x;
        if (x == 1){
            int a,b;
            cin >> a >> b;
            mp[a] = b;
        }
        else{
            int a;
            cin >> a;
        }
    }
}

