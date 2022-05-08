#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;
    while (t--){
        int n;
        cin >> n;
        vector<int>a(n);
        int sum = 0;
        bool only2 = true;
        for (int i = 0; i < n; i++){
            cin >> a[i];
            sum += a[i];
            if (a[i] == 1){
                only2 = false;
            }
        }
        if (sum%2 == 1 || (only2 && n%2==1)){
            cout << "NO\n";
            continue;
        }
        else{
            cout << "YES\n";
        }
    }
}
