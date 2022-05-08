/*
ID: samarth10
LANG: C++11
TASK: 
*/
#include <bits/stdc++.h>
using namespace std;
#define INF 2000000000
/*
void setIO(string name) {
	ios_base::sync_with_stdio(0); cin.tie(0);
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);
}
*/
long long a,b;
vector <long long> num;
bool ok(long long u){
    long long ans = 0;
    for (long long i = (a)/2; i < a; i++){
        if (u - num[i] > 0){
            ans += u - num[i];
        }
    }
    return ans <= b;
}
int main() {
    //setIO();
    cin >> a >> b;
    for (int i = 0; i < a; i++){
        long long c;
        cin >> c;
        num.push_back(c);
    }
    sort(num.begin(), num.end());
    long long lo = 1;
    long long hi = INF;
    long long mid;
    while (lo != hi){
        mid = (lo + hi + 1)/2;
        if (ok(mid)) {
            lo = mid;
        }
        else{
            hi = mid-1;
        }
    }
    cout << hi << "\n";
}

