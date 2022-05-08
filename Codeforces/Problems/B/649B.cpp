/*
Author: treewave
orz
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--){
        int n;
        cin >> n;
        vector <int> bad;
        int ar[n];
        for (int i = 0; i < n; i++){
            cin >> ar[i];
        }
        for (int i = 1; i < n-1; i++){
            if ((ar[i-1] <= ar[i] && ar[i] <= ar[i+1]) || (ar[i-1] >= ar[i] && ar[i] >= ar[i+1])){
                bad.push_back(i);
            }
        }
        cout << n - bad.size() << "\n";
        for (int i = 0; i < n; i++){
            if (!binary_search(bad.begin(), bad.end(), i)){
                cout << ar[i] << " ";
            }
        }
        cout << "\n";
    }
}

