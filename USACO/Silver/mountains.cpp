/*
ID: samarth10
LANG: C++11
TASK: 
*/
#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;

struct mountain{
    int negative;
    int positive;
};

int a[mxN], b[mxN], ans = 0;
mountain ar[mxN];

bool compare (mountain x, mountain y){
    if (x.negative == y.negative){
        return x.positive > y.positive;
    }
    return x.negative < y.negative;
}

int main() {
    freopen("mountains.in", "r", stdin);
    freopen("mountains.out", "w", stdout);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++){
        cin >> a[i] >> b[i];
        ar[i].positive = a[i]+b[i];
        ar[i].negative = a[i]-b[i];
    }
    sort(ar, ar+n, compare);
    int mxM = ar[0].positive;
    for (int i = 1; i < n; i++){
        if (ar[i].positive <= mxM){
            ans++;
        }
        mxM = max(mxM, ar[i].positive);
    }
    cout << n-ans << "\n";
}


