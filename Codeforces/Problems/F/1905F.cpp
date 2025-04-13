#include <bits/stdc++.h>
using namespace std;

#undef LOCAL

#ifdef LOCAL
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
void dbg_out() { cout << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cout << ' ' << H; dbg_out(T...); }
#define dbg(...) cout<< "LINE "<<__LINE__<<": -> [" << #__VA_ARGS__ << "]:", dbg_out(__VA_ARGS__)
#else
#define dbg(...) 7;
#endif


struct fenwick_tree{
    int n;
    vector<int> g;
    vector<int> a;

    fenwick_tree(int sz){
        this->n = sz;
        g.resize(sz);
    }

    fenwick_tree(vector<int> a){
        this->n = a.size();
        g.resize(n, 0);
        this->a = a;

        for (int i = 0; i < n; i++){
            upd(i, a[i]);
        }
    }

    void upd(int idx, int delta){
        a[idx] += delta;
        for (; idx < n; idx = (idx | (idx + 1))){
            g[idx] += delta;
        }
    }

    void set(int idx, int x){
        int delta = x - a[idx];
        upd(idx, delta);
    }

    int qry(int idx){
        int res = 0;
        for (; idx >= 0; idx = (idx & (idx + 1)) - 1){
            res += g[idx];
        }
        return res;
    }

    int qry(int fir, int las){
        return qry(las) - (fir == 0 ? 0 : qry(fir-1));
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++){
            cin >> a[i]; a[i]--;
        }

        map<int,int> val_to_idx;
        for (int i = 0; i < n; i++){
            val_to_idx[a[i]] = i;
        }

        //special case
        if (is_sorted(a.begin(), a.end())){
            cout << n-2 << "\n";
            continue;
        }

        vector<int> left_greater(n, -1); //if only one element to the left which is greater, store idx
        vector<int> right_less(n, -1); //if only one element to the right which is less, store idx
        vector<int> perm(n, -1); //if i is transported to i'th index, a[:i] is a permutation

        //case 1: k is not involved in swap
        //then, there could only be one possible (i, j) pair which makes k a good index -> stored in lg/rl
        //case 2: k is involved in swap
        //then, k must be sent where prefix is a permutation of 0...k-1 and suffix is a perm of k+1...n-1


        fenwick_tree ft(vector<int> (n, 0));
        int curr_max = -1;
        int arg_curr_max = -1;

        perm[find(a.begin(), a.end(), 0) - a.begin()] = 0;
        perm[find(a.begin(), a.end(), n-1) - a.begin()] = n-1;

        int curr_ans = 0;

        for (int i = 0; i < n; i++){
//            dbg(i, ft.qry(0, a[i]-1));
            if ((i == 0 && a[i] == 0) || (i != 0 && ft.qry(0, i-1) == i && a[i] == i)){
                curr_ans++;
            }
            if (a[i] > curr_max){
                curr_max = a[i];
                arg_curr_max = i;
            }
            ft.set(a[i], 1);
//            dbg(a[i], 1);
            if (a[i] != n-1 && ft.qry(a[i]+1, n-1) == 1){
                //there is one greater element to the left
                left_greater[i] = arg_curr_max;
            }
            if (ft.qry(0, i) == i+1 && i != n-1){
                //reached a mex point
                perm[val_to_idx[i+1]] = i+1;
                perm[val_to_idx[i]] = i;
            }
        }

//        dbg(curr_ans);

        for (int i = 0; i < n; i++){
            ft.set(i, 0);
        }

        int curr_min = n;
        int arg_curr_min = -1;

        for (int i = n-1; i >= 0; i--){
            if (a[i] < curr_min){
                curr_min = a[i];
                arg_curr_min = i;
            }
            ft.set(a[i], 1);
            if (a[i] != 0 && ft.qry(0, a[i]-1) == 1){
                right_less[i] = arg_curr_min;
            }
        }

        dbg(left_greater);
        dbg(right_less);
        dbg(perm);

        map<pair<int,int>, int> freq;
        for (int i = 0; i < n; i++){
            set<array<int, 2>> recorded;
            if (right_less[i] != -1 && left_greater[i] != -1){
                freq[{left_greater[i], right_less[i]}]++;
                recorded.insert({left_greater[i], right_less[i]});
            }
            if (perm[i] != -1){
                if (!recorded.count(array<int, 2>{min(perm[i], i), max(perm[i], i)})){
                    freq[{min(perm[i], i), max(perm[i], i)}]++;
                }
            }
        }

        int max_cnt = 0;
        for (auto &x : freq){
            if (x.first.first != x.first.second){
                max_cnt = max(max_cnt, x.second);
            }
        }

        dbg(freq);

        cout << curr_ans + max_cnt << "\n";

    }
}