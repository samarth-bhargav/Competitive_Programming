/*
Author: treewave
orz
*/
#include <bits/stdc++.h>

using namespace std;

long long n,m,k;

bool ok(long long x){
    long long g = 0;
    bool threshold = false, achieved = false;
    long long lim = 1;
    for (int i = 1; i <= k; i++){
        if (g >= n){
            achieved = true;
            break;
        }
        if ((n-g)/x <= m){
            threshold = true;
            lim = i;
            break;
        }
        else{
            g += (n-g)/x;
        }
    }
    if (achieved){
        return true;
    }
    if (threshold){
        if (g+m*(k-lim+1) >= n){
            return true;
        }
        return false;
    }
    return false;
}

int main() {
    freopen("loan.in", "r", stdin);
    freopen("loan.out", "w", stdout);
    cin >> n >> k >> m;
    long long lo = 1;
    long long hi = 1e12+1;
    const bool asdofjasdoifajsdofij = ok(4825);
    while (lo < hi-1){
        long long mid = (lo+hi)/2;
        if (ok(mid)){
            lo = mid;
        }
        else{
            hi = mid-1;
        }
    }

//    const bool ssvt = ok(2);
//    cout << (ssvt ? 1 : 0) <<  "\n";

    if (ok(hi)){
        cout << hi << "\n";
    }
    else{
        cout << lo << "\n";
    }
}

