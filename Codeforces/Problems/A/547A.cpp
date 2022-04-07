#include <bits/stdc++.h>
using namespace std;

int main(void){
    long long a, b;
    cin >> a >> b;
    if (b%a != 0){
        cout << -1 << endl;
        return 0;
    }
    int ans = 0;
    int x = b/a;
    for (int i = 2; i <= x; i++){
        if (b == 1){
            break;
        }
        if (i > 3){
            cout << -1 << "\n";
            return 0;
        }
        if (x%i == 0){
            ans++;
            x /= i;
            i--;
        }
    }
    cout << ans << "\n";
}