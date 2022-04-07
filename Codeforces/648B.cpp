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
vector <int> x;
vector <int> y;
int main() {
    //setIO();
    int t;
    cin >> t;
    while (t--){
        x.clear();
        y.clear();
        int c;
        cin >> c;
        for (int i = 0; i < c; i++){
            int k;
            cin >> k;
            x.push_back(k);
        }
        for (int i = 0; i < c; i++){
            int k;
            cin >> k;
            y.push_back(k);
        }
        while (!is_sorted(x.begin(), x.end())){
            bool alg = 0;
            for (int i = 0; i < x.size() - 1; i++){
                if (alg){
                    break;
                }
                for (int k = i + 1; k < x.size(); k++){
                    if (x[i] > x[k]){
                        if (y[i] != y[k]){
                            swap(y[i], y[k]);
                            swap(x[i], x[k]);
                            alg = true;
                            break;
                        }
                    }
                }
            }
            if (!alg){
                break;
            }
        }
        if (is_sorted(x.begin(), x.end())){
            cout << "Yes" << "\n";
        }
        else{
            cout << "No" << "\n";
        }
    }
}

