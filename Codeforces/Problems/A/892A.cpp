#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        if (count(a.begin(), a.end(), a[0]) == a.size()){
            cout << -1 << "\n";
            continue;
        }
        else{
            int x = *max_element(a.begin(), a.end());
            vector<int> b, c;
            for (int i = 0; i < n; i++){
                if (a[i] == x){
                    c.push_back(a[i]);
                }
                else{
                    b.push_back(a[i]);
                }
            }
            cout << b.size() << " " << c.size() << "\n";
            for (int p : b){
                cout << p << " ";
            }
            cout << "\n";
            for (int p : c){
                cout << p << " ";
            }
            cout << "\n";
        }
    }
}