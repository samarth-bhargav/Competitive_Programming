#include <bits/stdc++.h>

using namespace std;

const int mxN = 4e3;
bool adj[mxN][mxN];

struct dsu{
    vector<int> p;
    dsu(int n){
        p.resize(n);
        iota(p.begin(), p.end(), 0);
    }
    int find(int x){
        return x == p[x] ? x : p[x] = find(p[x]);
    }
    bool join(int a, int b){
        a = find(a);
        b = find(b);
        if (a == b) return false;
        p[a] = b;
        return true;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    for (int tt = 0; tt < t; tt++){
        int n; cin >> n;
//        for (int i = 0; i < n; i++){
//            for (int j = 0; j < n; j++){
//                adj[i][j] = false;
//            }
//        }
        dsu d(n);
        for (int i = 0; i < n; i++){
            string s; cin >> s;
            for (int j = 0; j < n; j++){
                if (s[j] == '1'){
                    d.join(i, j);
                    adj[i][j] = 1;
                }
                else{
                    adj[i][j] = 0;
                }
            }
        }
//        if (n == 5 && tt == 55){
//            for (int i = 0; i < n; i++){
//                for (int j = 0; j < n; j++){
//                    cout << adj[i][j];
//                }
//                cout << "\n";
//            }
//            return 0;
//        }
//        if (n == 5){
//            continue;
//        }
        map<int, vector<int>> cc;
        for (int i = 0; i < n; i++){
            cc[d.find(i)].push_back(i);
        }
        if (cc.size() == 1){
            cout << 0 << "\n";
            continue;
        }
        //go through each one
        bool all_clique = true;
        int bad = 1e9;
        int min_size = 1e9;
        int min_clique = -1;
        for (pair<int, vector<int>> k : cc){
            bool clique = true;
            if (!all_clique){
                //takes one operation
                break;
            }
            for (int i = 0; i < k.second.size(); i++){
                if (!clique){
                    all_clique = false;
                    break;
                }
                for (int j = i+1; j < k.second.size(); j++){
                    if (!adj[k.second[i]][k.second[j]]){
                        bad = k.second[i];
                        clique = false;
                        break;
                    }
                }
            }
            if (clique){
                if ((int)k.second.size() < min_size){
                    min_size = (int)k.second.size();
                    min_clique = k.first;
                }
            }
        }
        if (!all_clique){
            cout << 1 << "\n";
            //look at the "bad" component
            vector<int> bad_cc = cc[d.find(bad)];
            //check if there's any node with all connections
            bool good = false;
            for (int i = 0; i < bad_cc.size(); i++){
                bool not_good = false;
                for (int j = 0; j < bad_cc.size(); j++){
                    if (j == i) continue;
                    if (!adj[bad_cc[i]][bad_cc[j]]){
                        not_good = true;
                        break;
                    }
                }
                if (!not_good){
                    good = true;
                    break;
                }
            }
            if (good){
                //theres a node with all connections
                cout << bad+1 << "\n";
            }
            else{
                //consider spanning tree
                dsu st(n);
                vector<int> st_adj[n];
                for (int i = 0; i < bad_cc.size(); i++){
                    for (int j = i+1; j < bad_cc.size(); j++){
                        if (adj[bad_cc[i]][bad_cc[j]]){
                            if (st.join(bad_cc[i], bad_cc[j])){
                                st_adj[bad_cc[i]].push_back(bad_cc[j]);
                                st_adj[bad_cc[j]].push_back(bad_cc[i]);
                            }
                        }
                    }
                }
                for (int i = 0; i < n; i++){
                    if (st_adj[i].size() == 1){
                        cout << i+1 << "\n";
                        break;
                    }
                }
            }
        }
        else if (cc.size() >= 3){
            if (min_size == 1){
                cout << 1 << "\n";
                cout << min_clique+1 << "\n";
            }
            else{
                cout << 2 << "\n";
                cout << cc.begin()->second[0] + 1 << " " << (next(cc.begin()))->second[0] + 1 << "\n";
            }
        }
        else{
            cout << min_size << "\n";
            for (int x : cc[min_clique]){
                cout << x + 1 << " ";
            }
            cout << "\n";
        }
    }
}