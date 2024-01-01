#include <bits/stdc++.h>

using namespace std;

#define dbg(x) cerr << #x << ": "; for (int i : x){cerr << i << " ";} cerr << endl;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    bool flipped = false;

    int n, m; cin >> n >> m;

    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    for (int i = 0; i < m; i++){
        cin >> b[i];
    }
    if (n < m){
        flipped = true;
        swap(n, m);
        swap(a, b);
    }
    //initial op: get 1

    auto indexOf = [&](vector<int> arr, int x) -> int{
        return find(arr.begin(), arr.end(), x) - arr.begin();
    };

    auto do_op = [&](vector<int> arr, int x){
        vector<int> ret;
        ret.insert(ret.end(), arr.begin()+x+1, arr.end());
        ret.push_back(arr[x]);
        ret.insert(ret.end(), arr.begin(), arr.begin()+x);
        return ret;
    };

    int a1_idx = indexOf(a, 1), b1_idx = indexOf(b, 1);
    vector<int> a_ops, b_ops;
    a_ops.reserve(4 * n); b_ops.reserve(4 * n);
    if (a1_idx != 0){
        a_ops.push_back(a1_idx - 1);
        a = do_op(a, a_ops.back());
    }
    if (b1_idx != 0){
        b_ops.push_back(b1_idx - 1);
        b = do_op(b, b_ops.back());
    }
//    dbg(a); dbg(b);
    for (int i = 1; i < max(n, m); i++){
        //get ith index right
        a_ops.push_back(indexOf(a, i+1));
        a = do_op(a, a_ops.back());
        int i_idx = indexOf(a, i);
        if (i_idx != n-1){
            a_ops.push_back(i_idx+1);
            a = do_op(a, a_ops.back());
        }
        a_ops.push_back(indexOf(a, i+1));
        a = do_op(a, a_ops.back());

        if (i < m) {
            b_ops.push_back(indexOf(b, i+1));
            b = do_op(b, b_ops.back());
            i_idx = indexOf(b, i);
            if (i_idx != m-1){
                b_ops.push_back(i_idx+1);
                b = do_op(b, b_ops.back());
            }
            b_ops.push_back(indexOf(b, i+1));
            b = do_op(b, b_ops.back());
        }
//        dbg(a); dbg(b);
    }
//    dbg(a); dbg(b);
//    cerr << a_ops.size() << " " << b_ops.size() << "\n";
    assert(is_sorted(a.begin(), a.end()) && is_sorted(b.begin(), b.end()));

    if (abs((int)a_ops.size() - (int)b_ops.size()) % 2 == 1){
        if (a.size() % 2 == 0 && b.size() % 2 == 0){
            cout << -1 << "\n";
            return 0;
        }
        if (a.size() % 2 == 1){
            for (int i = 0; i < a.size(); i++){
                a_ops.push_back(0);
            }
        }
        else{
            for (int i = 0; i < b.size(); i++){
                b_ops.push_back(0);
            }
        }
    }
    if (a_ops.size() < b_ops.size()){
        int diff = b_ops.size() - a_ops.size();
        for (int i = 0; i < diff / 2; i++){
            a_ops.push_back(0);
            a_ops.push_back(n-1);
        }
    }
    else if (b_ops.size() < a_ops.size()){
        int diff = a_ops.size() - b_ops.size();
        for (int i = 0; i < diff / 2; i++){
            b_ops.push_back(0);
            b_ops.push_back(m-1);
        }
    }

    if (flipped) swap(a_ops, b_ops);
    cout << a_ops.size() << "\n";
    for (int i = 0; i < a_ops.size(); i++){
        cout << a_ops[i]+1 << " " << b_ops[i]+1 << "\n";
    }
    cout << "\n";
}