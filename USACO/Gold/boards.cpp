#include <bits/stdc++.h>
using namespace std;

//#define int long long
vector<pair<int,int>> startpoints; // (y coordinate, x coordinate)
vector<pair<int,int>> endpoints; // (x coordinate, y coordinate)
map<pair<int,int>, pair<int,int>> starttoend;
map<pair<int,int>, pair<int,int>> endtostart;
const int INF = 2000000001;


struct stmin{
    vector<int> t;
    vector<int> a;
    int sz;
    stmin(){}
    stmin(vector<int> a){
        this->a = a;
        this->sz = a.size();
        t.resize(4*sz);
        bld(1, 0, sz-1);
    }
    void bld(int v, int tl, int tr){
        if (tl == tr){
            t[v] = a[tl];
            return;
        }
        int tm = (tl + tr) / 2;
        bld(v*2, tl, tm);
        bld(v*2+1, tm+1, tr);
        if (t[v*2] < t[v*2+1]){
            t[v] = t[v*2];
        }
        else{
            t[v] = t[v*2+1];
        }
    }
    int qry(int l, int r){
        return qry(1, 0, sz-1, l, r);
    }
    int qry(int v, int tl, int tr, int l, int r){
        if (l > r){
            return INF;
        }
        if (l == tl && r == tr){
            return t[v];
        }
        int tm = (tl + tr) / 2;
        int i1 = qry(v*2, tl, tm, l, min(r, tm));
        int i2 = qry(v*2+1, tm+1, tr, max(l, tm+1), r);
        return min(i1, i2);
    }
    void upd(int pos, int new_val){
        upd(1, 0, sz-1, pos, new_val);
    }
    void upd(int v, int tl, int tr, int pos, int new_val){
        if (tl == tr){
            a[pos] = new_val;
            t[v] = new_val;
            return;
        }
        int tm = (tl + tr) / 2;
        if (tm >= pos){
            upd(v*2, tl, tm, pos, new_val);
            if (t[v*2] < t[v*2+1]){
                t[v] = t[v*2];
            }
            else{
                t[v] = t[v*2+1];
            }
        }
        else{
            upd(v*2+1, tm+1, tr, pos, new_val);
            if (t[v*2] < t[v*2+1]){
                t[v] = t[v*2];
            }
            else{
                t[v] = t[v*2+1];
            }
        }
    }
};

int main(){
    ifstream cin("boards.in");
    ofstream cout("boards.out");
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, p;
    cin >> n >> p;
    for (int i = 0; i < p; i++){
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        startpoints.emplace_back(y1, x1);
        endpoints.emplace_back(x2, y2);
        starttoend[{x1,y1}] = {x2,y2};
        endtostart[{x2,y2}] = {x1,y1};
    }
    sort(endpoints.rbegin(), endpoints.rend());
    sort(startpoints.begin(), startpoints.end());

    stmin st(vector<int> (p, INF));
    priority_queue<pair<pair<int,int>, int>> pq; //xcoord, ycoord, path len

    for (int i = 0; i < p; i++) {
        int end_x = endpoints[i].first;
        int end_y = endpoints[i].second;
        //first add everything from pq
        while (!pq.empty() && pq.top().first.first >= end_x){
            //find index position in startpoints
            int idx = lower_bound(startpoints.begin(), startpoints.end(), make_pair(pq.top().first.second, pq.top().first.first)) - startpoints.begin();
            st.upd(idx, pq.top().second + pq.top().first.first + pq.top().first.second);
            pq.pop();
        }
        //all right points have been added
        int spoint_idx = lower_bound(startpoints.begin(), startpoints.end(), make_pair(end_y, end_x)) - startpoints.begin();
        int optimal = spoint_idx == p ? INF: st.qry(spoint_idx, p-1);
        if (optimal == INF){
            //no processed points that have y coord above
            //this means you have to walk all the way to n; no more springboard
            pair<int, int> startpoint = endtostart[{end_x, end_y}];
            pq.push(make_pair(startpoint, n-end_x + n-end_y));
        }
        else{
            //we DO have an optimal :D
            pair<int,int> startpoint = endtostart[{end_x, end_y}];
            pq.push(make_pair(startpoint, optimal - end_x - end_y));
        }
    }
    while (!pq.empty()){
        //find index position in startpoints
        int idx = lower_bound(startpoints.begin(), startpoints.end(), make_pair(pq.top().first.second, pq.top().first.first)) - startpoints.begin();
        st.upd(idx, pq.top().second + pq.top().first.first + pq.top().first.second);
        pq.pop();
    }
    int ans = 2e9+1;
    for (int i = 0; i < p; i++){
        ans = min(ans, st.a[i]);
    }
    cout << ans << "\n";
}