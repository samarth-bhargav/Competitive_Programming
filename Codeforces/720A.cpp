#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--){
        ll a,b;
        cin >> a >> b;
        if (a%b == 0){
            cout << "NO\n";
            continue;
        }
        if (b == 2){
            cout << "YES\n";
            cout << a*a << " " << 3*a*a << " " << 4*a*a << "\n";
        }
        else{
            cout << "YES\n";
            cout << a << " " << a*(b-1) << " " << a*b << "\n";
        }
    }
}