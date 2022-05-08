/*
Dont raise your voice,improve your argument
--Desmond Tutu
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define all(x) x.begin(),x.end()
const ll m = (ll)1e9+7;

struct point{
    ll x, y;
    bool operator<(const point& a){
        if(y != a.y){
            return y<a.y;
        } else{
            return x<a.x;
        }
    }
};
bool operator==(const point& a, const point& b){
    return (a.x == b.x && a.y == b.y);
}

struct segment{
    point p, q;
};

bool sign(point a, point b, point c) {
    return ((c.y-a.y)*(b.x-a.x)>(b.y-a.y)*(c.x-a.x));
}
bool intersect(segment a, segment b){
    if(a.p == b.p || a.p == b.q || a.q == b.p || a.q == b.q){
        return false;
    }
    if((sign(a.p, b.p, b.q)!=sign(a.q, b.p, b.q)) && sign(a.p, a.q, b.p)!=sign(a.p, a.q, b.q)){
        return true;
    }
    else{
        return false;
    }
}
/*
*/
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    if (n == 3) {
        cout << 0 << "\n";
        return 0;
    }
    vector<point> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].x >> a[i].y;
    }

    vector<int> perm(n);
    std::iota(all(perm), 0);

    ll ans = 0;
    do {
        vector<point> pts(n);
        for (int i = 0; i < n; ++i) {
            pts[i] = a[perm[i]];
        }
        bool flag = true;
        vector<segment> seen;
        seen.push_back({pts[0], pts[1]});
        seen.push_back({pts[1], pts[2]});
        seen.push_back({pts[0], pts[2]});
        vector<int> i_freq(n, 0);
        for (int i = 3; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                bool good = true;
                segment p = {pts[i], pts[j]};
                for (auto &seg : seen) {
                    if (intersect(p, seg)) {
                        good = false;
                    }
                }
                if (good) {
                    seen.push_back(p);
                    i_freq[i]++;
                }
            }
        }
        for (int i = 3; i < n; ++i) {
            if (i_freq[i] != 3) {
                flag = false;
            }
        }
        if (flag) {
            ans++;
        }
    } while (next_permutation(all(perm)));
    cout << ans << "\n";
}
