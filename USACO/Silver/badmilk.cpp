/*
ID: samarth10
LANG: C++11
TASK: 
*/
#include <bits/stdc++.h>

using namespace std;


void setIO(string name) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen((name + ".in").c_str(), "r", stdin);
    freopen((name + ".out").c_str(), "w", stdout);
}


int main() {
    setIO("badmilk");
    vector <int> pos;
    int n,m,d,s;
    cin >> n >> m >> d >> s;
    vector <vector <bool>> vb(n, vector <bool> (m));
    set <int> poss;
    vector <int> num(m,0);
    vector < vector <int>> put;
    for (int i = 0; i < d; i++){
        int p,u,t;
        cin >> p >> u >> t; //p is person, u is milk, t is time
        num[u-1]++;
        vb[p-1][u-1] = true;
        vector <int> vi;
        vi.push_back(p);
        vi.push_back(u);
        vi.push_back(t);
        put.push_back(vi);
    }
    for (int i = 0; i < s; i++){
        int x,y;
        cin >> x >> y;
        for (int k  = 0; k < put.size(); k++){
            if (put[k][0] == x){
                if (put[k][2] <= y){
                    //if every single sick person drank the bad milk
                    pos.push_back(put[k][1]);
                }
            }
        }
    }
    for (int i = 0; i < pos.size(); i++){
        bool alg = true;
        for (int k = 0; k < vb.size(); k++){
            if (vb[k][pos[i] - 1] == false){
                alg = false;
                pos.erase(pos.begin() + i);
                break;
            }
        }
    }
    int maxn = 0;
    for (int i = 0; i < pos.size(); i++){
        maxn = max(maxn, num[pos[i] - 1]);
    }
    cout << maxn << "\n";
}

