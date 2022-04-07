//babybeluga
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string s; cin >> s;
    map<char, pair<set<char>, set<char>>> um;
    int iter = 0;
    bool new_iter = true;
    set<char> chars_used;
    for (int i = 0; i < s.length(); i++){
        if (um.find(s[i]) == um.end()){
            if (new_iter){
                um[s[i]] = {{},{}};
                chars_used.insert(s[i]);
                new_iter = false;
            }
            else{
                for (char c : chars_used){
                    um[s[i]].first.insert(c);
                    um[c].second.insert(s[i]);
                }
                chars_used.insert(s[i]);
            }
        }
        else{
            if (chars_used.find(s[i]) != chars_used.end()){
                chars_used.clear();
                chars_used.insert(s[i]);
                iter++;
                continue;
            }
            for (char c : chars_used){
                if (um[c].first.find(s[i]) != um[c].first.end()){
                    //basically if you find s[i] in the befores of one of them
                    chars_used.clear();
                    chars_used.insert(s[i]);
                    iter++;
                    break;
                }
            }
            if (new_iter){
                continue;
            }
            for (char c : chars_used){
                um[c].second.insert(s[i]);
                um[s[i]].first.insert(c);
            }
            chars_used.insert(s[i]);
        }
    }
    if (!chars_used.empty()){
        iter++;
    }
    cout << iter << "\n";
}

