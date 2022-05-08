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

bool compare(int a, int b){
    if (a > b){
        return true;
    }
    return false;
}

int main() {
    setIO("lemonade");
    int t;
    cin >> t;
    int ar[t];
    for (int i = 0; i < t; i++){
        cin >> ar[i];
    }
    sort(ar, ar+t, compare);
    int cnt = 0;
    for (int i = 0; i < t; i++){
        if (ar[cnt] < cnt){
            break;
        }
        else{
            cnt ++;
        }
    }
    cout << cnt << "\n";
}

