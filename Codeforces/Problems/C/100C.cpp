#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;
    while (t--){
        int n;
        cin >> n;
        vector<pair<int,int>>cmnds;
        for (int i = 0; i < n; i++){
            int a,b;
            cin >> a >> b;
             cmnds.emplace_back(a,b);
        }
        assert(is_sorted(cmnds.begin(),cmnds.end()));
        int pos = 0;
        int lastpos = 0;
        int ans = 0;
        pair<int,int>curr;
        while (pos < n){
            curr = cmnds[pos];
            if (pos == n-1){
                ans++;
                break;
            }
            pos++;
            //look at all ignored
            bool alg = false;
            while (pos < n && curr.first+abs(lastpos-curr.second) > cmnds[pos].first){
                alg = true;
                if (curr.second > lastpos){
                    //going forward
                    //now check if you can add to ans
                    if (pos == n-1){
                        int tmereached = curr.first+(cmnds[pos].second-lastpos);
                        ans += ((tmereached >= cmnds[pos].first)&&(lastpos <= cmnds[pos].second && cmnds[pos].second <= curr.second));
                    }
                    else{
                        int tmereached = curr.first+(cmnds[pos].second-lastpos);
                        ans += ((tmereached >= cmnds[pos].first)&&(tmereached <= cmnds[pos+1].first));
                    }
                }
                else{
                    if (pos == n-1){
                        int tmereached = curr.first+((lastpos - cmnds[pos].second));
                        ans += ((tmereached >= cmnds[pos].first)&&(lastpos >= cmnds[pos].second && cmnds[pos].second >= curr.second));
                    }
                    else{
                        int tmereached = curr.first+((lastpos - cmnds[pos].second));
                        ans += ((tmereached >= cmnds[pos].first)&&(tmereached <= cmnds[pos+1].first));
                    }
                }
                pos++;
            }
            if (!alg){
                ans++;
            }
            lastpos = curr.second;
        }
        cout << ans << "\n";
    }
}