#include <bits/stdc++.h>

using namespace std;

#define ll int64_t
ll N, K, L;
multiset<int>V;

bool ok(int H){
    multiset<int>cpy = V;
    int init = 0;
    for (auto it = cpy.begin(); it != cpy.end(); it++){
        if (*it < H){
            init++;
        }
        else{
            break;
        }
    }
    init = N-init;
    ll citused = 0;
    while (true){
        auto it = cpy.lower_bound(H);
        if (it == cpy.end()){
            //all values higher
            if (*cpy.begin() > H){
                if (cpy.size() >= H){
                    return true;
                }
                else{
                    return false;
                }
            }
            else{
                it = prev(cpy.end());
            }
        }
        else{
            if (*it >= H){
                if (it == cpy.begin()){
                    if (cpy.size() >= H){
                        return true;
                    }
                    else{
                        return false;
                    }
                }
                else{
                    it--;
                }
            }
        }
        citused += min((ll)(H-*it),K);
        if (citused > K*L){
            if (init >= H){
                return true;
            }
            return false;
        }
        int val = *it;
        cpy.erase(it);
        cpy.insert(val + min((ll)(H-val),K));
        if (val + min(ll(H-val),K) >= H){
            init++;
        }
        else{
            if (init >= H){
                return true;
            }
            return false;
        }
    }
}

void solve(){
    cin >> N >> K >> L;
    for (int i = 0; i < N; i++){
        int X;
        cin >> X;
        V.insert(X);
    }
    ok(3);
    int lo = *V.begin();
    int hi = *prev(V.end())+K;
    while (hi - lo > 1){
        int mid = (lo+hi)/2;
        if (ok(mid)){
            lo = mid;
        }
        else{
            hi = mid-1;
        }
    }
    cout << (ok(hi)?hi:lo) << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    solve();
}

