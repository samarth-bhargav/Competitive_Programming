//babybeluga
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++){
        double a,b;
        cin >> a >> b;
        cout << fixed;
        cout << setprecision(2) << (b-a)/a * 100.0 << "\n";
    }
}

