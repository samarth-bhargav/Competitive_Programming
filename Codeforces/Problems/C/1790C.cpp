#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<vector<int>> perms(n, vector<int> (n-1));
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n-1; j++){
                cin >> perms[i][j];
            }
        }
        vector<int> ans = perms[0];
        int missing = -1;
        for (int i = 1; i <= n; i++){
            if (find(ans.begin(), ans.end(), i) == ans.end()){
                missing = i;
                break;
            }
        }
        set<int> before, after;
        for (int i = 1; i < n; i++){
            bool encountered = false;
            for (int j = 0; j < n-1; j++){
                if (perms[i][j] == missing){
                    encountered = true;
                }
                else{
                    if (encountered){
                        after.insert(perms[i][j]);
                    }
                    else{
                        before.insert(perms[i][j]);
                    }
                }
            }
        }
        vector<int> actual_ans;
        bool encountered = false;
        for (int i = 0; i < n-1; i++){
            if (!encountered){
                if (before.find(ans[i]) == before.end()){
                    encountered = true;
                    actual_ans.push_back(missing);
                    actual_ans.push_back(ans[i]);
                }
                else{
                    actual_ans.push_back(ans[i]);
                }
            }
            else{
                actual_ans.push_back(ans[i]);
            }
        }
        if (actual_ans.size() == n-1){
            actual_ans.push_back(missing);
        }
        for (int i = 0; i < n; i++){
            cout << actual_ans[i] << " ";
        }
        cout << "\n";
    }
}

