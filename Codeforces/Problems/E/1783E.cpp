#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t; cin >> t;
    for (int p = 0; p < t; p++){
        int n; cin >> n;
        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        for (int i = 0; i < n; i++){
            cin >> b[i];
        }
        vector<array<int, 2>> curr_ranges;
        for (int i = 0; i < n; i++){
            vector<int> ceil_a, ceil_b;
            ceil_a.reserve(2 * sqrt(n+1) + 5);
            ceil_b.reserve(2 * sqrt(n+1) + 5);
            int lst = -1;

            ceil_a.push_back(1);
            ceil_b.push_back(1);
            for (int j = 1; (a[i] + j - 1) >= j * j; j++){
                lst = j;
                if (j != 1){
                    ceil_a.push_back(j);
                }
            }
            for (int j = lst; j >= 1; j--){
                ceil_a.push_back((a[i] + j - 1) / j);
                if (ceil_a.size() >= 2 && ceil_a.back() == ceil_a[ceil_a.size()-2]){
                    ceil_a.pop_back();
                }
            }

            if (a[i] != 1 && ceil_a.back() != a[i]){
                ceil_a.push_back(a[i]);
            }
            for (int j = 1; (b[i] + j - 1) >= j * j; j++){
                lst = j;
                if (j != 1){
                    ceil_b.push_back(j);
                }
            }
            for (int j = lst; j >= 1; j--){
                ceil_b.push_back((b[i] + j - 1) / j);
                if (ceil_b.size() >= 2 && ceil_b.back() == ceil_b[ceil_b.size()-2]){
                    ceil_b.pop_back();
                }
            }
            if (b[i] != 1 && ceil_b.back() != b[i]){
                ceil_b.push_back(b[i]);
            }
            for (int j = 0; j < ceil_a.size(); j++){
                if (ceil_a[j] > n){
                    ceil_a = vector<int> (ceil_a.begin(), ceil_a.begin() + j);
                    break;
                }
            }
            for (int j = 0; j < ceil_b.size(); j++){
                if (ceil_b[j] > n){
                    ceil_b = vector<int> (ceil_b.begin(), ceil_b.begin() + j);
                    break;
                }
            }
            int a_sz = ceil_a.size()-1;
            int b_sz = ceil_b.size()-1;
            ceil_a.push_back(ceil_a.back());
            ceil_b.push_back(ceil_b.back());
            //keep two pointers to keep track of when each changes
            int ptr_a = 0, ptr_b = 0;
            int start_range = ((a[i] + ceil_a[ptr_a] - 1) / ceil_a[ptr_a] <=
                               (b[i] + ceil_b[ptr_b] - 1) / ceil_a[ptr_b] ? ptr_a : -1);
            vector<array<int, 2>> ranges;
            ranges.reserve(2 * sqrt(n) + 5);
            while (ptr_a <= a_sz && ptr_b <= b_sz){
                if (ptr_a == a_sz && ptr_b == b_sz){
                    break;
                }
                if ((ptr_a != a_sz) && (ptr_b == b_sz || ceil_a[ptr_a+1] < ceil_b[ptr_b+1])){
                    //advance ptr_a
                    ptr_a++;
                    if (start_range == -1){
                        if ((a[i] + ceil_a[ptr_a] - 1) / ceil_a[ptr_a] <=
                            (b[i] + ceil_a[ptr_a] - 1) / ceil_a[ptr_a]){
                            start_range = ptr_a;
                        }
                    }
                }
                else if (ptr_a != a_sz && ptr_b != b_sz && ceil_a[ptr_a+1] == ceil_b[ptr_b+1]){
                    ptr_a++; ptr_b++;
                    if (start_range == -1){
                        if ((a[i] + ceil_a[ptr_a] - 1) / ceil_a[ptr_a] <=
                            (b[i] + ceil_a[ptr_a] - 1) / ceil_a[ptr_a]){
                            start_range = ptr_a;
                        }
                    }
                    else{
                        if ((a[i] + ceil_b[ptr_b] - 1) / ceil_b[ptr_b] >
                            (b[i] + ceil_b[ptr_b] - 1) / ceil_b[ptr_b]){
                            ranges.push_back({ceil_a[start_range], ceil_b[ptr_b]-1});
                            start_range = -1;
                        }
                    }
                }
                else{
                    ptr_b++;
                    if (start_range != -1){
                        if ((a[i] + ceil_b[ptr_b] - 1) / ceil_b[ptr_b] >
                            (b[i] + ceil_b[ptr_b] - 1) / ceil_b[ptr_b]){
                            ranges.push_back({ceil_a[start_range], ceil_b[ptr_b]-1});
                            start_range = -1;
                        }
                    }
                }
            }
            if (start_range != -1){
                if ((a[i] + ceil_a[ptr_a] - 1) / ceil_a[ptr_a] <=
                    (b[i] + ceil_b[ptr_b] - 1) / ceil_b[ptr_b]){
                    ranges.push_back({ceil_a[start_range], n});
                }
            }

            //we have a bunch of ranges of k values that work
            if (i == 0){
                curr_ranges = ranges;
            }
            else{
                //we want to merge ranges
                int ptr_curr = 0;
                vector<array<int, 2>> new_ranges;
                new_ranges.reserve(2 * sqrt(n) + 5);
                for (array<int, 2> rng : ranges){
                    while (ptr_curr < curr_ranges.size() && curr_ranges[ptr_curr][1] < rng[0]){
                        ptr_curr++;
                    }
                    while (ptr_curr < curr_ranges.size() && curr_ranges[ptr_curr][0] <= rng[1]){
                        new_ranges.push_back({max(rng[0], curr_ranges[ptr_curr][0]), min(rng[1], curr_ranges[ptr_curr][1])});
                        ptr_curr++;
                    }
                    if (ptr_curr > 0){
                        ptr_curr--;
                    }
                }
                swap(curr_ranges, new_ranges);
            }
        }
        int num_elems = 0;
        for (array<int, 2> rng : curr_ranges){
            num_elems += (rng[1] - rng[0] + 1);
        }
        cout << num_elems << "\n";
        for (array<int, 2> rng : curr_ranges){
            for (int i = rng[0]; i <= rng[1]; i++){
                cout << i << " ";
            }
        }
        cout << "\n";
    }
}
