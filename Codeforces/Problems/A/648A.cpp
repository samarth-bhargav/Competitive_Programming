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
    int t;
    cin >> t;
    while (t--){
        int a,b;
        cin >> a >> b;
        vector <int> col(a,0);
        vector <int> row(b, 0);
        for (int i = 0; i < a; i++){
            for (int k = 0; k < b; k++){
                int c;
                cin >> c;
                if (c == 1){
                    col[i] = 1;
                    row[k] = 1;
                }
            }
        }
        int count = 0;
        for (int i = 0; i < col.size(); i++){
            for (int k = 0; k < row.size(); k++){
                if (col[i] == 0 && row[k] == 0){
                    count ++;
                    col.erase(col.begin() + i);
                    row.erase(row.begin() + k);
                    i--;
                    k--;
                }
            }
        }
        if (count % 2 == 1){
            cout << "Ashish" << "\n";
        }
        else{
            cout << "Vivek" << "\n";
        }
    }
}

