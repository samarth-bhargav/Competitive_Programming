#include <bits/stdc++.h>
using namespace std;

#define int long long
const int mxN = 2e5;

map<int, set<int>> occ; //maps the char to the references where it occurs
vector<map<int, vector<int>>> posses; //maps the char to the values where it occurs in a string
vector<vector<int>> representations; //stores the numerical rep in terms of the references
vector<long long> sizes(mxN + 26, 0);

string getSubstr(int ref, int l, int r, bool initial=false){
    //iterate through ref's representation until breaks
    if (0 <= ref && ref <= 25 && !(initial)){
        return string(1, char(97 + ref));
    }
    string ret = "";
    //find where it begins
    long long curr_sz = 0;
    int start_ref, start_l;
    for (int i = 0; i < representations[ref].size(); i++){
        curr_sz += sizes[representations[ref][i]];
        if (curr_sz >= l + 1){
            start_ref = i;
            start_l = sizes[representations[ref][i]] - (curr_sz - l);
            break;
        }
    }
    if (curr_sz >= r + 1){
        ret += getSubstr(representations[ref][start_ref], start_l, sizes[representations[ref][start_ref]] - (curr_sz - r));
        return ret;
    }
    ret += getSubstr(representations[ref][start_ref], start_l, sizes[representations[ref][start_ref]] - 1);
    for (int i = start_ref + 1; i < representations[ref].size(); i++){
        curr_sz += sizes[representations[ref][i]];
        if (curr_sz >= r + 1){
            //now limit
            ret += getSubstr(representations[ref][i], 0, sizes[representations[ref][i]] - (curr_sz - r));
            break;
        }
        else{
            ret += getSubstr(representations[ref][i], 0, sizes[representations[ref][i]] - (curr_sz - r));
        }
    }
    return ret;
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int l, r, tc;
    cin >> l >> r >> tc; l--; r--;

    for (int c = 0; c < 26; c++){
        representations.push_back({c}); //represent themselves
        map<int, vector<int>> pos;
        pos[c] = {0};
        posses.push_back(pos);
        occ[c] = {c};
    }
    for (int t = 26; t <= tc + 25; t++){
        char c; string s;
        cin >> c >> s;
        int c_rep = c - 'a';
        for (int x : occ[c_rep]){
            //the strings where it occurs
            //replace it with reference
            for (int pos : posses[x][c_rep]){
                //the positions in the string where it occurs
                //replace raw with reference now
                representations[x][pos] = t;
            }
            posses[x][c_rep].clear();
        }
        occ[c_rep].clear();
        representations.push_back({});
        posses.push_back(map<int, vector<int>> ());
        for (char x : s){
            representations[t].push_back(x - 'a');
            posses[t][x - 'a'].push_back(representations[t].size() - 1);
            occ[x - 'a'].insert(t);
        }
    }
    //get actual answer
    //find actual sizes of each of the references
    for (int t = tc+25; t >= 0; t--){
        for (int x : representations[t]){
            if (0 <= x && x <= 25){
                //raw character
                sizes[t]++;
            }
            else{
                sizes[t] += sizes[x];
            }
        }
    }
    for (int i = 0; i <= 25; i++){
        sizes[i] = 1;
    }
    cout << getSubstr(0, l, r, true) << "\n";
}