/*
Dont raise your voice,improve your argument
--Desmond Tutu
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
 * vals basically stores the counts of s[i+1] for every i based on letter
*/
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,k;
    cin >> n >> k;
    vector<vector<int>>vals(26,vector<int>(26,0));
    string s;
    if (n == 1){
        cout << "a" << "\n";
        return 0;
    }
    if (n == 2){
        if (k == 1){
            cout << "aa" << "\n";
        }
        else{
            cout << "ab" << "\n";
        }
        return 0;
    }
    if (k == 1){
        for (int i = 0; i < n; i++){
            cout << "a";
        }
        cout << "\n";
        return 0;
    }
    s += "ab"; vals[0][1]++;
    for (int i = 2; i < n; i++){
        char c = s[i-1];
        char best = 'a';
        for (int j = 0; j < k; j++){
            if (vals[c-'a'][best-'a'] >= vals[c-'a'][j]){
                best = 'a'+j;
            }
        }
        s += best;
        vals[c-'a'][best-'a']++;
    }
    cout << s << "\n";
}

