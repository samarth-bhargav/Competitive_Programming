/*
ID: samarth10
LANG: C++11
TASK: 
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--){
        int acap, bcap;
        cin >> acap >> bcap;
        int numswords, numax;
        cin >> numswords >> numax;
        int weightsword, weightax;
        cin >> weightsword >> weightax;
        int ans = 0;
        int acapcpy = acap, bcapcpy = bcap, numswordscpy = numswords, numaxcpy = numax;
        for (int i = 0; i <= numswords && weightsword * i <= acap; i++){
            int axes = (acap - weightsword*i)/weightax;
            int bans = 0, aans = 0;
            numswords -= i;
            numax -= axes;
            aans = i + axes;
            if (weightax < weightsword){
                if (numax * weightax > bcap){
                    bans += bcap / weightax;
                }
                else{
                    bans += min(bcap / weightax, numax);
                    bcap -= weightax * bans;
                    bans += min(bcap / weightsword, numswords);
                }
            }
            else{
                if (numswords * weightsword > bcap){
                    bans += bcap / weightsword;
                }
                else{
                    bans += min(bcap / weightsword, numswords);
                    bcap -= bans * weightsword;
                    bans += min(bcap / weightax, numax);
                }
            }
            ans = max(ans, aans+bans);
            acap = acapcpy; bcap = bcapcpy; numswords = numswordscpy; numax = numaxcpy;
        }
        cout << ans << "\n";
    }
}

