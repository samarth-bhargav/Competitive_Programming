#include <bits/stdc++.h>
using namespace std;

#define int long long
int ans = 0;
vector<int> total_items_pf;
vector<pair<int, bool>> total_items;

struct dsu{
    int n;
    vector<int> p, answer, sz, mx, num_n;
    dsu(int n){
        this->n = n;
        this->p.resize(n);
        this->sz.resize(n);
        this->mx.resize(n);
        this->num_n.resize(n);
        this->answer.resize(n);
        for (int i = 0; i < n; i++){
            sz[i] = 1;
            num_n[i] = total_items[i].second ? 1 : 0;
            p[i] = i;
            mx[i] = total_items[i].first;
            answer[i] = num_n[i] ? total_items[i].first : 0;
            ans += answer[i];
        }
    }
    int find(int x){
        return x==p[x] ? p[x] : p[x] = find(p[x]);
    }
    void join(int a, int b){
        a = find(a);
        b = find(b);
        if (a == b){
            return;
        }
        if (sz[a] > sz[b]){
            swap(a, b);
        }
        p[a] = b;
        mx[b] = max(mx[b], mx[a]);
        num_n[b] += num_n[a];
        sz[b] += sz[a];
        ans -= answer[a];
        ans -= answer[b];
        int idx = prev(upper_bound(total_items.begin(), total_items.end(),
                                   make_pair(mx[b], true))) - total_items.begin() + 1;
        answer[b] = total_items_pf[idx] - total_items_pf[idx - num_n[b]];
        ans += answer[b];
    }
};

int32_t main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m, q;
    cin >> n >> m >> q;
    total_items_pf.resize(n+m+1);
    for (int i = 0; i < n; i++){
        int x; cin >> x;
        total_items.emplace_back(x, 1);
    }
    for (int i = 0; i < m; i++){
        int x; cin >> x;
        total_items.emplace_back(x, 0);
    }

    sort(total_items.begin(), total_items.end());
    map<int, vector<int>> differences;
    for (int i = 1; i < n+m; i++){
        if (differences.find(total_items[i].first - total_items[i-1].first) == differences.end())
            differences[total_items[i].first - total_items[i-1].first] = vector<int>(0);
        differences[total_items[i].first - total_items[i-1].first].push_back(i-1);
    }

    total_items_pf[0] = 0;
    for (int i = 1; i <= n+m; i++){
        total_items_pf[i] = total_items_pf[i-1] + total_items[i-1].first;
    }
    dsu d(n+m);

    vector<int> solutions(q);
    vector<pair<int, int>> queries(q);
    for (int qq = 0; qq < q; qq++){
        cin >> queries[qq].first;
        queries[qq].second = qq;
    }
    sort(queries.begin(), queries.end());
    auto it1 = differences.begin();
    for (int qq = 0; qq < q; qq++){
        for (; it1 != differences.end() && it1->first <= queries[qq].first; it1++){
            for (int x : it1->second){
                d.join(x, x+1);
            }
        }
        solutions[queries[qq].second] = ans;
    }
    for (int i = 0; i < q; i++){
        cout << solutions[i] << "\n";
    }
}