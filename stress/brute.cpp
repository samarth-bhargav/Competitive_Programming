#include <bits/stdc++.h>
using namespace std;

template <class T> using V = vector<T>;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    V<int> P(N);
    for (auto &t : P) {
        cin >> t;
        --t;
    }
    V<int> pos(N);
    for (int i = 0; i < N; ++i)
        pos[P[i]] = i;
    V<V<pair<int, char>>> to_ins(N + 1);
    V<V<int>> to_del(N + 1);
    { // process "LO"s from lowest to highest, record insertions and deletions
        stack<int> cur;
        for (int i = 0; i < N; ++i) {
            while (!cur.empty() && cur.top() > pos[i]) {
                to_del.at(i + 1).push_back(cur.top());
                cur.pop();
            }
            cur.push(pos[i]);
            to_ins.at(i + 1).push_back({pos[i], 'L'});
        }
    }
    { // process "HI"s from highest to lowest, record insertions and deletions
        stack<int> cur;
        for (int i = N - 1; i >= 0; --i) {
            while (!cur.empty() && cur.top() > pos[i]) {
                to_ins.at(i + 1).push_back({cur.top(), 'H'});
                cur.pop();
            }
            cur.push(pos[i]);
            to_del.at(i + 1).push_back(pos[i]);
        }
        while (!cur.empty()) {
            to_ins.at(0).push_back({cur.top(), 'H'});
            cur.pop();
        }
    }
    int ans = 0;
    map<int, char> m; // maps each position to 'H' or 'L'
    auto hilo = [&](map<int, char>::iterator it,
                    map<int, char>::iterator next_it) {
        return it->second == 'H' && next_it->second == 'L';
    };
    auto get_dif = [&](map<int, char>::iterator it) {
        int dif = 0;
        if (it != begin(m))
            dif += hilo(prev(it), it);
        if (next(it) != end(m))
            dif += hilo(it, next(it));
        if (it != begin(m) && next(it) != end(m))
            dif -= hilo(prev(it), next(it));
        return dif;
    };
    for (int i = 0; i <= N; ++i) { // to finish, go from lowest to highest again
        for (auto &t : to_del.at(i)) {
            auto it = m.find(t);
            assert(it != end(m));
            ans -= get_dif(it);
            m.erase(it);
        }
        for (auto &t : to_ins.at(i)) {
            auto it = m.insert(t).first;
            assert(it->second);
            ans += get_dif(it);
        }
        cout << ans << "\n";
    }
}