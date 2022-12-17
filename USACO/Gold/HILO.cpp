#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;
map<int, int> loc;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
        loc[a[i]] = i;
    }
    loc[0] = -1; loc[-1] = -1;
    vector<int> least_greater(n), greatest_less(n);
    least_greater[0] = -1; greatest_less[0] = -1;
    set<int> curr; curr.insert(a[0]);
    for (int i = 1; i < n; i++){
        auto it = curr.lower_bound(a[i]);
        if (it == curr.end()){
            // everything is less
            greatest_less[i] = *prev(it);
            least_greater[i] = -1;
        }
        else if (it == curr.begin()){
            //everything is greater
            greatest_less[i] = -1;
            least_greater[i] = *it;
        }
        else{
            greatest_less[i] = *prev(it);
            least_greater[i] = *it;
        }
        curr.insert(a[i]);
    }
    int curr_ans = 0;
    cout << curr_ans << "\n";
    for (int i = 1; i <= n; i++){
        int location = loc[i];
        int one, two;
        if (location == 0){
            one = 0;
        }
        else{
            one = (loc[least_greater[location]] > loc[greatest_less[location]] ? 1 : 0);
        }
        two = (loc[i-1] > location ? -1 : 0);
        cout << one + two + curr_ans << "\n";
        curr_ans += (one + two);
    }
}