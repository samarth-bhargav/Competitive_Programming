#include <bits/stdc++.h>
using namespace std;

const int mxL = 21;
set<char> letters;
int cnt[mxL][mxL];
int dp[1 << mxL];

int main(){
    string s;
    cin >> s; int n = s.length();
    vector<int> a(n);
    for (int i = 0; i < n; i++){
        letters.insert(s[i]);
    }
    for (int i = 0; i < n; i++){
        a[i] = distance(letters.begin(), letters.find(s[i]));
    }
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n-1; i++){
        cnt[a[i]][a[i+1]]++;
    }
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 0; i < mxL; i++){
        for (int j = 0; j < mxL; j++){
            if (j != i){
                dp[(1 << i) + (1 << j)] = cnt[i][j];
            }
        }
    }
    for (int i = 0; i < (1 << mxL); i++){
        if (__builtin_popcount(i) <= 2){
            continue;
        }
        else{
            for (int j = 0; j < mxL; j++){
                if ((i >> j) & 1){
                    //jth bit from the right is activated
                    int sum1 = 0, sum2 = 0;
                    for (int k = 0; k < mxL; k++){
                        if (((i >> k) & 1) && k != j){
                            sum1 += cnt[j][k];
                            sum2 += cnt[k][j];
                        }
                    }
                    int sum = min(sum1, sum2);
                    dp[i] = min(dp[i], dp[i ^ (1 << j)] + sum);
                }
            }
        }
    }
    int sum = 0;
    for (int i = 0; i < mxL; i++){
        sum += cnt[i][i];
    }
    cout << dp[(1 << (letters.size())) - 1] + sum + 1;
}