#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--){

        int n, m; cin >> n >> m;
        vector<int> x(n);
        for (int i = 0; i < n; i++){
            cin >> x[i];
        }
        vector<vector<bool>> answers(n, vector<bool> (m));
        for (int i = 0; i < n; i++){
            string s; cin >> s;
            for (int j = 0; j < m; j++){
                answers[i][j] = s[j] == '0' ? 0 : 1;
            }
        }
        int ans = -1;
        vector<int> optimal_perm;
        for (int mask = 0; mask < (1 << n); mask++){
            //on bits represent maximizing ri-xi
            //off bits represent maximizing xi-ri
            vector<array<int, 2>> weights;
            //go question by question
            for (int i = 0; i < m; i++){
                //see how many benefits
                int benefits = 0;
                for (int j = 0; j < n; j++){
                    if ((mask >> j) & 1){
                        //maximizing ri-xi, so want
                        if (answers[j][i]){
                            benefits++;
                        }
                    }
                    else{
                        if (answers[j][i]){
                            benefits--;
                        }
                    }
                }
                weights.push_back({benefits, i});
            }
            sort(weights.begin(), weights.end());
            vector<int> perm(m);
            for (int i = 0; i < m; i++){
                perm[weights[i][1]] = i+1;
            }
            //calculate the answer
            int temp = 0;
            vector<int> r(n, 0);
            for (int i = 0; i < m; i++){
                for (int j = 0; j < n; j++){
                    if (answers[j][i]){
                        r[j] += perm[i];
                    }
                }
            }
            for (int i = 0; i < n; i++){
                temp += abs(r[i] - x[i]);
            }
            if (ans == -1 || temp > ans){
                ans = temp;
                optimal_perm = perm;
            }
        }
        for (int elem : optimal_perm){
            cout << elem << " ";
        }
        cout << "\n";
    }

}
