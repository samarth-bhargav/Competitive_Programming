#include <bits/stdc++.h>
using namespace std;

#define int long long
const int M = 1e9+7;

int n, m;
array<int, 3> isec(array<int, 2> pos, array<int, 2> dir){
    int d1, d2;
    d1 = (dir[0] == -1) ? pos[0] - 1 : n - pos[0];
    d2 = (dir[1] == -1) ? pos[1] - 1 : m - pos[1];
    if (d1 < d2){
        return {pos[0] + dir[0]*d1, pos[1] + dir[1]*d1, 1};
    }
    else if (d1 == d2){
        return {pos[0] + dir[0]*d1, pos[1] + dir[1]*d1, 2};
    }
    else{
        return {pos[0] + dir[0]*d2, pos[1] + dir[1]*d2, 3};
    }
}
bool in_middle(int a, int b, int c){
    if (a > c) swap(a, c);
    return a <= b && b <= c;
}
long long binpow(long long a, long long b) {
    a %= M;
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % M;
        a = a * a % M;
        b >>= 1;
    }
    return res;
}
long long mod_inv(long long a){
    return binpow(a, M-2);
}

long long compute(int a, int c, array<int, 2> prob, array<int, 2> prob_c){
    int num1 = prob[0];
    num1 = ((num1 * a) % M + M) % M;
    num1 = (num1 * binpow(prob_c[0], a-1)) % M;
    num1 = (num1 * binpow(prob_c[1], c)) % M;
    num1 = (num1 + M) % M;
    int denom1 = (prob[1] * binpow(prob_c[1], c + a - 1)) % M;
    int mid = (binpow(prob_c[0], c)) % M;
    denom1 = ((denom1 - mid) % M + M) % M;
    int num2 = ((prob[0] * c) % M + M) % M;
    num2 = (num2 * binpow(prob_c[0], a+c-1)) % M;
    num2 = (num2 * binpow(prob_c[1], 2 * c)) % M;
    int denom2 = (prob[1] * binpow(prob_c[1], a+c-1)) % M;
    mid = binpow(prob_c[1], 2 * c);
    mid = (mid - ((2 * binpow(prob_c[0], c)) % M * binpow(prob_c[1], c)) % M) % M;
    mid = (mid + binpow(prob_c[0], 2 * c)) % M;
    denom2 = ((denom2 * mid) % M + M) % M;
    int val1 = (num1 * binpow(denom1, M-2)) % M;
    val1 = (val1 + M) % M;
    int val2 = (num2 * binpow(denom2, M-2)) % M;
    val2 = (val2 + M) % M;
    cerr << num1 << "/" << denom1 << " " << num2 << "/" << denom2 << "\n";
    return ((val1 + val2) % M + M) % M;
}

int32_t main(){
    int t;
    cin >> t;
    while (t--){
        int rb, cb, rd, cd, p;
        cin >> n >> m >> rb >> cb >> rd >> cd >> p;
        int x = 1, y = 1;
        vector<array<int, 2>> cycle;
        cycle.push_back({rb, cb});
        array<int, 2> curr;
        while (true){
            array<int, 3> intersect = isec(cycle.back(), {x,y});
            if (intersect[0] == cycle[0][0] && intersect[1] == cycle[0][1]){
                break;
            }
            cycle.push_back({intersect[0], intersect[1]});
            if (intersect[2] == 1){
                x = -x;
            }
            else if (intersect[2] == 2){
                x = -x; y = -y;
            }
            else{
                y = -y;
            }
        }
        cycle.push_back(cycle.front());
        vector<int> dirt_isec;
        int tot_length = 0;
        for (int i = 1; i < cycle.size(); i++){
            tot_length += (cycle[i][0] - cycle[i-1][0]);
            if (in_middle(cycle[i][0], rd, cycle[i-1][0]) || in_middle(cycle[i][1], cd, cycle[i-1][1])){
                if (in_middle(cycle[i][0], rd, cycle[i-1][0])){
                    dirt_isec.push_back(abs(rd - cycle[i-1][0]));
                }
                else{
                    dirt_isec.push_back(abs(cd - cycle[i-1][1]));
                }
            }
        }
        array<int, 2> prob = {p / __gcd(p, 100LL), 100 / __gcd(p, 100LL)};
        array<int, 2> prob_c = {(100-p) / __gcd((100-p), 100LL), 100 / __gcd((100-p), 100LL)};
        int ans = 0;
        for (int idx : dirt_isec){
            ans = ((ans + compute(idx+1, cycle.size()-1, prob, prob_c)) % M + M) % M;
        }
        cout << ans << "\n";
    }
}
