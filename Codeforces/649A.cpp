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
        int n,x;
        cin >> n >> x;
        int ar[n];
        bool alg = true;
        int sum = 0;
        int maxpre = -1, maxend = -1;
        for (int i = 0; i < n; i++){
            cin >> ar[i];
            sum += ar[i];
            if (ar[i]%x != 0){
                alg = false;
                if (maxpre == -1){
                    maxpre = i;
                }
                maxend = i;
            }
        }
        if (alg){
            cout << -1 << "\n";
            continue;
        }
        if (sum%x != 0){
            cout << n << "\n";
            continue;
        }
//        cout << maxpre << " " << maxend << "\n";
        cout << max(n-maxpre-1, maxend) << "\n";
    }
}
