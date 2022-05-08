/*
Author: treewave
orz
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--){
        int n;
        cin >> n;
        int three = 0;
        int five = 0;
        int seven = 0;
        if (n%3 == 0){
            three += n / 3;
            cout << three << " " << five << " " << seven << "\n";
        }
        else if (n == 0){
            cout << 0 << " " << 0 << " " << "\n";
        }
        else if (n == 5){
            cout << 0 << " " << 1 << " " << 0 << "\n";
        }
        else if (n == 7){
            cout << 0 << " " << 0 << " " << 1 << "\n";
        }
        else if (n%3 == 1){
            if (n >= 10){
                cout << n/3 - 2 << " " << 0 << " " << 1 << "\n";
            }
            else{
                cout << -1 << "\n";
            }
        }
        else{
            if (n >= 8){
                cout << n/3 - 1 << " " << 1 << " " << 0 << "\n";
            }
            else{
                cout << -1 << "\n";
            }
        }
    }
}

