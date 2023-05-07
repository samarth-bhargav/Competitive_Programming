#include <bits/stdc++.h>
using namespace std;

#define int long long
const int L = 18;
const int mxM = 1e5;

struct avg{
    long long num, denom;
    int id;
    avg(long long n, long long d, int id){
        num = n; denom = d;
        this->id = id;
    }
    avg(){}
    bool operator <(const avg &o) const{
        return num * o.denom < o.num * denom;
    }
};

bool ge(long long x, avg y){
    return x * y.denom >= y.num;
}

bool i1[mxM][L], d1[mxM][L], eq[mxM][L];
bool eqry(int lb, int rb){
    if (lb > rb) return true;
    int diff = rb - lb + 1;
    bool ret = true;
    for (int i = 0; i < L; i++){
        if ((diff >> i) & 1){
            ret &= (eq[lb][i]);
            lb += (1 << i);
            if (!ret) return false;
        }
    }
    return true;
}
bool dqry(int lb, int rb){
    if (lb > rb) return true;
    int diff = rb - lb + 1;
    bool ret = true;
    for (int i = 0; i < L; i++){
        if ((diff >> i) & 1){
            ret &= (d1[lb][i]);
            lb += (1 << i);
            if (!ret) return false;
        }
    }
    return true;
}
bool iqry(int lb, int rb){
    if (lb > rb) return true;
    int diff = rb - lb + 1;
    bool ret = true;
    for (int i = 0; i < L; i++){
        if ((diff >> i) & 1){
            ret &= (i1[lb][i]);
            lb += (1 << i);
            if (!ret) return false;
        }
    }
    return true;
}

int32_t main(){
    int t;
    cin >> t;
    while (t--){
        int n, m; cin >> n >> m;
        vector<int> a(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        a = vector<int> (a.begin() + n - m, a.end());
        assert(a.size() == m);
        vector<vector<int>> b(m);
        vector<array<int, 2>> student;
        for (int i = 0; i < m; i++){
            int k; cin >> k;
            for (int j = 0; j < k; j++){
                int x; cin >> x;
                b[i].push_back(x);
                student.push_back({x, i});
            }
        }
        vector<avg> avgs(m);
        for (int i = 0; i < m; i++){
            long long temp = 0;
            for (int j : b[i]){
                temp += j;
            }
            avgs[i] = avg(temp, b[i].size(), i);
        }
        map<int, int> id_to_avgs;
        sort(avgs.begin(), avgs.end());
        for (int i = 0; i < m; i++){
            id_to_avgs[avgs[i].id] = i;
        }
        for (int i = 0; i < m; i++){
            for (int j = 0; j < L; j++){
                eq[i][j] = true;
                i1[i][j] = true;
                d1[i][j] = true;
            }
        }
        for (int i = 0; i < m; i++){
            eq[i][0] = ge(a[i], avgs[i]);
            if (i != m-1){
                i1[i][0] = ge(a[i], avgs[i+1]);
            }
            if (i != 0){
                d1[i][0] = ge(a[i], avgs[i-1]);
            }
        }
        for (int j = 1; j < L; j++){
            for (int i = 0; i < m; i++){
                eq[i][j] = (eq[i][j-1] & eq[i+(1<<(j-1))][j-1]);
                i1[i][j] = (i1[i][j-1] & i1[i+(1<<(j-1))][j-1]);
                d1[i][j] = (d1[i][j-1] & d1[i+(1<<(j-1))][j-1]);
            }
        }

        for (int s = 0; s < student.size(); s++){
            avg curr = avgs[id_to_avgs[student[s][1]]];
            curr.num -= student[s][0];
            curr.denom--;
            //binary search to find pos
            int old_pos = id_to_avgs[student[s][1]];
            int new_pos = lower_bound(avgs.begin(), avgs.end(), curr) - avgs.begin();
            if (new_pos == n || new_pos > old_pos){
                new_pos--;
            }
            if (new_pos < old_pos){
                //shifted backward
                bool good = true;
                good &= dqry(new_pos+1, old_pos);
                good &= ge(a[new_pos], curr);
                good &= eqry(0, new_pos-1);
                good &= eqry(old_pos+1, m-1);
                cout << (good ? 1 : 0);
            }
            else if (new_pos == old_pos){
                bool good = true;
                good &= ge(a[new_pos], curr);
                good &= eqry(0, new_pos-1);
                good &= eqry(new_pos+1, m-1);
                cout << (good ? 1 : 0);
            }
            else{
                bool good = true;
                good &= eqry(0, old_pos-1);
                good &= iqry(old_pos, new_pos-1);
                good &= ge(a[new_pos], curr);
                good &= eqry(new_pos+1, m-1);
                cout << (good ? 1 : 0);
            }
        }
        cout << "\n";
    }
}
