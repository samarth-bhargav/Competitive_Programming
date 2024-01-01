#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<int> a(n, -1);
        if (n == 1){
            cout << 1 << "\n";
        }
        else if (n == 2){
            cout << 1 << " " << 2 << "\n";
        }
        else{
            a[n / 2] = 1;
            a[0] = 3;
            a[n-1] = 2;
            int curr = 4;
            for (int i = 0; i < n; i++){
                if (a[i] == -1){
                    a[i] = curr; curr++;
                }
            }
            for (int i = 0; i < n; i++){
                cout << a[i] << " ";
            }
            cout << "\n";
        }
    }
}