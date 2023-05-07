#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int x; cin >> x;
        int off_bits = 0;
        for (int b = 0; b <= 30; b++){
            if (!((x >> b) & 1)){
                off_bits += (1 << (b+1));
            }
        }
        //check if x is a subset of off_bits
        if ((x & off_bits) != x){
            cout << -1 << "\n";
            continue;
        }
        int both = (x & off_bits);
        both >>= 1;
        int a = 0, b = 0;
        int cnt = 0;
        for (int l = 0; l <= 30; l++){
            if ((both >> l) & 1){
                a += (1 << l);
                b += (1 << l);
            }
            else{
                if ((x >> l) & 1){
                    cnt++;
                }
            }
        }
        if ((cnt == 0 || cnt == 1) && a == 0 && b == 0){
            cout << -1 << "\n";
            continue;
        }
        bool a_done = false;
        for (int l = 0; l <= 30; l++){
            if ((x >> l) & 1){
                if (!a_done){
                    a += (1 << l);
                    a_done = true;
                }
                else{
                    b += (1 << l);
                }
            }
        }
        cout << a << " " << b << "\n";
    }
}

