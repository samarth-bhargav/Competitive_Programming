/*
Dont raise your voice,improve your argument
--Desmond Tutu
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/
#define int ll

int digits(int x){
    int ret = 0;
    while (x != 0){
        x /= 10;
        ret++;
    }
    return ret;
}
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--){
        int a,b,c;
        cin >> a >> b >> c;
        int x,y,cval = pow(10,c-1);
        x = cval; y = cval;
        while (digits(x) != a){
            x *= 8;
        }
        while (digits(y) != b){
            y *= 7;
        }
        cout << x << " " << y << "\n";
    }
}

