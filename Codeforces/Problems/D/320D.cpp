#include <bits/stdc++.h>
using namespace std;

int main(){

    int n;
    cin >> n;
    int val[n], tdeath[n];
    for (int i = 0; i < n; i++){
        cin >> val[i]; val[i];
    }
    stack<int> st; st.push(0);
    int ans = -1;
    tdeath[0] = -1;
    for (int i = 1; i < n; i++){
        tdeath[i] = 0;
        while (!st.empty() && val[st.top()] < val[i]){
            tdeath[i] = max(tdeath[i], tdeath[st.top()] + 1);
            st.pop();
        }
        if (st.empty()){
            tdeath[i] = -1;
        }
        st.push(i);
        ans = max(ans, tdeath[i] + 1);
    }
    for (int i = 0; i < n; i++){
        cerr << tdeath[i] << " ";
    }
    cout << ans << "\n";
}