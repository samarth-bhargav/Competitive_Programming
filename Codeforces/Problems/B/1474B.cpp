/*
Dont raise your voice,improve your argument
--Desmond Tutu
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/
vector<int>primes = {2,3};

void gen(){
    for (int i = 5; i <= 10100; i+=2){
        bool alg = true;
        for (int j = 2; j <= sqrt(i); j++){
            if (i%j == 0){
                alg = false;
                break;
            }
        }
        if (alg){
            primes.push_back(i);
        }
    }
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    gen();
    int t;
    cin >> t;
    while (t--){
        int n;
        cin >> n;
        auto it = lower_bound(primes.begin(),primes.end(),n+1);
        cout << *it * *(next(it)) << "\n";
    }
}

