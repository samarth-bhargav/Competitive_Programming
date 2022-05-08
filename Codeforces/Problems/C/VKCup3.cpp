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
    multiset <int> vals;
    int snow[t], temp[t];
    for (int i = 0; i < t; i++){
        cin >> snow[i];
    }
    for (int i = 0; i < t; i++){
        cin >> temp[i];
    }
    vector <int> valserase;
    for (int i = 0; i < t; i++){
        vals.insert(snow[i]);
        int ans = 0;
        auto it = vals.lower_bound(temp[i]);
        for (auto iterate = vals.begin(); iterate != vals.end(); iterate++){
            if (*iterate < temp[i])
            valserase.push_back(*iterate);
        }

    }
    cout << "\n";
}

