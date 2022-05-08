#include <bits/stdc++.h>
using namespace std;

int main() {
    //setIO();
    int t;
    cin >> t;
    while (t--){
        int n;
        cin >> n;
        char ar[n];
        for (int i = 0; i < n; i++){
            cin >> ar[i];
        }
        int k = 0;
        while (true){
            bool alg = true;
            vector <int> val;
            for (int i = 0; i < n-1; i++){
                if (ar[i] == 'A' && ar[i+1] == 'P'){
                    alg = false;
                    val.push_back(i+1);
                }
            }
            k++;
            for (auto &i : val){
                ar[i] = 'A';
            }
            if (alg){
                break;
            }
        }
        cout << k-1 << "\n";
    }
}

