#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 9e18;

int min(int a, int b){
    return a > b ? b : a;
}
int binpow(int a, int b) {
    if (b == 0)
        return 1;
    int res = binpow(a, b / 2);
    if (b % 2)
        return res * res * a;
    else
        return res * res;
}

bool valid(int x, int y){
    for (int k = 0; k < 40; k++){
        if (((x / binpow(3, k))%3)%2 != (((y / binpow(3, k))%3)%2)){
            return false;
        }
    }
    return true;
}

bool instance = false;
vector<bool> exists;

int solve(int a, int rb){
    if (a == rb){
        return 1;
    }
    if (a > rb){
        return 0;
    }
    vector<pair<int,int>> buffer_len;
    bool chain = false;
    for (int i = 0; i < exists.size(); i++){
        if (exists[(int32_t)i]){
            if (chain){
                buffer_len.back().second++;
            }
            else{
                buffer_len.emplace_back(i, 1);
                chain = true;
            }
        }
        else{
            chain = false;
        }
    }
    vector<int> prod_len; prod_len.push_back(0);
    for (int i = 0; i < buffer_len.size(); i++){
        prod_len.push_back(prod_len.back() + buffer_len[(int32_t)i].second);
    }
    //to see how much it affects from beginning, look at prod_len[i]
    int offset = 0;
    int curr = a;
    for (int i = buffer_len.size()-1; i >= 0; i--){
        //you don't want curr + 3^{buffer_len[i].first} * x to exceed rb
        //curr + 3^{buffer_len[i].first} * x = rb,
        //3^{buffer_len[i].first} * x = rb - curr
        //x = (rb - curr) / 3^{buffer_len[i].first}
        int x = (rb - curr) / binpow(3, buffer_len[(int32_t)i].first);
        x = min(x, binpow(3, buffer_len[(int32_t)i].second) - 1);
        // 3^y = x
        offset += (binpow(3, buffer_len[(int32_t)i].second) - x - 1) * binpow(3, prod_len[(int32_t)i]);
        curr = curr + x * binpow(3, buffer_len[(int32_t)i].first);
    }
    return binpow(3, prod_len.back()) - offset;
}

int solve(int a, int b, int rb){
    if (a < b) swap(a, b);
    int right_bound = a + rb;
    int d = a - b;
    if (d%2 == 1){
        return 0;
    }
    bool one = false;
    queue<int> num;
    int pow = 1;
    for (int i = 0; i < 40; i++, pow *= 3){
        int rem = ((int)(d / pow)) % ((int)3);
        if (rem == 1){
            if (!one){
                num.push(2);
                one = true;
            }
            else{
                num.push(0);
                one = false;
            }
        }
        else{
            if (one){
                if (rem == 2){
                    num.push(0);
                }
                else if (rem == 0){
                    num.push(2);
                }
            }
            else{
                num.push(0);
                one = false;
            }
        }
    }
    int min_valid_x = 0;
    int sz = num.size();
    for (int i = 0; i < sz; i++){
        min_valid_x += (binpow(3, i) * num.front());
        num.pop();
    }
    if (min_valid_x > right_bound){
        return 0;
    }
    int min_valid_y = min_valid_x + d;
    pow = 1;
    while (min_valid_x + pow <= right_bound){
        if (valid(min_valid_x + pow, min_valid_y + pow)){
            exists.push_back(1);
        }
        else{
            exists.push_back(0);
        }
        pow *= 3;
    }
    //so now we have exists
    //it could be something like {0, 1, 0, 0, 0, 0, 1}
    //this means that there exists a pattern of buffer 3 for 3, and it repeats once every 729
    int ret = solve(min_valid_x, right_bound - d) - solve(min_valid_x, b) + valid(min(a,b) + d, b);
    exists.clear();
    return ret;
}

int32_t main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int32_t t;
    cin >> t;
    while (t--){
        int64_t d, a, b;
        cin >> d >> a >> b;
        cout << (int64_t)solve((int)a, (int)b, (int)d) << "\n";
    }
}
