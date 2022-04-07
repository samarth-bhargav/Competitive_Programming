/*
Dont raise your voice,improve your argument
--Desmond Tutu
*/
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
        ll n;
        cin >> n;
        if (n == 1){
            cout << "NO\n";
            continue;
        }
        ll lower = 1, upper = cbrt(n);
        while (lower <= upper){
            if (lower*lower*lower + upper*upper*upper == n){
                cout << "YES\n";
                break;
            }
            else if (lower*lower*lower+upper*upper*upper < n){
                lower++;
            }
            else{
                upper--;
            }
        }
        if (lower*lower*lower+upper*upper*upper != n){
            cout << "NO\n";
        }
    }
}

