#include <iostream>
#include <assert.h>
#include <vector>

int main(){
    int t;
    std::cin >> t;
    while (t--){
        int n;
        std::cin >> n;
        assert(n>=3);
        //special cases
        if (n == 3){
            std::cout << 2 << "\n";
            std::cout << "3 2\n3 2\n";
            continue;
        }
        if (n == 4){
            std::cout << 3 << "\n";
            std::cout << "3 4\n4 2\n4 2\n";
            continue;
        }
        if (n == 5){
            std::cout << 5 << "\n";
            std::cout << "2 5\n3 5\n5 4\n4 5\n4 5\n";
            continue;
        }
        if (n == 6){
            std::cout << "6\n";
            std::cout << "4 6\n5 6\n6 3\n6 3\n3 2\n3 2\n";
            continue;
        }
        if (n == 7){
            std::cout << "7\n";
            std::cout << "4 7\n5 7\n6 7\n7 3\n7 3\n3 2\n3 2\n";
            continue;
        }
        if (n == 8){
            std::cout << "8\n";
            std::cout << "4 8\n5 8\n6 8\n7 8\n8 3\n8 3\n3 2\n3 2\n";
            continue;
        }
        std::vector<std::pair<int,int>>ans;
        for (int i = 3; i <= n-1; i++){
            if (i == 8){
                continue;
            }
            ans.emplace_back(i,n);
        }
        int k = n;
        while (k != 1){
            k = ((k+7)/8);
            ans.emplace_back(n,8);
        }
        ans.emplace_back(8,2);
        ans.emplace_back(8,2);
        ans.emplace_back(8,2);
        std::cout << ans.size() << "\n";
        for (auto & i : ans){
            std::cout << i.first << " " << i.second << "\n";
        }
    }
}
