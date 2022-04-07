/*
Dont raise your voice,improve your argument
--Desmond Tutu
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
    int n;
    cin >> n;
    int ar[n][n];
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cin >> ar[i][j];
        }
    }
    int rmq[n][n][n];
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            rmq[i][j][j] = ar[i][j];
        }
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            for (int k = j+1; k < n; k++){
                rmq[i][j][k] = min(rmq[i][j][k-1],ar[i][k]);
            }
        }
    }
//    for (int i = 0; i < n; i++){
//        for (int j = 0; j < n; j++){
//            for (int k = 0; k < n; k++){
//                cerr << rmq[i][j][k] << " ";
//            }
//            cerr << "\n";
//        }
//        cerr << "\n";
//    }
    ll ans = 0;
    int temp[n];
    for (int i = 0; i < n; i++){
        for (int j = i; j < n; j++){
            //left and right column
            for (int k = 0; k < n; k++){
                temp[k] = rmq[k][i][j];
            }
//            for (int k = 0; k < n; k++){
//                cerr << temp[k] << " ";
//            }
//            cerr << "\n";
            vector<vector<int>>segments;
            vector<int>curr;
            for (int k = 0; k < n; k++){
                if (temp[k] < 100){
                    if (!curr.empty()){
                        segments.push_back(curr);
                        curr.clear();
                    }
                }
                else if (temp[k] == 100){
                    curr.push_back(1);
                }
                else{
                    curr.push_back(2);
                }
            }
            if (!curr.empty()){
                segments.push_back(curr);
            }
            for (auto & v : segments){
                ll ret = 0;
                vector<int>ones;
                for (int a = 0; a < v.size(); a++){
                    if (v[a] == 1){
                        ones.push_back(a);
                    }
                }
                if (ones.empty()){
                    continue;
                }
                int last = ones[ones.size()-1];
                for (int a = 0; a < v.size(); a++){
                    if (a > last){
                        break;
                    }
                    int nextval = *lower_bound(ones.begin(),ones.end(),a);
                    ret += v.size()-nextval;
                }
                ans += ret;
            }
        }
    }
    cout << ans << "\n";
}

