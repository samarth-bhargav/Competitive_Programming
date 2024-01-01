#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n, x;
        cin >> n >> x;
        vector<int> a(n), b(n), c(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        for (int i = 0; i < n; i++){
            cin >> b[i];
        }
        for (int i = 0; i < n; i++){
            cin >> c[i];
        }
        int currans = 0;
        for (int i = 0; i < n; i++){
            if (((currans | a[i]) | x) == x){
                currans |= a[i];
            }
            else{
                break;
            }
        }
        for (int i = 0; i < n; i++){
            if (((currans | b[i]) | x) == x){
                currans |= b[i];
            }
            else{
                break;
            }
        }
        for (int i = 0; i < n; i++){
            if (((currans | c[i]) | x) == x){
                currans |= c[i];
            }
            else{
                break;
            }
        }
        cout << (currans == x ? "Yes\n" : "No\n");
    }
}