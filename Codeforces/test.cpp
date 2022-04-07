#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;
    while (t--){
        int n;
        cin >> n;
        if (n == 2){
            cout << "-1\n";
        }
        else{
            int ans[n][n]; int curr = 1;
            for (int i = 0; i < n; i++){
                for (int j = i%2; j < n; j+=2){
                    ans[i][j] = curr; curr++;
                }
            }
            for (int i = 0; i < n; i++){
                for (int j = (i+1)%2; j < n; j+=2){
                    ans[i][j] = curr; curr++;
                }
            }
            for (int i = 0; i < n; i++){
                for (int j = 0; j < n; j++){
                    cout << ans[i][j] << " ";
                }
                cout << "\n";
            }
        }
    }
}