/*
Author: treewave
orz
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    //setIO();
    int n;
    cin >> n;
    vector<int>ar(n);
    for (auto & i : ar){
        cin >> i;
    }
    sort(ar.begin(), ar.end());
    int ma = 0, mi = INT_MAX;
    int val1 = 0, val2 = 0;
    for (int i = 2; i < ar.size(); i++){
        val1 += ar[i]-ar[i-1]-1;
    }
    for (int i = 1; i < ar.size()-1; i++){
        val2 += ar[i]-ar[i-1]-1;
    }
    ma = max(val1,val2);
    cerr << ma << "\n";
    for (auto & i : ar){
        int lo = i;
        int hi = i+n-1;
        if (lower_bound(ar.begin(),ar.end(),hi)==ar.end() || (lower_bound(ar.begin(),ar.end(),hi) == ar.begin() && !binary_search(ar.begin(),ar.end(),hi))){
            break;
        }
        auto it = binary_search(ar.begin(),ar.end(),hi)?lower_bound(ar.begin(),ar.end(),hi):prev(lower_bound(ar.begin(),ar.end(),hi));
        int numelements = it-lower_bound(ar.begin(),ar.end(),lo)+1;
        if (numelements == n-1){
            mi = min(mi,2);
            continue;
        }
        mi = min(mi,n-numelements);
    }
    for (int i = ar.size()-1; i >= 0; i--){
        int lo = ar[i]-n+1;
        int hi = ar[i];
        if (lower_bound(ar.begin(),ar.end(),lo) == ar.end()){
            break;
        }
        auto it = lower_bound(ar.begin(),ar.end(),lo);
        int numelements = lower_bound(ar.begin(),ar.end(),hi)-it+1;
        if (numelements == n-1){
            mi = min(mi,2);
            continue;
        }
        mi = min(mi,n-numelements);
    }
    cerr << mi << "\n";
}

