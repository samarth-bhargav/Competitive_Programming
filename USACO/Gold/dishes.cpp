#include <bits/stdc++.h>
using namespace std;

int main(){
    ifstream cin("dishes.in");
    ofstream cout("dishes.out");
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    deque<vector<int>> stacks;
    stacks.push_back({a[0]});
    deque<int> sb = {a[0]};
    int greatest_popped = -1;
    bool flag = false;
    for (int d = 1; d < n; d++){
        int element = a[d];
        if (element < greatest_popped){
            cout << d << "\n";
            flag = true;
            break;
        }
        auto stack_pos = lower_bound(sb.begin(), sb.end(), element);
        if (stack_pos == sb.end()){
            sb.push_back(element);
            stacks.push_back({element});
            continue;
        }
        else{
            int stack_index = stack_pos - sb.begin();
            if (stacks[stack_index].back() < element){
                for (int i = 0; i < stack_index; i++){
                    stacks.pop_front();
                    sb.pop_front();
                }
                while (stacks[0].back() < element){
                    greatest_popped = max(greatest_popped, stacks[0].back());
                    stacks[0].pop_back();
                }
            }
            else{
                stacks[stack_index].push_back(element);
            }
        }
    }
    if (!flag){
        cout << n << "\n";
    }
}
