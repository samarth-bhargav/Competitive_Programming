#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 100;
int g[N][N];


long long binpow(long long a, long long b) {
    if (b == 0)
        return 1;
    long long res = binpow(a, b / 2);
    if (b % 2)
        return res * res * a;
    else
        return res * res;
}

bool valid(int x, int y){
    for (int k = 0; k <= 40; k++){
        if (((x / binpow(3, k))%3)%2 != (((y / binpow(3, k))%3)%2)){
            return false;
        }
    }
    return true;
}

int32_t main(){
    int t;
    cin >> t;
    while (t--){
        int d, x, y;
        cin >> d >> x >> y;
        if (x < y){
            swap(x,y);
        }
        int cnt = 0;
        int xcpy = x;
        for (; x <= xcpy+d; x++, y++){
            if (valid(x,y)){
                cnt++;
            }
        }
        cout << cnt << "\n";
    }

//    int buff = 0;
//    for (int i = 0; i < N; i++){
//        for (int j = 0; j < N; j++){
//            cout << (g[i][j] ? "1" : " ");
//        }
//        cout << "\n";
//    }
}
