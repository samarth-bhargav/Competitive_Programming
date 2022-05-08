/*
Author: treewave
orz
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--){
        int n,q;
        cin >> n >> q;
        vector<int>ar(n);
        for (int i = 0; i < n; i++){
            cin >> ar[i];
        }
        vector<long long>pref(n+1);
        int init = (ar[0]+ar[n-1]/2);
        sort(ar.begin(),ar.end());
        pref[0] = 0;
        for (int i = 1; i <= n; i++){
            pref[i] = pref[i-1] + ar[i-1];
        }
        for (int i = 0; i < q; i++){
            int x;
            cin >> x;
            int lo = 0;
            int hi = n-1; //inclusive
            bool ok = false;
            int it = lower_bound(ar.begin(),ar.end(),init)-ar.begin()-binary_search(ar.begin(),ar.end(),init);
            while (lo != hi){
                if (pref[hi+1]-pref[lo] == x){
                    cout << "Yes" << "\n";
                    ok = true;
                    break;
                }
                int mid = (ar[lo]+ar[hi])/2;
                int pos = lower_bound(ar.begin()+lo,ar.end()+hi,mid)-ar.begin()-binary_search(ar.begin(),ar.end(),mid);
                if (pref[pos+1]-pref[lo] < x){
                    hi = pos;
                }
                else{
                    lo = pos;
                }
            }
            if (!ok){
                cout << "No" << "\n";
            }
        }
    }
}

