/*
Author: treewave
orz
*/
#include <bits/stdc++.h>

using namespace std;

int n, x, y;
bool ok(int a){
    return (a/x + a/y >= n-1);
}
int main() {
    cin >> n >> x >> y;
    long long lo = min(x,y);
    long long hi = 1e9;
    const bool hello = ok(3 );
    if (n == 1){
        cout << min(x,y) << "\n";
        return 0;
    }
    while (lo < hi-1){
        int mid = (lo+hi)/2;
        if (ok(mid)){
            hi = mid;
        }
        else{
            lo = mid+1;
        }
    }
    if (ok(lo)){
        cout << lo+min(x,y) << "\n";
    }
    else{
        cout << hi+min(x,y) << "\n";
    }
}

