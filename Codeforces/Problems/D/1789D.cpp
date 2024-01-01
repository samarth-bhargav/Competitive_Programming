#include <bits/stdc++.h>

using namespace std;

const int mxN = 2000;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    bitset<mxN> a;
    bitset<mxN> b;
    a.reset(); b.reset();

    int t; cin >> t;
    for (int tt = 0; tt < t; tt++){
        int n; cin >> n;
        string s1, s2; cin >> s1 >> s2;
        for (int i = 0; i < n; i++){
            if (s1[n-1-i] == '0') a.set(i, 0);
            else{
                a.set(i, 1);
            }

            if (s2[n-1-i] == '0') b.set(i, 0);
            else b.set(i, 1);
        }
        auto equal = [&](){
            bool bad = false;
            for (int i = 0; i < n; i++){
                if (a.test(i) != b.test(i)){
                    bad = true; break;
                }
            }
            return !bad;
        };
        if (equal()){
            cout << 0 << "\n";
            continue;
        }
        bool solved = false;
        vector<int> ops;
        for (int iter = 0; iter < 2; iter++){
            if (iter == 1){
                ops.clear();
                a.reset(); b.reset();
                for (int i = 0; i < n; i++){
                    if (s1[i] == '0') a.set(i, 0);
                    else{
                        a.set(i, 1);
                    }

                    if (s2[i] == '0') b.set(i, 0);
                    else b.set(i, 1);
                }
            }
            int r1 = -1;
            for (int i = 0; i < n; i++){
                if (a.test(n-i-1)){
                    r1 = max(r1, i);
                }
            }
            if (r1 == -1){
                cout << -1 << "\n";
                solved = true;
                break;
            }
            int l1 = n;
            r1 = n - 1 - r1;
            for (int i = r1+1; i < n; i++){
                if (a.test(i) != b.test(i)){
                    ops.push_back(i - r1);
                    a ^= (a << ops.back());
                }
            }
            for (int j = n; j < 2000; j++){
                a.set(j, 0);
            }
            for (int i = n-1; ~i; i--){
                if (a.test(i) == 1){
                    l1 = i; break;
                }
            }
            for (int i = r1 - (l1 == r1); ~i; i--){
                if (a.test(i) != b.test(i)){
                    ops.push_back(i - l1);
                    a ^= (a >> -ops.back());
                }
            }
            if (!equal()){
                continue;
            }
            cout << ops.size() << "\n";
            for (int i = 0; i < ops.size(); i++){
                cout << ops[i] * (iter == 1 ? -1 : 1) << " ";
            }
            cout << "\n";
            solved = true;
            break;
        }
        if (!solved){
            cout << -1 << "\n";
        }
        a.reset(); b.reset();
    }
}