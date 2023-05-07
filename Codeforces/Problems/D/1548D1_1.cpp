#include <bits/stdc++.h>
using namespace std;

const int mxN = 6e3+1;
typedef long long ll;

vector<array<int, 2>> mod_poss = {{0, 0}, {0, 2}, {2, 0}, {2, 2}};
vector<int> sz_mod(4, 0);
ll nCr[mxN][4];

int bndry(array<int, 2> a, array<int, 2> b){
    ll slpx = b[1] - a[1], slpy = b[0] - a[0];
    if (slpx == 0) return abs(slpy);
    else if (slpy == 0) return abs(slpx);
    ll gcd = __gcd(abs(slpx), abs(slpy));
    slpx /= gcd; slpy /= gcd;
    return min(abs((b[0] - a[0]) / slpy), abs((b[1] - a[1]) / slpx));
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    vector<array<int, 2>> pts(n);
    for (int i = 0; i < n; i++){
        cin >> pts[i][0] >> pts[i][1];
    }
    for (int i = 0; i < n; i++){
        if (pts[i][0] % 4 == 0){
            if (pts[i][1] % 4 == 0){
                sz_mod[0]++;
            }
            else{
                sz_mod[1]++;
            }
        }
        else{
            if (pts[i][1] % 4 == 0){
                sz_mod[2]++;
            }
            else{
                sz_mod[3]++;
            }
        }
    }
    memset(nCr, 0, sizeof(nCr));
    for (ll k = 0; k < 4; k++){
        for (ll r = k; r <= n; r++){
            if (k == 0) nCr[r][k] = 1;
            else if (k == 1) nCr[r][k] = r;
            else if (k == 2) nCr[r][k] = (r * (r-1)) / 2;
            else nCr[r][k] = (r * (r-1) * (r-2)) / 6;
        }
    }
    ll ans = 0;
    set<array<int, 3>> seen;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            for (int k = 0; k < 4; k++){
                array<int, 3> rep = {i, j, k};
                sort(rep.begin(), rep.end());
                if (seen.find(rep) != seen.end()){
                    continue;
                }
                seen.insert(rep);
                int num_4 = 0;
                if ((mod_poss[i][0] - mod_poss[j][0]) % 4 == 0 && (mod_poss[i][1] - mod_poss[j][1]) % 4 == 0){
                    num_4++;
                }
                if ((mod_poss[i][0] - mod_poss[k][0]) % 4 == 0 && (mod_poss[i][1] - mod_poss[k][1]) % 4 == 0){
                    num_4++;
                }
                if ((mod_poss[j][0] - mod_poss[k][0]) % 4 == 0 && (mod_poss[j][1] - mod_poss[k][1]) % 4 == 0){
                    num_4++;
                }
                if (num_4 == 1 || num_4 == 3){
                    array<int, 4> freqs = {0, 0, 0, 0};
                    freqs[i]++; freqs[j]++; freqs[k]++;
                    ll temp = 1;
                    for (int l = 0; l < 4; l++){
                        temp *= nCr[sz_mod[l]][freqs[l]];
                    }
                    ans += temp;
                }
            }
        }
    }
    cout << ans << "\n";

//    for (int i = 0; i < n; i++){
//        for (int j = i+1; j < n; j++){
//            for (int k = j+1; k < n; k++){
//                cout << "Triangle: " << i << " " << j << " " << k << " Boundaries: " << bnd[i][j] << " " << bnd[j][k] << " " << bnd[i][k] << "\n";
//            }
//        }
//    }

}
