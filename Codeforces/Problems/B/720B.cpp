//babybeluga
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/
bool isprime(int n){
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;
    for (int i = 5; i * i <= n; i = i + 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    return true;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int primes[100005];
    int pos = 0;
    for (int i = 2; i <= 2000000000 && pos < 100005; i++){
        if (isprime(i)){
            primes[pos] = i;
            pos++;
        }
    }
    int t;
    cin >> t;
    while (t--){
        int n; cin >> n;
        vector<pair<int,int>>a(n);
        for (int i = 0; i < n; i++){
            int x; cin >> x;
            a[i].first = x; a[i].second = i;
        }
        sort(a.begin(),a.end());
        vector<int>answer(n);
        for (int i = 0; i < n; i++){
            answer[a[i].second] = primes[i];
        }
        cout << n-1 << "\n";
        for (int i = 0; i < n-1; i++){
            cout << i+1 << " " << i+2 << " " << answer[i] << " " << answer[i+1] << "\n";
        }
    }
}

