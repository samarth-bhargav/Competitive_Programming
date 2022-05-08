/*
Leaves From the Vine
Falling so Slow

Like Fragile Tiny Shells
Drifting in the Foam

Little Soldier Boy
Come Marching Home

Brave Soldier Boy
Come Back Home
*/

#include <bits/stdc++.h>
using namespace std;

long long n,k;
bool ok(long long x){
    return ((k)*(k+1)/2-(k-1) - (x)*(x+1)/2 >= n ? 1 : 0);
}

int main(){
    cin >> n >> k;
    if (k*(k+1)/2-(k-1) < n){
        cout << -1 << "\n";
    }
    else{
        long long lo = 0;
        long long hi = 1e9;
        while (hi-lo > 1){
            long long mid = (lo+hi)/2;
            if (ok(mid)){
                lo = mid;
            }
            else{
                hi = mid-1;
            }
        }
        if (ok(hi)){
            lo = hi;
        }
        cout << k-lo-1 << "\n";
    }
    return EXIT_SUCCESS;
}