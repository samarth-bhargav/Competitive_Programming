#include <bits/stdc++.h>
using namespace std;

const int mxN = 500;
vector<int> adj[mxN];
vector<bool> vis(mxN, false);
vector<int> in_deg(mxN, 0);
vector<vector<int>> groups;
bool same[mxN][mxN];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    memset(same, 0, sizeof(mxN));
    vector<vector<bool>> a(m, vector<bool> (n));
    for (int i = 0; i < n; i++){
        string s; cin >> s;
        for (int j = 0; j < m; j++){
            a[j][i] = (s[j] == '0' ? 0 : 1);
        }
    }
    for (int d1 = 0; d1 < m; d1++){
        for (int d2 = 0; d2 < m; d2++){
            if (d1 == d2) continue;
            bool all_less = true;
            for (int p = 0; p < n; p++){
                if (a[d1][p] > a[d2][p]){
                    all_less = false;
                    break;
                }
            }
            if (all_less && find(adj[d2].begin(), adj[d2].end(), d1) == adj[d2].end()){
                adj[d1].push_back(d2);
                in_deg[d2]++;
            }
            else if (all_less && find(adj[d2].begin(), adj[d2].end(), d1) != adj[d2].end()){
                //exact same!!
//                cerr << "hi\n";
                same[d1][d2] = true;
                same[d2][d1] = true;
            }
        }
    }
    vector<int> par(m);
    vector<bool> is_par(m, false);
    vector<int> top_sort;
    vector<int> in_degcpy(in_deg.begin(), in_deg.end());
    for (int i = 0; i < m; i++){
        if (in_degcpy[i] == 0){
            //start top sort
            queue<int> q; q.push(i);
            par[i] = -1;
            while (!q.empty()){
                int tp = q.front(); q.pop();
                top_sort.push_back(tp);
                for (int nd : adj[tp]){
                    in_deg[nd]--;
                    if (in_deg[nd] == 0){
                        q.push(nd);
                        if (is_par[tp]){par[nd] = -1;}
                        else {par[nd] = tp; is_par[tp] = true;}
                    }
                }
            }
        }
    }
//    for (int i = 0; i < top_sort.size(); i++){
//        cout << top_sort[i] << " ";
//    }
//    cout << "\n";
    for (int i = 0; i < m; i++){
        if (!is_par[i]){
            vector<int> grp;
            int nd = i;
            while (nd != -1){
                grp.push_back(nd);
                nd = par[nd];
            }
            reverse(grp.begin(), grp.end());
            groups.push_back(grp);
        }
    }
    vector<int> access_groups(m);
    vector<int> doc_access_levels(m);
    for (int i = 0; i < groups.size(); i++){
        for (int doc : groups[i]){
            access_groups[doc] = i+1;
        }
    }
    for (vector<int> grp : groups){
        for (int i = 0; i < grp.size(); i++){
            if (i != 0 && same[grp[i]][grp[i-1]]){
                doc_access_levels[grp[i]] = doc_access_levels[grp[i-1]];
                continue;
            }
            doc_access_levels[grp[i]] = grp.size()-i+1;
        }
    }
    vector<vector<int>> people_access_levels(n, vector<int> (groups.size()));
    for (int p = 0; p < n; p++){
        for (int grp = 0; grp < groups.size(); grp++){
            //iterate through group
            bool broken = false;
            for (int doc = groups[grp].size()-1; ~doc; doc--){
                if (!a[groups[grp][doc]][p]){
                    people_access_levels[p][grp] = doc_access_levels[groups[grp][doc]]-1;
                    broken = true;
                    break;
                }
            }
            if (!broken){
                people_access_levels[p][grp] = doc_access_levels[groups[grp].front()];
            }
        }
    }
    cout << groups.size() << "\n";
    for (int i = 0; i < m; i++){
        cout << access_groups[i] << " ";
    }
    cout << "\n";
    for (int i = 0; i < m; i++){
        cout << doc_access_levels[i] << " ";
    }
    cout << "\n";
    for (int i = 0; i < n; i++){
        for (int j = 0; j < groups.size(); j++){
            cout << people_access_levels[i][j] << " ";
        }
        cout << "\n";
    }
}
