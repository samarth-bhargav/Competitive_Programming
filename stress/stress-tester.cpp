#include <bits/stdc++.h>
using namespace std;

#define int long long

int rnd(int l, int r) {
    return l + rand() % (r - l + 1);
}

string rnd_str(int len){
    string ret = "";
    for (int i = 0; i < len; i++){
        ret += char(rnd(97, 97+1));
    }
    return ret;
}

bool equal(string file1, string file2) {
    auto read_file = [&](string f) {
        vector<string> words;
        ifstream in(f);
        string token;
        while (in >> token) words.push_back(token);
        return words;
    };
    return read_file(file1) == read_file(file2);
}

int32_t main() {
    srand(time(0));
    std::random_device rd;
    std::mt19937 g(rd());
    for (int t = 0;; t++) {
        cout << "testing: " << t << endl;

        ofstream out("in.txt");

        {
            //generate test cases here
            out << 1 << "\n";
            int n = rnd(1, 10), k = rnd(0, 20);
            out << n << " " << k << "\n";
            for (int i = 0; i < n; i++){
                out << rnd(0, 10) << " " << rnd(0, 10) << "\n";
            }
        }

        out.close();

        system("C:\\Users\\samar\\Coding\\Competitive_Programming\\cmake-build-debug\\real.exe < in.txt > out1.txt");
        system("C:\\Users\\samar\\Coding\\Competitive_Programming\\cmake-build-debug\\brute.exe < in.txt > out2.txt");

        if (!equal("out1.txt", "out2.txt")) {
            cout << "difference found\n";
            return 0;
        }
    }
}