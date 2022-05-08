#include <functional>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;

#define VT vector
typedef VT<int> VI;
typedef VT<VI> VVI;
typedef VT<string> VS;
typedef VT<double> VD;
#define REP(i,n) for(int _n=n, i=0;i<_n;++i)
#define FOR(i,a,b) for(int i=(a),_b=(b);i<=_b;++i)
#define ALL(c) c.begin(),c.end()
#define PB push_back
#define MP make_pair
#define FS first
#define SC second
#define SZ size()


int N;
vector<int> data;
const int infinity = 1e9;


int main()
{
    cin >> N;
    data.assign(N, 0);
    for (int i = 0; i < N; ++i)
    {
        cin >> data[i];
    }

    data.push_back(infinity);


    vector<int> minimal;
    vector<int> length;
    for (int i = 0; i < data.size(); ++i)
    {
        vector<int>::iterator it = lower_bound(minimal.begin(), minimal.end(), data[i]);

        if (it == minimal.end())
        {
            minimal.push_back(data[i]);
            length.push_back(minimal.size());
        }
        else
        {
            int index = distance(minimal.begin(), it);

            minimal[index] = data[i];
            length.push_back(index+1);
        }
    }

    vector<int> belongs(data.size(), false);
    map<int, multiset<int> > elements; //lengths -> last elements
    elements[length.back()].insert(data.back());

    belongs[data.size() - 1] = true;
    for (int i = data.size() - 1; i >= 0; --i)
    {
        int l = length[i];

        map<int, multiset<int> >::iterator it = elements.find(l + 1);
        if (it == elements.end())
            continue;

        multiset<int>& ends = it->second;

        if (ends.upper_bound(data[i]) != ends.end())
        {
            belongs[i] = true;
            elements[length[i]].insert(data[i]);
        }
    }


    string result(N, '1');

    for (int i = 0; i < N; ++i)
    {
        if (belongs[i])
        {
            if (elements[length[i]].size() == 1)
                result[i] = '3';
            else
                result[i] = '2';
        }
    }

    cout << result << endl;


}