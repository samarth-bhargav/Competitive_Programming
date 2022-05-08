/*
Author: treewave
orz
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    //setIO();
    int t;
    cin >> t;
    while (t--){
        int n, m;
        cin >> n >> m;
        long long ar[n][m];
        long long ans = 0;
        for (int i = 0; i < n; i++){
            for (int k = 0; k < m; k++){
                cin >> ar[i][k];
            }
        }
        for (int i = 0; i < n; i++){
            for (int k = 0; k < m; k++){
                long long x = (long long) llround((ar[i][k] + ar[n-i-1][k] + ar[n-i-1][m-k-1] + ar[i][m-k-1])/(4.0));
                if ((m%2 == 1 && k == m/2) || (n%2 == 1 && i == n/2)){
                    ans += (abs(x - ar[i][k]) + abs(x - ar[n-i-1][k]) + abs(x - ar[n-i-1][m-k-1]) + abs(x - ar[i][m-k-1]))/2;
                }
                else{
                    ans += abs(x - ar[i][k]) + abs(x - ar[n-i-1][k]) + abs(x - ar[n-i-1][m-k-1]) + abs(x - ar[i][m-k-1]);
                }
                ar[i][m-k-1] = x;
                ar[n-i-1][m-k-1] = x;
                ar[n-i-1][k] = x;
                ar[i][k] = x;
            }
        }
        /*
        for (int i = 0; i < n; i++){
            for (int k = 0; k < m; k++){
                cout << ar[i][k] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
         */
        cout << ans << "\n";
    }
}

