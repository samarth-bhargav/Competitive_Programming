#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;
    while (t--){
        int n, m;
        cin >> n >> m;
        int a[n][m];
        vector<vector<vector<int>>> sortings(m);
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                cin >> a[i][j];
            }
        }
        for (int c = 0; c < m; c++){
            vector<pair<int,int>> temp;
            for (int r = 0; r < n; r++){
                temp.emplace_back(a[r][c], r);
            }
            sort(temp.begin(), temp.end());
            vector<int> temporary;
            for (int i = 0; i < n; i++){
                if (temporary.empty()){
                    temporary.push_back(temp[i].second);
                }
                else if (a[temporary.back()][c] == temp[i].first){
                    temporary.push_back(temp[i].second);
                }
                else{
                    sortings[c].push_back(temporary);
                    temporary.clear();
                    temporary.push_back(temp[i].second);
                }
            }
            if (!temporary.empty()){
                sortings[c].push_back(temporary);
            }
        }
        map<string, int> prefixes, suffixes;
        string base = "";
        for (int i = 0; i < n; i++){
            base += 'R';
        }
        string temp_base = base;
        for (vector<int> x : sortings[0]){
            for (int elem : x){
                temp_base[elem] = 'B';
            }
            prefixes[temp_base] = 1;
        }
        for (int c = 1; c < m-1; c++){
            temp_base = base;
            for (vector<int> x : sortings[c]){
                for (int elem : x){
                    temp_base[elem] = 'B';
                }
                if (prefixes.find(temp_base) != prefixes.end()){
                    if (prefixes[temp_base] == c){
                        prefixes[temp_base]++;
                    }
                }
            }
        }
        base = "";
        for (int i = 0; i < n; i++){
            base += 'B';
        }
        for (vector<int> x : sortings[m-1]){
            for (int elem : x){
                temp_base[elem] = 'R';
            }
            suffixes[temp_base] = m-2;
        }
        for (int c = m-2; c > 0; c--){
            temp_base = base;
            for (vector<int> x : sortings[c]){
                for (int elem : x){
                    temp_base[elem] = 'R';
                }
                if (suffixes.find(temp_base) != suffixes.end()){
                    if (suffixes[temp_base] == c){
                        suffixes[temp_base]--;
                    }
                }
            }
        }
        //in the commonalities of prefixes and suffixes, there is a maximum of n possible colorings
        //with range minimum and range max query preprocessing, it will take O(nlogm)
        //time to check if some coloring is possible
        bool sol_found = false;
        for (pair<string,int> p : prefixes){
            if (suffixes.find(p.first) != suffixes.end()){
                if (prefixes[p.first] >= suffixes[p.first]){
                    cout << "YES\n";
                    cout << p.first << " " << prefixes[p.first] << "\n";
                    sol_found = true;
                    break;
                }
            }
        }
        if (!sol_found){
            cout << "NO\n";
        }
    }
}
