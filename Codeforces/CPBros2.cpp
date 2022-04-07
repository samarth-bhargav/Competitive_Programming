/*
ID: samarth10
LANG: C++11
TASK: 
*/
#include <bits/stdc++.h>
using namespace std;
long ConvertTo10(const string& input, int base)
{
    if(base < 2 || base > 36)
        return 0;
    bool isNegative = (input[0] == '-');
    int startIndex = input.length()-1;
    int endIndex   = isNegative ? 1 : 0;
    long value = 0;
    int digitValue = 1;
    for(int i = startIndex; i >= endIndex; --i)
    {
        char c = input[i];
        if(c >= 'a' && c <= 'z')
            c -= ('a' - 'A');
        if(c >= '0' && c <= '9')
            c -= '0';
        else
            c = c - 'A' + 10;
        if(c >= base)
            return 0;
        value += c * digitValue;
        digitValue *= base;
    }
    if(isNegative)
        value *= -1;
    return value;
}

// Convert base 10 to arbitrary base
// - Base must be between 2 and 36
// - If base is invalid, returns "0"
// - NOTE: this whole function could be done with itoa
string ConvertFrom10(long value, int base)
{
    if(base < 2 || base > 36)
        return "0";

    bool isNegative = (value < 0);
    if(isNegative)
        value *= -1;
    string output;

    do
    {
        char digit = value % base;
        if(digit < 10)
            digit += '0';
        else
            digit = digit + 'A' - 10;
        output += digit;
        value /= base;
    } while (value > 0);
    if(isNegative)
        output += '-';
    reverse(output.begin(), output.end());
    return output;
}
string ConvertBase(const string& input, int baseFrom, int baseTo)
{
    return ConvertFrom10(ConvertTo10(input, baseFrom), baseTo);
}
int CharToInt (char c){
    return c-48;
}
// O(1) Time Complexity
char IntToChar (int c){
    return c + '0';
}
// O(1) Time Complexity

//For Int To String, Float to String, etc. use std::to_string
long long StringtoLL (string s){
    return stoll(s);
}
double StringtoDouble (string s){
    return stod(s);
}
int StringtoInt (string s){
    return stoi(s);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string a,c;
    cin >> a >> c;
    string s = ConvertBase(a,10,3);
    string q = ConvertBase(c, 10, 3);
    string b;
    int x = q.length() - s.length();
    int y = s.length() - q.length();
    if (s.length() < q.length()){
        for (int i = 0; i < x; i++){
            s.insert(0,"0");
        }
    }
    else{
        for (int i = 0; i < y; i++){
            q.insert(0,"0");
        }
    }
    for (int i = 0; i < s.length(); i++){
        b += IntToChar((((CharToInt(q[i])-CharToInt(s[i]))%3) + 3)%3);
    }
    b = ConvertBase(b, 3, 10);
    cout << b << "\n";
}

