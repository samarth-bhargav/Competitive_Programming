#include <bits/stdc++.h>

using namespace std;

struct cow{
    int pref1;
    int pref2;
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ifstream cin("cereal.in");
    ofstream cout("cereal.out");
    int n,m;
    cin >> n >> m;
    cow ar[n];
    unordered_map<int,set<int>>mp;
    for (int i = 0; i < n; i++){
        int a,b;
        cin >> a >> b;
        a--; b--;
        mp[a].insert(i);
        mp[b].insert(i);
        cow x; x.pref1 = a; x.pref2 = b;
        ar[i] = x;
    }
    int ans[n];
    int curr[n];
    memset(curr,-1,sizeof(curr));
    memset(ans,0,sizeof(ans));
    vector <bool> occ(m,false);
    //occ checks if cereal brand is occupied
    for (int i = 0; i < n; i++){
        if (occ[ar[i].pref1]){
            if (occ[ar[i].pref2]){
                continue;
            }
            else{
                occ[ar[i].pref2] = true;
                ans[0]++;
                curr[i] = ar[i].pref2;
            }
        }
        else{
            occ[ar[i].pref1] = true;
            ans[0]++;
            curr[i] = ar[i].pref1;
        }
    }
    //removing first i cows from line
    for (int i = 1; i < n; i++){
//        cerr << "Cows Removed: " << i-1 << "\n";
//        for (int j = 0; j < n; j++){
//            cerr << curr[j] << " ";
//        }
//        cerr << "\n";
        if (curr[i-1] == -1){
            ans[i] = ans[i-1];
            continue;
        }
        ans[i] = ans[i-1]-1;
        occ[curr[i-1]] = false;
        int currcow = *mp[curr[i-1]].lower_bound(i);
        int currbrandunoccupied = curr[i-1];
        int currcurrcow = 1e9;
        while (true){
            if (currcow > n-1){
                break;
            }
            if (currcow == currcurrcow){
                break;
            }
            currcurrcow = currcow;
            if (curr[currcow] == -1){
                curr[currcow] = currbrandunoccupied;
                occ[currbrandunoccupied] = true;
                ans[i]++;
                continue;
            }
            else{
                if (curr[currcow] == ar[currcow].pref1){
                    //move onto next available cow
                    if (mp[currbrandunoccupied].lower_bound(currcow) == mp[currbrandunoccupied].end()){
                        break;
                    }
                    if (mp[currbrandunoccupied].lower_bound(currcow) == prev(mp[currbrandunoccupied].end())){
                        break;
                    }
                    currcow = *(++mp[currbrandunoccupied].lower_bound(currcow));
                    continue;
                }
                occ[curr[currcow]] = false;
                int a = curr[currcow];
                curr[currcow] = currbrandunoccupied;
                currbrandunoccupied = a;
                if (mp[a].lower_bound(currcow) == mp[a].end() || mp[a].lower_bound(currcow) == prev(mp[a].end())){
                    break;
                }
                currcow = *(++mp[a].lower_bound(currcow));
            }
        }
    }
    for (int i = 0; i < n; i++){
        cout << ans[i] << "\n";
    }
}

