#include <bits/stdc++.h>
using namespace std;

bool check(int ones, int twos, int threes, vector<int> &a){
    for (int i = 0; i < a.size(); i++){
        bool yay = false;
        for (int one = 0; one <= ones; one++){
            for (int two = 0; two <= twos; two++){
                if (a[i] - one - two * 2 < 0){
                    continue;
                }
                if ((a[i] - one - two * 2) % 3 == 0 && (a[i] - one - two * 2) / 3 <= threes){
                    yay = true;
                }
            }
        }
        if (!yay){
            return false;
        }
    }
    return true;
}

int main(){
    int t;
    cin >> t;
    while (t--){
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        int max_threes = *max_element(a.begin(), a.end()) / 3;
        int ans = 1e9;
        for (int ones = 0; ones < 2; ones++){
            for (int twos = 0; twos < 3; twos++){
                for (int threes = max_threes; ~threes && threes > max_threes-4; threes--){
//                    if (ones + twos + threes == 2){
//                        cout << ones << " " << twos << " " << threes << "\n";
//                    }
                    if (check(ones, twos, threes, a)){
                        ans = min(ans, ones + twos + threes);
                    }
                }
            }
        }
        cout << ans << "\n";
    }
}
