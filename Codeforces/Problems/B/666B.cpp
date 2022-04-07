/*
ID: samarth10
LANG: C++11
TASK:
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    //setIO();
    int t;
    cin >> t;
    long long ar[t];
    for (int i = 0; i < t; i++){
        cin >> ar[i];
    }
    sort(ar, ar+t);
    long long ans = 1e18;
    long long c = 0;
    for (int i = 1; i <= 1e9; i++){
        long long currprod = 1;
        long long currans = 0;
        for (int k = 0; k < t; k++){
            if (k != 0){
                currprod *= i;
            }
            currans += abs(currprod - ar[k]);
        }
        if (ans < currans){
            c = i-1;
            break;
        }
        else{
            ans = min(ans, currans);
        }
    }
    cout << ans << "\n";
}