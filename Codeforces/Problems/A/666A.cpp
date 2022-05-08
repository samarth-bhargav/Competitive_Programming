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
        map <char, int> mp;
        for (int i = 0; i < n; i++){
            string s;
            cin >> s;
            for (char c : s){
                if (mp.find(c) == mp.end()){
                    mp.insert(make_pair(c,1));
                }
                else{
                    mp[c]++;
                }
            }
        }
        bool alg = true;
        for (auto & i : mp){
            if ((i.second)%n != 0){
                alg = false;
                break;
            }
        }
        if (alg){
            cout << "YES\n";
        }
        else{
            cout << "NO\n";
        }
    }
}

