/*
Author: treewave
orz
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    freopen("leftout.in", "r", stdin);
    freopen("leftout.out", "w", stdout);
    int n;
    cin >> n;
    char ar[n][n];
    for (int i = 0; i < n; i++){
        for (int k = 0; k < n; k++){
            cin >> ar[i][k];
        }
    }
    int sqrcnt = 0;
    pair <int,int> ans;
    for (int i = 0; i <= n-2; i+=2){
        for (int k = 0; k <= n-2; k+=2){
            int rc = 0, lc = 0;
            ar[i][k] == 'L' ? lc++ : rc++;
            ar[i][k+1] == 'L' ? lc++ : rc++;
            ar[i+1][k+1] == 'L' ? lc++ : rc++;
            ar[i+1][k] == 'L' ? lc++ : rc++;
            if ((rc == 3 && lc == 1) || (lc == 3 && rc == 1)){
                if (sqrcnt >= 1){
                    cout << -1 << "\n";
                    return 0;
                }
                else{
                    sqrcnt++;
                }
                ans = make_pair(i,k);
            }
        }
    }
    cout << ans.first+1 << " " << ans.second+1 << "\n";
}

