#include <bits/stdc++.h>
using namespace std;

int n,m;
vector<pair<long long, long long>>pii;

bool ok(long long d){
    int currinterval = 0;
    long long pos = pii[0].first;
    for (int i = 1; i < n; i++){
        if (pos+d <= pii[currinterval].second){
            pos += d;
            continue;
        }
        else{
            auto it = upper_bound(pii.begin(),pii.end(),make_pair(pos+d,0LL));
            if (it == pii.end()){
                if (prev(it)->first <= pos+d && prev(it)->second >= pos+d){
                    pos += d;
                    currinterval = m-1;
                }
                else{
                    return false;
                }
            }
            else{
                if (it->first == pos+d){
                    currinterval = it-pii.begin();
                    pos += d;
                    continue;
                }
                it--;
                if (it->first <= pos+d && pos+d <= it->second){
                    pos += d;
                    currinterval = it-pii.begin();
                    continue;
                }
                else{
                    it++;
                    pos = it->first;
                    currinterval = it-pii.begin();
                    continue;
                }
            }
        }
    }
    return true;
}

int main(){
    freopen("socdist.in","r",stdin);
    freopen("socdist.out","w",stdout);
    cin >> n >> m;
    for (int i = 0; i < m; i++){
        long long a,b;
        cin >> a >> b;
        pii.emplace_back(a,b);
    }
    sort(pii.begin(),pii.end());
    long long lo = 1;
    long long hi = 1e18;
    while (hi-lo > 1){
        long long mid = (hi+lo)/2;
        if (ok(mid)){
            lo = mid;
        }
        else{
            hi = mid-1;
        }
    }
    cout << (ok(hi)?hi:lo) << "\n";
}