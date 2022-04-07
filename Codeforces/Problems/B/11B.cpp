#include <bits/stdc++.h>
using namespace std;

int pfact(int n){
    int ret = 0;
    while (n % 2 == 0){
        ret++;
        n = n/2;
    }
    for (int i = 3; i <= sqrt(n); i = i + 2){
        while (n % i == 0){
            ret++;
            n = n/i;
        }
    }
    if (n > 2){
        ret++;
    }
    return ret;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--){
        int a,b,k;
        cin >> a >> b >> k;
        int x = __gcd(a,b);
        int a1 = pfact(a);
        int b1 = pfact(b);
//        cerr << a1 << " " << b1 << "\n";
        if (a != b && k == 1){
            if (x == a || x == b){
                cout << "YES\n";
            }
            else{
                cout << "NO\n";
            }
        }
        else if (a == b && k == 1){
            cout << "NO\n";
        }
        else{
            if (a1+b1 >= k){
                cout << "YES\n";
            }
            else{
                cout << "NO\n";
            }
        }
    }
}