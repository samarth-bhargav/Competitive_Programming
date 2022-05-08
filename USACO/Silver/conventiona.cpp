/*
ID: samarth10
LANG: C++11
TASK: 
*/
#include <bits/stdc++.h>

using namespace std;

const int mxN = 1e5;
int ar[mxN];
int n,m,c;
bool ok(int x){
    int buses = 1;
    int currcnt = 1;
    int currloval = ar[0];
    for (int i = 1; i < n; i++){
        if (currcnt < c){
            if (ar[i] - currloval > x){
                buses++;
                currcnt = 1;
                currloval = ar[i];
            }
            else{
                currcnt++;
            }
        }
        else{
            buses++;
            currcnt = 1;
            currloval = ar[i];
        }
    }
    if (buses > m){
        return false;
    }
    return true;
}
int main(){
    freopen("convention.in", "r", stdin);
    freopen("convention.out", "w", stdout);
    cin >> n >> m >> c;
    for (int i = 0; i < n; i++){
        cin >> ar[i];
    }
    sort(ar, ar+n);
    int lo = 0, hi = 1e9;
    while (lo < hi){
        int mid = (lo+hi)/2;
        if (ok(mid)){
            hi = mid;
        }
        else{
            lo = mid+1;
        }
    }
//    ok(1);
    cout << lo << "\n";
}

