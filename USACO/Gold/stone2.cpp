#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e6;

int main(){
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    int x = *max_element(a.begin(), a.end());
    long long ans = 0;
    for (int k = 1; k <= x; k++){
        long long temp = 0;
        int num_odds = 0;
        bool flag = false;
        bool curr_odd = true;
        bool first_odd = false;
        for (int i = 1; i*k <= x; i++) {
            //taking in between k*i and k*(i+1)
            int between = upper_bound(a.begin(), a.end(), k * (i + 1) - 1)
                          - lower_bound(a.begin(), a.end(), k * i);
            if (between % 2 == 1) {
                if (i == 1){
                    first_odd = true;
                }
                num_odds++;
                if (num_odds >= 3) {
                    flag = true;
                    break;
                }
                if (num_odds == 2) {
                    if (curr_odd){
                        temp += between;
                    }
                    else{
                        flag = true;
                        break;
                    }
                }
                curr_odd = true;
            } else {
                if (curr_odd) {
                    if (num_odds == 1 && !first_odd) {
                        flag = true;
                        break;
                    }
                }
                curr_odd = false;
            }
        }
        if (flag){}
        else if (num_odds == 1 && first_odd){
            ans += (upper_bound(a.begin(), a.end(), k*2 - 1) - lower_bound(a.begin(), a.end(), k));
        }
        else{
            if (num_odds == 2){
                ans += temp;
            }
        }
    }
    cout << ans << "\n";
}
