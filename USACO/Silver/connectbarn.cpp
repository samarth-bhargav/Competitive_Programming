//babybeluga
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/
const int mxN = 1e5;
int t, n, m;

struct dsu{
    int p[mxN], mxs[mxN], mns[mxN];
    void init(){
        for (int i = 0; i < n; i++){
            p[i] = i;
            mxs[i] = i;
            mns[i] = i;
        }
    }
    int find(int x){
        return p[x]==x ? x : p[x] = find(p[x]);
    }
    int find_max(int a){
        return mxs[find(a)];
    }
    int find_min(int a){
        return mns[find(a)];
    }
    void join(int a, int b){
        int x = find(a);
        int y = find(b);
        mxs[x] = max(mxs[x],mxs[y]);
        mxs[y] = max(mxs[x],mxs[y]);
        mns[x] = min(mns[x],mns[y]);
        mns[y] = min(mns[x],mns[y]);
        p[x] = y;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> t;
    while (t--){
        dsu d;
        cin >> n >> m;
        d.init();
        for (int i = 0; i < m; i++){
            int a,b;
            cin >> a >> b; a--; b--;
            d.join(a,b);
        }
        set<int>heads;
        for (int i = 0; i < n; i++){
            heads.insert(d.find(i));
        }
        int firsthead = d.find(0);
        int lasthead = d.find(n-1);
        if (firsthead == lasthead){
            return
        }
        int firstc = d.find_max(firsthead);
        int lastc = d.find_min(lasthead);
        ll ans;
        if (firstc - lastc % 2 == 0){
            int len = (firstc - lastc)/2;
            ans = len*len*2;
        }
        else{
            int len = (abs(firstc-lastc))/2;
            ans = len*len + (len+1)*(len+1);
        }
        for (auto & i : heads){
            if (i == firsthead || i == lasthead){
                continue;
            }
            int connection1 = d.find_min(i);
            int connection2 = d.find_max(i);
            ll curr = (connection1 - firstc)*(connection1 - firstc) + (connection2 - lastc)*(connection2 - lastc);
            ans = min(ans,curr);
        }
        cout << ans << "\n";
    }
}

