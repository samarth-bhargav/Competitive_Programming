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


int main() {
    //setIO();
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--){
        int a,b;
        cin >> a >> b;
        string s;
        cin >> s;
        int curr = 0;
        for (int i = 0; i < a; i++){
            if (s[i] == '0'){
                if (b >= i - curr){
                    s.insert(curr, "0");
                    s.erase(s.begin() + i + 1);
                    b -= i - curr;
                    curr ++;
                }
                else{
                    s.insert(i - b, "0");
                    s.erase(s.begin() + i + 1);
                    break;
                }
            }
        }
        cout << s << "\n";
    }
}

