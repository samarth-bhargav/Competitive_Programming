#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

#define int long long
#define oset tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>

int count_inv(vector<int> a){
    int ret = 0, b = 0;
    int n = a.size();
    for (int i = 0; i < n; i++){
        if (a[i]){
            b++;
        }
        else{
            ret += b;
        }
    }
    return ret;
}

int32_t main(){
    ifstream cin("balance.in");
    ofstream cout("balance.out");
    int n;
    cin >> n;
    vector<int> a(2*n);
    oset ones;
    oset zeroes;
    for (int i = 0; i < 2*n; i++){
        cin >> a[i];
        if (a[i]){
            ones.insert(i);
        }
        else{
            zeroes.insert(i);
        }
    }
    int left_inv = count_inv(vector<int>(a.begin(), a.begin()+n));
    int right_inv = count_inv(vector<int>(a.begin()+n, a.end()));

    vector<int> acpy = a;
    oset onescpy = ones;
    oset zeroescpy = zeroes;
    int left_inv_cpy = left_inv;
    int right_inv_cpy = right_inv;

    cerr << "left inversions: " << left_inv << "\n";
    cerr << "right inversions: " << right_inv << "\n";

    //test transferring from left to right

    int ans = abs(right_inv - left_inv);
    auto mid_point = ones.lower_bound(n-1);
    int ones_on_left = ones.order_of_key(*mid_point);
    int ones_on_right = ones.size() - ones_on_left;

    cerr << "ones on left: " << ones_on_left << "\n";
    cerr << "ones on right: " << ones_on_right << "\n";

    int moves_so_far = 0;

    int ones_to_move = min(ones_on_left, n - ones_on_right);
    for (int t = 1; t <= ones_to_move; t++){
        //we transfer 't' ones from the left to the right
        //bring one to the middle

        auto left_closest_one = prev(ones.upper_bound(n-1));
//        int one_index = ones.order_of_key(*left_closest_one);
        a[*left_closest_one] = 0;
        a[n-1] = 1;
        moves_so_far += (n-1) - (*left_closest_one);
        left_inv -= ((n-1) - (*left_closest_one));
        ones.erase(left_closest_one);
        ones.insert(n-1);
        //there's still a zero at n-1 according to the zeroes set

        zeroes.insert(*left_closest_one);
        zeroes.erase(n-1);

        auto right_closest_zero = (zeroes.lower_bound(n));
//        int zero_index = zeroes.order_of_key(*right_closest_zero);
        a[*right_closest_zero] = 1;
        a[n] = 0;
        moves_so_far += (*right_closest_zero) - n;
        right_inv -= (*right_closest_zero) - n;
        zeroes.erase(right_closest_zero);
        zeroes.insert(n);
        //there's still a one at n according to the ones set

        ones.insert(*right_closest_zero);
        ones.erase(n);

        //perform the central swap
        //1 goes to the right, 0 goes to the left
        ones_on_left--;
        ones_on_right++;
        left_inv += (ones_on_left);
        right_inv += (n - ones_on_right);
        a[n-1] = 0;
        a[n] = 1;
        ones.erase(n-1);
        ones.insert(n);
        zeroes.erase(n);
        zeroes.insert(n-1);
        moves_so_far++;

        ans = min(ans, (moves_so_far) + abs(right_inv - left_inv));
    }

    a = acpy;
    ones = onescpy;
    zeroes = zeroescpy;
    left_inv = left_inv_cpy;
    right_inv = right_inv_cpy;
    moves_so_far = 0;

    ones_to_move = min(ones_on_right, n - ones_on_left);
    for (int t = 1; t <= ones_to_move; t++){
        //we transfer 't' ones from the right to the left
        //bring zero to the middle

        auto left_closest_zero = prev(zeroes.upper_bound(n-1));
//        int zero_index = zeroes.order_of_key(*left_closest_zero);
        a[*left_closest_zero] = 1;
        a[n-1] = 0;
        moves_so_far += (n-1) - (*left_closest_zero);
        left_inv += ((n-1) - (*left_closest_zero));
        zeroes.erase(left_closest_zero);
        zeroes.insert(n-1);
        //there's still a one at n-1 according to the zeroes set

        ones.insert(*left_closest_zero);
        ones.erase(n-1);

        auto right_closest_one = (ones.lower_bound(n));
//        int one_index = zeroes.order_of_key(*right_closest_one);
        a[*right_closest_one] = 0;
        a[n] = 1;
        moves_so_far += (*right_closest_one) - n;
        right_inv += (*right_closest_one) - n;
        ones.erase(right_closest_one);
        ones.insert(n);
        //there's still a zero at n according to the ones set

        zeroes.insert(*right_closest_one);
        zeroes.erase(n);

        //perform the central swap
        //1 goes to the right, 0 goes to the left

//        int zeroes_on_left = n - (ones_on_left);
//        int zeroes_on_right = n - (ones_on_right);
        left_inv -= (ones_on_left);
        right_inv -= (n - ones_on_right);
        ones_on_left++;
        ones_on_right--;
        a[n-1] = 1;
        a[n] = 0;
        zeroes.erase(n-1);
        zeroes.insert(n);
        ones.erase(n);
        ones.insert(n-1);
        moves_so_far++;

        ans = min(ans, (moves_so_far) + abs(right_inv - left_inv));
    }

    cout << ans << "\n";
}
