/*
ID: samarth10
LANG: C++11
TASK: 
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    freopen("moobuzz.in", "r", stdin);
    freopen("moobuzz.out", "w", stdout);
    int x;
    cin >> x;
    if (x%8 == 1){
        cout << (x/8)*15 + 1 << "\n";
    }
    if (x%8 == 2){
        cout << (x/8)*15 + 2 << "\n";
    }
    if (x%8 == 3){
        cout << (x/8)*15 + 4 << "\n";
    }
    if (x%8 == 4){
        cout << (x/8)*15 + 7 << "\n";
    }
    if (x%8 == 5){
        cout << (x/8)*15 + 8 << "\n";
    }
    if (x%8 == 6){
        cout << (x/8)*15 + 11 << "\n";
    }
    if (x%8 == 0){
        cout << ((x/8)-1)*15 + 14 << "\n";
    }
    if (x%8 == 7){
        cout << (x/8)*15 + 13 << "\n";
    }
}

