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
        int n,k;
        cin >> n >> k;
        multiset<int>mp;
        for (int i = 0; i < n; i++){
            int x;
            cin >> x;
            mp.insert(x);
        }
        for (int i = 0; i < k; i++){
            auto it = prev(mp.end());
            const int a = *it;
            mp.erase(it);
            auto it1 = prev(mp.end());
            const int b = *it1;
//            cout << a << " " << b << "\n";
            mp.erase(it1);
            mp.insert(a+b);
            mp.insert(0);
        }
        cout << *prev(mp.end()) - *(mp.begin()) << "\n";
    }
}

