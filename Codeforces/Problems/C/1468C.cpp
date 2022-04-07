/*
Dont raise your voice,improve your argument
--Desmond Tutu
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

/*
 * Sets off as many crackers in first cell
 * Then tries to run away as far as possible (to see most fireworks)
 * He should set off the crackers from greatest to least
 * The largest cracker you can set off is distance from guard to you...
 * Plus the distance from you to an end
*/
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--){
        int n,m,a,b;
        cin >> n >> m >> a >> b;
        vector<int>ar(m);
        for (auto & i : ar){
            cin >> i;
        }
        sort(ar.begin(),ar.end());
        if (a > b){ //you are to the right
            int maxsecond = abs(a-b)+n-a-1;
            int firelim = abs(a-b)-1;
            //find the largest firework you can set off
            if (lower_bound(ar.begin(),ar.end(),maxsecond) == ar.begin()){
                if (*ar.begin() == maxsecond){
                    cout << min(firelim,1) << "\n";
                }
                else{
                    cout << 0 << "\n";
                }
                continue;
            }
            vector<int>::iterator it1;
            if (binary_search(ar.begin(),ar.end(),maxsecond)){
                it1 = lower_bound(ar.begin(),ar.end(),maxsecond);
            }
            else{
                it1 = prev(lower_bound(ar.begin(),ar.end(),maxsecond));
            }
            cout << min((int)(it1-ar.begin()+1),firelim) << "\n";
        }
        else{
            int maxsecond = abs(a-b)+a-2;
            int firelim = abs(a-b)-1;
            vector<int>::iterator it1;
            if (lower_bound(ar.begin(),ar.end(),maxsecond) == ar.begin()){
                if (*ar.begin() == maxsecond){
                    cout << min(firelim,1) << "\n";
                }
                else{
                    cout << 0 << "\n";
                }
                continue;
            }
            if (binary_search(ar.begin(),ar.end(),maxsecond)){
                it1 = lower_bound(ar.begin(),ar.end(),maxsecond);
            }
            else{
                it1 = prev(lower_bound(ar.begin(),ar.end(),maxsecond));
            }
            cout << min((int)(it1-ar.begin()+1),firelim) << "\n";
        }
    }
}

