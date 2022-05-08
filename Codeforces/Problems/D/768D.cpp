#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int k, q, x;

bool check(int mid){
    double val = (pow(k, mid) - k * pow(k-1, mid)) / (pow(k, mid) + 0.0);
    cerr << val << "\n";
    return val >= ((x + 0.0) / 2000);
}

int binary_search(){
    int lo = k;
    int hi = 1e9;
    while (lo < hi - 1){
        int mid = (lo + hi) / 2;
        if (check(mid)){
            hi = mid;
        }
        else{
            lo = mid;
        }
    }
    //lo = hi-1
    if (check(lo)){
        return lo;
    }
    return hi;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> k >> q;
    for (int i = 0; i < q; i++){
        cin >> x;
        if (k == 1){
            cout << 1 << "\n";
            continue;
        }
        cout << ceil((log((2000-x+0.0)/2000) - log(k) - 1e-7) / (log(k-1) - log(k))) << "\n";
    }
}

