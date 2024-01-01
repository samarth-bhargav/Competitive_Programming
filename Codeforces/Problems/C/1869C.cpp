#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n, m; cin >> n >> m;
        if (m == 1){
            cout << 0 << "\n";
            for (int i = 0; i < n; i++){
                for (int j = 0; j < m; j++){
                    cout << 0 << " ";
                }
                cout << "\n";
            }
            continue;
        }
        int a[n][m];
        if (n+1 < m){
            cout << n+1 << "\n";
            for (int i = 0; i < n; i++){
                for (int j = 0; j < n+1; j++){
                    a[i][j] = (i + j) % (n + 1);
                }
            }
            for (int i = 0; i < n; i++){
                for (int j = n+1; j < m; j++){
                    a[i][j] = j;
                }
            }
        }
        else{
            cout << m << "\n";
            for (int i = 0; i < n; i++){
                for (int j = 0; j < m; j++){
                    a[i][j] = (i >= m-1 ? a[i - m + 1][j] : (i + j) % m);
                }
            }
        }
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                cout << a[i][j] << " ";
            }
            cout << "\n";
        }
    }
}