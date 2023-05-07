#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n, s, r;
        cin >> n >> s >> r;
        int max_val = s - r;
        int curr_sum = max_val;
        vector<int> sol = {max_val};
        for (int i = n-1; i > 0; i--){
            if (curr_sum + max_val + (i-1) * 1 <= s){
                sol.push_back(max_val);
                curr_sum += max_val;
            }
            else{
                max_val--;
                i++;
            }
        }
        for (int i = 0; i < n; i++){
            cout << sol[i] << " ";
        }
        cout << "\n";
    }
}

