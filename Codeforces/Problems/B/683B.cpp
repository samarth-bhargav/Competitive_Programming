/*
Author: treewave
orz
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    //setIO();
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--){
        int n,m;
        cin >> n >> m;
        int ar[n][m];
        int negcnt = 0;
        int leastabselement = 1e9;
        long long abssum = 0;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                cin >> ar[i][j];
                leastabselement = min(leastabselement,abs(ar[i][j]));
                abssum += abs(ar[i][j]);
                if (ar[i][j] < 0){
                    negcnt++;
                }
            }
        }
        if (negcnt%2 == 0){
            cout << abssum << "\n";
        }
        else{
            cout << abssum - 2*leastabselement << "\n";
        }
    }
}

