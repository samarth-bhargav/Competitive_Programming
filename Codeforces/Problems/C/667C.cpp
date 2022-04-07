/*
ID: samarth10
LANG: C++11
TASK: 
*/
#include <bits/stdc++.h>

using namespace std;

vector <int> factors(int n){
    vector <int> vi;
    for(int i = 1; i <= sqrt(n); ++i){
        if(n % i == 0){
            vi.push_back(i);
            if(i != sqrt(n)){
                vi.push_back(n/i);
            }
        }
    }
    sort(vi.begin(), vi.end());
    return vi;
}
int main() {
    //setIO();
    int t;
    cin >> t;
    while (t--){
        int n,a,b;
        cin >> n >> a >> b;
        vector <int> vi = factors(abs(a-b));
        vector <pair <int,int>> ans;
        //step 1: see if it is possible to insert any more elements by looking at factors (insert in between / on left)
        for (int i : vi){
            int ncpy = n;
            if ((b-a)/i + 1 <= ncpy){ // if you can insert elements in between
                ncpy -= (b-a)/i + 1;
            }
            else{
                continue;
            }
            int minel = a;
            while (minel > 0 && ncpy >= 0){
                minel -= i;
                ncpy -= 1;
            }
            if (minel <= 0){
                minel += i;
                ncpy++;
            }
            if (ncpy < 0){
                minel += i;
                ans.emplace_back(minel,i);
                continue;
            }
            if (ncpy == 0){
                ans.emplace_back(minel, i);
                continue;
            }
            ans.emplace_back(minel,i);
        }
        pair <int,int> maxel = make_pair(1e9,-1);
        for (auto & i : ans){
            if (i.first + (n-1)*i.second < maxel.first){
                maxel = make_pair(i.first, i.second);
            }
        }
        for (int i = 0; i < n; i++){
            cout << maxel.first + maxel.second * i << " ";
        }
        cout << "\n";
    }
}

