#include <iostream>
#include <cmath>
#include<vector>
#include <unordered_map>
#include <string>
#include<bits/stdc++.h>
using namespace std;

// Function to convert binary to decimal
int binaryToDecimal(string n)
{
    string num = n;

    // Stores the decimal value
    int dec_value = 0;

    // Initializing base value to 1
    int base = 1;

    int len = num.length();
    for (int i = len - 1; i >= 0; i--) {

        // If the current bit is 1
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }

    // Return answer
    return dec_value;
}
string setStringtoASCII(string str)
{
    // To store size of s
    int N = int(str.size());

    // If given string is not a
    // valid string
    if (N % 8 != 0) {
        return "Not Possible!";
    }

    // To store final answer
    string res = "";

    // Loop to iterate through string
    for (int i = 0; i < N; i += 8) {
        int decimal_value
            = binaryToDecimal((str.substr(i, 8)));

        // Apprend the ASCII character
        // equivalent to current value
        res += char(decimal_value);
    }

    // Return Answer
    return res;
}

int main()
{
    string s = "0110000101100010";
    cout << setStringtoASCII(s);

    return 0;
}