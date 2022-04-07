/*
Author: treewave
orz
*/
#include <bits/stdc++.h>

using namespace std;

struct person{
    int id;
    int tme;
    int lim;
    int rest;
};

person ar[1005];

int n,m;

bool ok(int t){
    int cnt = 0;
    int h = m;
    for (int i = 0; i < n; i++){
        int rem = ar[i].tme * ar[i].lim + ar[i].rest;
        if (rem >= t){
            cnt += min(min(ar[i].lim,t/ar[i].tme),h);
            h -= min((min(ar[i].lim,t/ar[i].tme)),h);
            continue;
        }
        cnt += min((t/rem)*(ar[i].lim)+ min((((t%rem)+rem)%rem / ar[i].tme),ar[i].lim),h);
        h -= min(((t/rem)*(ar[i].lim)+ min((((t%rem)+rem)%rem / ar[i].tme),ar[i].lim)),h);
    }
    return cnt >= m;
}

int main() {
    //setIO();
    cin >> m >> n;
    for (int i = 0; i < n; i++){
        cin >> ar[i].tme >> ar[i].lim >> ar[i].rest;
        ar[i].id = i;
    }
    int lo = 0;
    int hi = 1e9;
    ok(2414);
    while (hi-lo > 1){
        int mid = (lo+hi)/2;
        if (ok(mid)){
            hi = mid;
        }
        else{
            lo = mid+1;
        }
    }
    if (ok(lo)){
        cout << lo << "\n";
    }
    else{
        lo = hi;
        cout << lo << "\n";
    }
    for (int i = 0; i < n; i++){
        int rem = ar[i].tme * ar[i].lim + ar[i].rest;
        if (rem >= lo){
            cout << min(min(ar[i].lim,lo/ar[i].tme),m) << " ";
            m -= min(min(ar[i].lim,lo/ar[i].tme),m);
            continue;
        }
        cout << min((lo/rem)*(ar[i].lim)+min((((lo%rem)+rem)%rem) / ar[i].tme, ar[i].lim),m) << " ";
        m -=min(((lo/rem)*(ar[i].lim)+ min((((lo%rem)+rem)%rem) / ar[i].tme, ar[i].lim)),m);
    }
    cout << "\n";
}

