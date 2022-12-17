#include <bits/stdc++.h>
using namespace std;

int perfect_power(int x, int d=1){
    if (x == 1){
        return d;
    }
    if (d == 1){
        int div = -1;
        for (int i = 2; i <= sqrt(x)+1; i++){
            if (x%i == 0){
                div = i;
                break;
            }
        }
        if (div == -1){
            return -1;
        }
        return perfect_power(x / div, div);
    }
    return x % d == 0 ? perfect_power(x / d, d) : -1;
}

int main(){
    int r, c;
    cin >> r >> c;
    int ans = 1;
    for (int row = 2; row <= r; row++){
        int pp = perfect_power(row);
        if (pp == -1){
            pp = row;
        }
        if (pp == row){
            ans += c;
        }
        else{
            // log_pp(row) = x
            int pw = log(row) / log(pp);
            //pp^(pw)^(col) = pp^(pw * col)
            //finding how many of pw * col is alr existing
            //if pw * col has a factor less than iter basically
            //iterate from p = 1 to p = pw-1, and see what's min k s.t. pw | p * k
            //put all these k's into a set and do some PIE sht
            vector<int> PIE;
            for (int p = 1; p < pw; p++){
                //find min k
                int k = ((p * pw) / __gcd(p, pw)) / p;
                PIE.push_back(k);
            }
            for (int mask = 1; mask < (1 << PIE.size()); mask++){
                //combine all into big
                int lcm = 1;
                int min_bit = -1;
                for (int bit = 0; bit < PIE.size(); bit++){
                    if ((mask >> bit) & 1){
                        if (min_bit == -1){
                            min_bit = bit;
                        }
                        lcm = (lcm * PIE[bit]) / __gcd(lcm, PIE[bit]);
                    }
                }
                ans += c - (PIE.size()%2 == 1 ? 1 : -1) * (c / (lcm / PIE[min_bit]));
            }
        }
    }
    cout << ans << "\n";
}
