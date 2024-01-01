#include <bits/stdc++.h>

using namespace std;

const int M = 998244353;
const string abet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    const int ABET_SZ = abet.size();
    assert(abet.size() == ABET_SZ);

    int n; cin >> n;
    vector<string> words(n);
    vector<vector<string>> words_with_len(11);
    unordered_set<string> encountered;
    for (int i = 0; i < n; i++){
        cin >> words[i];
        string temp = words[i];
        reverse(temp.begin(), temp.end());
        if (encountered.count(temp)) continue;
        words_with_len[words[i].size()].push_back(words[i]);
        encountered.insert(words[i]);
    }
    int ans = 0;
    for (int len = 3; len <= 10; len++){
        //len is side length of cube
        int occ[ABET_SZ][ABET_SZ], triple_occ[ABET_SZ][ABET_SZ][ABET_SZ];
        memset(occ, 0, sizeof(occ));
        memset(triple_occ, 0, sizeof(triple_occ));
        for (string s : words_with_len[len]){
            int f_idx = find(abet.begin(), abet.end(), s[0]) - abet.begin();
            int e_idx = find(abet.begin(), abet.end(), s.back()) - abet.begin();
            occ[f_idx][e_idx]++;
            string temp = s;
            reverse(temp.begin(), temp.end());
            if (temp == s) continue;
            occ[e_idx][f_idx]++;
        }
        for (int i = 0; i < ABET_SZ; i++){
            for (int j = 0; j < ABET_SZ; j++){
                for (int k = 0; k < ABET_SZ; k++){
                    for (int l = 0; l < ABET_SZ; l++){
                        long long temp = occ[i][l] * occ[j][l]; temp %= M;
                        temp *= occ[k][l]; temp %= M;
                        triple_occ[i][j][k] += temp;
                        triple_occ[i][j][k] %= M;
                    }
                }
            }
        }
        for (int i = 0; i < ABET_SZ; i++){
            for (int j = 0; j < ABET_SZ; j++){
                for (int k = 0; k < ABET_SZ; k++){
                    for (int l = 0; l < ABET_SZ; l++){
                        long long temp = 1;
                        temp *= triple_occ[i][j][k]; temp %= M;
                        temp *= triple_occ[i][j][l]; temp %= M;
                        temp *= triple_occ[i][k][l]; temp %= M;
                        temp *= triple_occ[j][k][l]; temp %= M;
                        ans += temp; ans %= M;
                    }
                }
            }
        }
    }
    cout << (ans + M) % M;
}