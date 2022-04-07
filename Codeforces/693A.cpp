#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;
    while (t--){
        int w,h,n;
        cin >> w >> h >> n;
        int a = 0, b = 0;
        while (w%2 != 1){
            w /= 2;
            a++;
        }
        while (h%2 != 1){
            h /= 2;
            b++;
        }
        cout << (pow(2,a)*pow(2,b)>=n?"YES":"NO") << "\n";
    }
}
