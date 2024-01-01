#include <bits/stdc++.h>

using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int xa, ya, xb, yb, xc, yc;
        cin >> xa >> ya >> xb >> yb >> xc >> yc;
        xb -= xa; yb -= ya;
        xc -= xa; yc -= ya;
        if ((xb >= 0) == (xc >= 0)){
            if ((yb >= 0) == (yc >= 0)){
                //same quadrant
                cout << min(abs(xb), abs(xc)) + min(abs(yb), abs(yc)) + 1 << "\n";
            }
            else{
                //diff quadrant
                cout << min(abs(xb), abs(xc)) + 1 << "\n";
            }
        }
        else if ((yb >= 0) == (yc >= 0)){
            //diff quadrant
            cout << min(abs(yb), abs(yc)) + 1 << "\n";
        }
        else{
            //opposite quadrant
            cout << 1 << "\n";
        }
    }
}