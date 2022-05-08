/*
Author: treewave
orz
*/
#include <bits/stdc++.h>

using namespace std;

bool ok(int x, int y){
    return ((x*(x+1))/2 >= y);
}
int main(){
    //setIO();
    int t;
    cin >> t;
    while (t--){
        int x;
        cin >> x;
        int lo = 1;
        int hi = 1e4;
        while (hi-lo>1){
            int mid = (lo+hi)/2;
            if (ok(mid,x)){
                hi = mid;
            }
            else{
                lo = mid+1;
            }
        }
        int ret;
        if (ok(lo,x)) ret = lo;
        else ret = hi;
        int diff = (ret*(ret+1))/2 - x;
        cout << (diff == 1 ? ret+1 : ret) << "\n";
    }
}

