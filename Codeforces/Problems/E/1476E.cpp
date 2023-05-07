#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;
map<int, vector<int>> adj;
vector<int> in_deg(mxN, 0);

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    vector<string> st;
    map<string, int> str_mp;
    for (int i = 0; i < n; i++){
        string s; cin >> s;
        st.push_back(s);
        str_mp[s] = i;
    }
    vector<pair<string, int>> req(m);
    for (int i = 0; i < m; i++){
        cin >> req[i].first >> req[i].second;
        req[i].second--;
    }
    for (int i = 0; i < m; i++){
        string good = st[req[i].second];
        bool is_subset = false;
        for (int mask = 0; mask < (1 << k); mask++){
            //build string
            string curr = "";
            for (int b = 0; b < k; b++){
                if ((mask >> b) & 1){
                    curr += req[i].first[b];
                }
                else{
                    curr += '_';
                }
            }
            if (curr == good){
                is_subset = true;
                continue;
            }
            else{
                if (str_mp.count(curr)){
                    adj[str_mp[good]].push_back(str_mp[curr]);
                    in_deg[str_mp[curr]]++;
                }
            }
        }
        if (!is_subset){
            cout << "NO\n";
            return 0;
        }
    }
    //kahn top sort
    vector<int> top_sort;
    queue<int> q;
    for (int i = 0; i < n; i++){
        if (in_deg[i] == 0){
            q.push(i);
        }
    }
    while (!q.empty()){
        //go through each neighbor
        int tp = q.front(); q.pop();
        top_sort.push_back(tp);
        for (int s : adj[tp]){
            if (--in_deg[s] == 0){
                q.push(s);
            }
        }
    }
    if (top_sort.size() != n){
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
    for (int i = 0; i < n; i++){
        cout << top_sort[i]+1 << " ";
    }
    cout << "\n";
}
