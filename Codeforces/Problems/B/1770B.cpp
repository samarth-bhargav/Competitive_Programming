#include <bits/stdc++.h>
using namespace std;


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--){
        int n, k;
        cin >> n >> k;
        int lo = 1, hi = n;
        bool which = 1;
        for (int i = 0; i < n; i++){
            if (which){
                cout << hi << " ";
                hi--;
            }
            else{
                cout << lo << " ";
                lo++;
            }
            which = (which ? 0 : 1);
        }
        cout << "\n";
    }
}
