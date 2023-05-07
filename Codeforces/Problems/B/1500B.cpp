#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll

int gcd(int a, int b, int& x, int& y) {
    x = 1, y = 0;
    int x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1) {
        int q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return a1;
}

int32_t main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m; ll k;
    cin >> n >> m >> k;
    vector<int> a(n), b(m);
    map<int, int> a_pos, b_pos;

    for (int i = 0; i < n; i++){
        cin >> a[i];
        a_pos[a[i]] = i;
    }
    for (int i = 0; i < m; i++){
        cin >> b[i];
        b_pos[b[i]] = i;
    }

    set<int> cong;

    ll lcm = (n * m) / __gcd(n, m);
    for (int i = 0; i < n; i++){
        if (b_pos.find(a[i]) != b_pos.end()){
            int j = b_pos[a[i]];
            // x = i mod n, x = j mod m
            // x = nx' + i, x = my' + j
            // nx' + i = my' + j
            // nx' - my' = j - i, first check if gcd(n, m) | j - i
            if ((j - i) % __gcd(n, m) != 0){
                continue;
            }
            int x, y;
            gcd(n, -m, x, y);
            if (n * x - m * y == -__gcd(n, m)){
                x = -x; y = -y;
            }
            //scale up x and y
            x *= ((j - i) / __gcd(n, m));
            y *= ((j - i) / __gcd(n, m));
            //push actual solution
            cong.insert(((n * x + i) % lcm + lcm) % lcm);
            if (((n * x + i) % lcm + lcm) % lcm == 41){
                cerr << i << " " << j << "\n";
            }
        }
    }
//    cerr << b_pos[14] << "\n";
    ll ops = 0;
    ops += lcm * ((k-1) / (lcm - cong.size()));
    ll num_left = k - ((lcm - cong.size()) * ((k-1) / (lcm - cong.size())));
    cong.insert(-1);
    for (auto it = next(cong.begin()); it != cong.end(); it++){
        if (*it - *prev(it) - 1 >= num_left){
            ops += (*prev(it) + num_left + 1);
            num_left = 0;
            break;
        }
        else{
            num_left -= (*it - *prev(it) - 1);
        }
    }
    if (num_left != 0){
        ops += *prev(cong.end()) + num_left + 1;
    }
    cout << ops << "\n";
}
