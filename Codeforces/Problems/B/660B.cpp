/*
ID: samarth10
LANG: C++11
TASK: 
*/
#include <bits/stdc++.h>

using namespace std;


void setIO(string name) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen((name + ".in").c_str(), "r", stdin);
    freopen((name + ".out").c_str(), "w", stdout);
}
string DecimalToBinary(int n) {
    int binaryNumber[100], num=n;
    int i = 0;
    while (n > 0) {
        binaryNumber[i] = n % 2;
        n = n / 2;
        i++;
    }
    string s = "";
    for (int j = i - 1; j >= 0; j--)
        s += binaryNumber[j];
    return s;
}
int main() {
    //setIO();
    int t;
    cin >> t;
    while (t--){
        int n;
        cin >> n;
        string s;
        int x = 0;
        for (int i = 0; i < n+1; i++){
            if (4 * i >= n){
                x = i;
                break;
            }
        }
        for (int i = 0; i < n-x; i++){

            s += '9';
        }
        for (int i = 0; i < x; i++){
            s += '8';
        }
        cout << s << "\n";
    }
}

