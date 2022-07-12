#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e4+3;
int n, M, dp[mxN+1][1229];


deque<int> gen_prime(){
    bitset<mxN> bits;
    bits.set();
    bits[0] = bits[1] = 0;
    for (int i = 2; i * i <= mxN; i++){
        if (bits[i]){
            for (int j = i*i; j <= mxN; j += i){
                bits[j] = 0;
            }
        }
    }
    deque<int> primes;
    for (int p = bits._Find_first(); p < bits.size(); p = bits._Find_next(p)){
        primes.push_back(p);
    }
    return primes;
}

int main(){
    ifstream cin("exercise.in");
    ofstream cout("exercise.out");
    memset(dp, 0, sizeof(dp));
    cin >> n >> M;
    deque<int> primes = gen_prime();
    vector<vector<int>> prime_powers(primes.size());
    for (int i = 0; i < primes.size(); i++){
        int x = primes[i];
        while (x <= mxN){
            prime_powers[i].push_back(x);
            x = x * primes[i];
        }
    }
    for (int i = 0; i < primes.size(); i++){
        for (int power : prime_powers[i]){
            dp[power][i] = power;
        }
    }
    for (int x = 0; x <= mxN; x++){
        for (int last = 0; last < primes.size(); last++){
            for (int power : prime_powers[last]){
                if (last > 0 && x - power >= 0){
                    dp[x][last] = (dp[x][last] + ((((long long)power * dp[x-power][last-1]) % M + M) % M) % M + M) % M;
                }
            }
        }
        for (int last = 1; last < primes.size(); last++){
            dp[x][last] = ((dp[x][last] + dp[x][last-1]) % M + M) % M;
        }
    }
    int ans = 0;
    for (int x = 0; x <= n; x++){
        ans = ((ans + dp[x][1228]) % M + M) % M;
    }
    cout << ((ans + 1) % M + M) % M << "\n";
}
