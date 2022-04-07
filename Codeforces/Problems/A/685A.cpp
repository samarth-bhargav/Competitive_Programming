/*
Author: treewave
orz
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    //setIO();
    int t;
    cin >> t;
    while (t--){
        int x;
        cin >> x;
        if (x == 1){
            cout << 0 << "\n";
            continue;
        }
        else{
            if (x == 2){
                cout << 1 << "\n";
                continue;
            }
            if (x == 3){
                cout << 2 << "\n";
                continue;
            }
            else{
                if (x%2 == 0){
                    cout << 2 << "\n";
                }
                else{
                    cout << 3 << "\n";
                }
            }
        }
    }
}

