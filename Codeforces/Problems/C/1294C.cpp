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
set <int> facts;

void factors(int x){
    for (int i = 2; i <= sqrt(x); i++){
        if (x % i == 0){
            facts.insert(i);
            x /= i;
        }
        if (facts.size() == 3){
            break;
        }
        if (facts.size() == 2){
            facts.insert(x);
            break;
        }
    }
}

int main() {
    //setIO();
    int t;
    cin >> t;
    while (t--){
        int x;
        cin >> x;
        factors(x);
        if (facts.size() == 3){
            cout << "YES" << "\n";
            for (int g: facts){
                cout << g << " ";
            }
            cout << "\n";
        }
        else{
            cout << "NO\n";
        }
        facts.clear();
    }
}

