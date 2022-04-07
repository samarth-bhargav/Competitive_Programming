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
    while (t--){
        int n;
        cin >> n;
        long long minans = 1e9;
        long long currsum = 0;
        for (int i = 0; i < n; i++){
            long long x;
            cin >> x;
            currsum += x;
            minans = min(minans, currsum);
        }
        cout << -1 * minans << "\n";
    }
}

