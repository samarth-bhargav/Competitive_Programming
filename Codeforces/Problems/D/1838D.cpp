#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q;
    string str; cin >> str;
    vector<int> s(n);
    for (int i = 0; i < n; i++){
        s[i] = (str[i] == '(' ? 1 : 0);
    }
    if (n%2 == 1){
        for (int i = 0; i < q; i++){
            cout << "NO\n";
        }
        return 0;
    }
    vector<int> adj_diff(n-1);
    set<int> zeroes;
    for (int i = 0; i < n-1; i++){
        adj_diff[i] = s[i+1] - s[i];
        if (adj_diff[i] == 0){
            zeroes.insert(i);
        }
    }
    for (int i = 0; i < q; i++){
        int idx; cin >> idx; idx--;
        s[idx] = s[idx]^1;
        if (zeroes.count(idx-1)){
            zeroes.erase(idx-1);
        }
        if (zeroes.count(idx)){
            zeroes.erase(idx);
        }
        if (idx != 0){
            adj_diff[idx-1] = s[idx] - s[idx-1];
        }
        if (idx != n-1){
            adj_diff[idx] = s[idx+1] - s[idx];
        }
        if (adj_diff[idx-1] == 0){
            zeroes.insert(idx-1);
        }
        if (adj_diff[idx] == 0){
            zeroes.insert(idx);
        }
        if (s[0] != 1 || s.back() != 0){
            cout << "NO\n";
            continue;
        }
        if (zeroes.empty()){
            cout << "YES\n";
            continue;
        }
        int first = *zeroes.begin();
        int last = *prev(zeroes.end());
        cerr << first << " " << last << "\n";
        if (s[first] != 1 || s[last] != 0){
            cout << "NO\n";
        }
        else{
            cout << "YES\n";
        }
    }
}