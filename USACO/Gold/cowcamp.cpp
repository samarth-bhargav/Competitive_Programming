#include <bits/stdc++.h>
using namespace std;

const int mxN = 1000;
int fact[mxN+1];

int main(){
    int t, k;
    cin >> t >> k; t--;
    fact[1] = 1;
    for (int i = 2; i <= t; i++){
        fact[i] = fact[i-1] * i;
    }
    vector<double> leq_x(t+1);
    int curr = 0;
    for (int i = 0; i <= t; i++){
        curr += (fact[t] / (fact[i] * fact[t-i]));
        leq_x[i] = curr / (pow(2, t));
    }
    vector<int> y_values(t+1);
    for (int i = 0; i <= t; i++){
        y_values[i] = int(log(0.5) / log(leq_x[i]));
    }
    vector<double> probabilities(t+1);
    for (int i = 0; i <= t; i++){
        for (int j = t - y_values[i]; j <= t; j++){
            int suboptimal = t;
            int prob = 1;
            for (int l = 0; l <= j; l++){
                if (y_values[suboptimal] == l){
                    suboptimal--;
                }
                prob *= (suboptimal / t);
            }
            probabilities[i] += prob;
        }
    }
    double ans = 0;
    for (int i = 0; i <= t; i++){
        ans += i * probabilities[i];
    }
    cout << ans << "\n";
}
