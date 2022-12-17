#include <bits/stdc++.h>
using namespace std;

const int mxN = 50;

int main(){
    int t;
    cin >> t;
    while (t--){
        int n, m;
        cin >> n >> m;
        vector<vector<int>> a(m);
        unordered_map<int,set<int>> present;
        for (int i = 0; i < m; i++){
            int k; cin >> k; a[i].resize(k);
            for (int j = 0; j < k; j++){
                cin >> a[i][j]; a[i][j]--;
                present[a[i][j]].insert(i);
            }
        }
        //contiguous subarray check
        bool bad = false;
        for (int b = 0; b < n; b++){
            if (present.find(b) != present.end()){
                if (present[b].empty()){
                    continue;
                }
                if (*prev(present[b].end()) - *present[b].begin() != present[b].size()-1){
                    cout << "NO\n";
                    bad = true;
                    break;
                }
            }
        }
        if (bad){
            continue;
        }
//        if (n == 1){
//            cout << "YES\n";
//            continue;
//        }
        //bracket sequence check
        //can probably do this using stacks?
        for (int i = 0; i < m; i++){
            if (bad){
                break;
            }
            stack<int> vals;
            unordered_set<int> processed;
            for (int elem : a[i]){
                if (processed.find(elem) != processed.end()){
                    if (vals.top() != elem){
                        cout << "NO\n";
                        bad = true;
                        break;
                    }
                    vals.pop();
                }
                else{
                    processed.insert(elem);
                    vals.push(elem);
                }
            }
        }
        if (bad){
            continue;
        }
        //bracket ordering must persist across lines
        //from line to line, see which elements got "inserted".
        //subtract these elements from the new line, and see if it equals the old one
        //gained[i] denotes elements gained from m = i to m = i+1
        //lost[i] denotes elements lost from m = i+1 to m = i
        vector<set<int>> gained(m-1), lost(m-1);
        for (int i = 0; i < m-1; i++){
            for (int elem : a[i]){
                if (find(a[i+1].begin(), a[i+1].end(), elem) == a[i+1].end()){
                    //you lost element from i to i+1
                    lost[i].insert(elem);
                }
            }
        }
        for (int i = m-1; i > 0; i--){
            for (int elem : a[i]){
                if (find(a[i-1].begin(), a[i-1].end(), elem) == a[i-1].end()){
                    //you gained element from i-1 to i
                    gained[i-1].insert(elem);
                }
            }
        }
        for (int i = 0; i < m-1; i++){
            if (bad){
                break;
            }
            for (int elem : gained[i]){
                if (bad){
                    break;
                }
                int pos = find(a[i+1].begin(), a[i+1].end(), elem) - a[i+1].begin();
                for (int p = pos+1; a[i+1][p] != elem; p++){
                    if (gained[i].find(a[i+1][p]) == gained[i].end()){
                        bad = true;
                        cout << "NO\n";
                        break;
                    }
                }
            }
        }
        if (bad){
            continue;
        }
        for (int i = 0; i < m-1; i++){
            vector<int> cpy_1, cpy_2;
            for (int j = 0; j < a[i].size(); j++){
                if (lost[i].find(a[i][j]) == lost[i].end()){
                    cpy_1.push_back(a[i][j]);
                }
            }
            for (int j = 0; j < a[i+1].size(); j++){
                if (gained[i].find(a[i+1][j]) == gained[i].end()){
                    cpy_2.push_back(a[i+1][j]);
                }
            }
            if (cpy_1 != cpy_2){
                cout << "NO\n";
                bad = true;
                break;
            }
        }
        if (bad){
            continue;
        }
        cout << "YES\n";
    }
}
