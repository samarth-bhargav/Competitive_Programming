#include <bits/stdc++.h>
using namespace std;

int rnd(int l, int r) {
    return l + (rand() * rand()) % (r - l + 1);
}

int main(){
    srand(time(NULL));
    std::random_device rd;
    std::mt19937 g(rd());
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    for (int tt = 0; tt < 1000; tt++){
        int n;
//        cin >> n;
        n = 8;
        vector<int> a(n);
        for (int i = 0; i < n; i++){
//            cin >> a[i];
            a[i] = rnd(1, 10);
        }

        auto brute = [&](auto self, vector<int> a, bool mi) -> int{
            if (a.size() == 1){
                return a[0];
            }
            int ans = 0;
            for (int i = 0; i < a.size()-1; i++){
                vector<int> aa = a;
                if (mi){
                    aa[i] = min(a[i], a[i+1]);
                }
                else{
                    aa[i] = max(a[i], a[i+1]);
                }
                aa.erase(aa.begin() + i + 1);
                ans = max(ans, self(self, aa, mi ^ 1));
            }
            return ans;
        };

        long long ans = 0;

        for (int i = 0; i < n; i++){
            multiset<int> elems;
            for (int j = i; j < n; j++){
                elems.insert(a[j]);
                if (j - i + 1 >= 5){
                    if ((j - i + 1) % 2 == 0){
                        ans += (long long)(*prev(prev(elems.end())));
                        if (*prev(prev(elems.end())) != brute(brute, vector<int> (a.begin() + i, a.begin() + j + 1), 1)){
                            for (int k = i; k <= j; k++){
                                cerr << a[k] << " ";
                            }
                            cerr << endl;
                            assert(false);
                        }
                    }
                    else{
                        ans += (long long)(*prev(elems.end()));
                        if (*prev(elems.end()) != brute(brute, vector<int> (a.begin() + i, a.begin() + j + 1), 1)){
                            for (int k = i; k <= j; k++){
                                cerr << a[k] << " ";
                            }
                            cerr << endl;
                            assert(false);
                        }
                    }
                }
                else{
                    ans += brute(brute, vector<int>(a.begin() + i, a.begin() + j + 1), 1);
                }
            }
        }
        cout << ans << "\n";
    }




    auto translate = [&](vector<int> a){
        set<int> s;
        for (int x : a){
            s.insert(x);
        }
        vector<int> t(s.size());
        int i = 0;
        map<int,int> mp;
        for (int x : s){
            t[i] = x;
            mp[x] = i;
            i++;
        }
        for (int j = 0; j < a.size(); j++){
            a[j] = mp[a[j]];
        }
        return make_pair(a, t);
    };




    map<pair<vector<int>, int>, int> LOOKUP;
    LOOKUP[make_pair(vector<int>{0}, 0)] = 0;
    LOOKUP[make_pair(vector<int>{0}, 1)] = 0;

    auto brute = [&](auto self, vector<int> a, bool mi) -> int{
        auto [x, y] = translate(a);
        a = x;
        if (LOOKUP.count(make_pair(a, mi))){
            return y[LOOKUP[make_pair(a, mi)]];
        }
        int ans = 0;
        for (int i = 0; i < a.size()-1; i++){
            vector<int> aa = a;
            if (mi){
                aa[i] = min(a[i], a[i+1]);
            }
            else{
                aa[i] = max(a[i], a[i+1]);
            }
            aa.erase(aa.begin() + i + 1);
            ans = max(ans, self(self, aa, mi ^ 1));
        }
        LOOKUP[make_pair(a, mi)] = ans;
        return y[ans];
    };







    vector<int> left_geq(n, -1), right_g(n, n);

    stack<int> st;
    for (int i = 0; i < n; i++){
        while (!st.empty() && a[i] > a[st.top()]){
            st.pop();
        }
        if (!st.empty()){
            left_geq[i] = st.top();
        }
        st.push(i);
    }

    while (!st.empty()){
        st.pop();
    }

    for (int i = n-1; ~i; i--){
        while (!st.empty() && a[i] >= a[st.top()]){
            st.pop();
        }
        if (!st.empty()){
            right_g[i] = st.top();
        }
        st.push(i);
    }

    while (!st.empty()){
        st.pop();
    }
}


