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
        cout << 2 << "\n";
        if (n == 2){
            cout << 1 << " " << 2 << "\n";
        }
        else if (n == 3){
            cout << 2 << " " << 3 << "\n" << 1 << " " << 3 << "\n";
        }
        else{
            cout << n << " " << n-1 << "\n";
            cout << n-2 << " " << n << "\n";
            for (int i = n-1; i >= 3; i--){
                cout << i << " " << i-2 << "\n";
            }
        }
    }
}

