#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e4+5;
int n,tmax;
int ar[mxN];

bool ok(int k){
    int tm = 0, pos=k;
    priority_queue<int,vector<int>,greater<int>>pq;
    for (int i = 0; i < k; i++){
        pq.push(ar[i]);
    }
    while (pos < n){
        int x = pq.top();
        pq.pop();
        pq.push(x+ar[pos]);
        pos++;
    }
    while (!pq.empty()){
        tm = pq.top();
        pq.pop();
    }
    return tm<=tmax;
}

int main(){
    ifstream cin("cowdance.in");
    ofstream cout("cowdance.out");
    cin >> n >> tmax;
    for (int i = 0; i < n; i++){
        cin >> ar[i];
    }
    int lo = 1;
    int hi = n;
    while (hi-lo > 1){
        int mid = (lo+hi)/2;
        if (ok(mid)){
            hi = mid;
        }
        else{
            lo = mid+1;
        }
    }
    cout << (ok(lo)?lo:hi) << "\n";
}