/*
Dont raise your voice,improve your argument
--Desmond Tutu
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/
int num(char c){
    return c-'a';
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,k; string s;
    cin >> n >> k >> s;
    map<int,queue<int>>mp;
    for (int i = 0; i < n; i++){
        mp[num(s[i])].push(i);
    }
    set<int>rem;
    for (int i = 1; i <= k; i++){
        rem.insert(mp.begin()->second.front());
        mp.begin()->second.pop();
        if (mp.begin()->second.empty()){
            mp.erase(mp.begin()->first);
        }
    }
    for (int i = 0; i < n; i++){
        if (rem.find(i) != rem.end()){
            continue;
        }
        cout << s[i];
    }
    cout << "\n";
}

