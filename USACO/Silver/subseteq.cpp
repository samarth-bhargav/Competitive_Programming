#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

string String(char x, char y){
    string s(1, x);
    string t(1, y);
    return s + t;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    map <char, vector<int>> spos;
    map <char, vector<int>> tpos;
    string all = "abcdefghijklmnopqr";

    string s, t;
    cin >> s >> t;

    //perform initialization on s & t
    map <string, bool> crosses;
    for (int i = 0; i < s.length(); i++){
        spos[s[i]].push_back(i);
    }
    for (int i = 0; i < t.length(); i++){
        tpos[t[i]].push_back(i);
    }
    for (int i = 0; i < all.length(); i++){
        for (int j = i+1; j < all.length(); j++){
            int i_iter = 0;
            int j_iter = 0;
            int last_tpos = -1;
            //checking if both strings have same amount of both letters
            if (spos[all[i]].size() != tpos[all[i]].size() || spos[all[j]].size() != tpos[all[j]].size()){
                crosses[String(all[i], all[j])] = true;
                crosses[String(all[i], all[j])] = true;
                continue;
            }
            bool bad = false;
            for (int k = 0; k < s.length(); k++){
                if (s[k] == all[i]){
                    int pos = tpos[all[i]][i_iter];
                    if (pos < last_tpos){
                        crosses[String(all[i], all[j])] = true;
                        crosses[String(all[j], all[i])] = true;
                        bad = true;
                        break;
                    }
                    else{
                        i_iter++;
                        last_tpos = pos;
                    }
                }
                else if (s[k] == all[j]){
                    int pos = tpos[all[j]][j_iter];
                    if (pos < last_tpos){
                        crosses[String(all[i], all[j])] = true;
                        crosses[String(all[j], all[i])] = true;
                        bad = true;
                        break;
                    }
                    else{
                        j_iter++;
                        last_tpos = pos;
                    }
                }
            }
            if (!bad){
                crosses[String(all[i], all[j])] = false;
                crosses[String(all[i], all[j])] = false;
            }
        }
    }
    int q; cin >> q;
    for (int i = 0; i < q; i++){
        string a; cin >> a;
        bool works = true;
        if (a.length() == 1){
            works = (spos[a[0]].size() == tpos[a[0]].size());
        }
        for (int pos1 = 0; pos1 < a.length(); pos1++){
            for (int pos2 = pos1+1; pos2 < a.length(); pos2++){
                works &= !crosses[String(a[pos1], a[pos2])];
            }
        }
        cout << (works ? "Y" : "N");
    }
    cout << "\n";
}

