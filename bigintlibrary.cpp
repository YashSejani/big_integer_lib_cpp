#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> string_vector(string num)
{
    vector<int> result;
    for (int i = num.size() - 1; i >= 0; --i)
    {
        result.push_back(num[i] - '0');
    }
    return result;
}

string vector_string(vector<int> numVec)
{
    string result;
    bool leadingZero = true;
    for (int i = numVec.size() - 1; i >= 0; --i)
    {
        if (leadingZero && numVec[i] == 0)
            continue;
        leadingZero = false;
        result += (numVec[i] + '0');
    }
    return result.empty() ? "0" : result;
}

int compare(string num1, string num2)
{
    if (num1.length() > num2.length())
        return 1;
    if (num1.length() < num2.length())
        return -1;
    for (size_t i = 0; i < num1.length(); ++i)
    {
        if (num1[i] > num2[i])
            return 1;
        if (num1[i] < num2[i])
            return -1;
    }
    return 0;
}

vector<int> subtract(vector<int> a, vector<int> b)
{
    vector<int> result;
    int borrow = 0;
    for (int i = 0; i < a.size(); ++i)
    {
        int digitA = a[i];
        int digitB = (i < b.size()) ? b[i] : 0;
        int diff = digitA - digitB - borrow;
        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }
        result.push_back(diff);
    }
    while (result.size() > 1 && result.back() == 0)
        result.pop_back();
    return result;
}

vector<int> add(vector<int> a, vector<int> b)
{
    vector<int> result;
    int carry = 0;
    int maxLength = max(a.size(), b.size());

    for (int i = 0; i < maxLength; ++i)
    {
        int digitA = (i < a.size()) ? a[i] : 0;
        int digitB = (i < b.size()) ? b[i] : 0;
        int sum = digitA + digitB + carry;
        result.push_back(sum % 10);
        carry = sum / 10;
    }
    if (carry)
        result.push_back(carry);
    return result;
}

string subwithsign(string num1, string num2)
{
    int cmp = compare(num1, num2);
    vector<int> vec1 = string_vector(num1);
    vector<int> vec2 = string_vector(num2);
    vector<int> result;

    if (cmp == 0)
    {
        return "0";
    }
    else if (cmp > 0)
    {
        result = subtract(vec1, vec2);
        return vector_string(result);
    }
    else
    {
        result = subtract(vec2, vec1);
        return "-" + vector_string(result);
    }
}

vector<int> multiply(const vector<int> &a, const vector<int> &b)
{
    vector<int> result(a.size() + b.size(), 0);
    for (int i = 0; i < a.size(); ++i)
    {
        for (int j = 0; j < b.size(); ++j)
        {
            result[i + j] += a[i] * b[j];
            if (result[i + j] >= 10)
            {
                result[i + j + 1] += result[i + j] / 10;
                result[i + j] %= 10;
            }
        }
    }
    while (result.size() > 1 && result.back() == 0)
        result.pop_back();
    return result;
}

pair<string, string> divide_mod(const string &dividend, const string &divisor)
{
    if (compare(divisor, "0") == 0)
        return {"NaN", "NaN"};
    string quotient = "", remainder = "";
    for (char digit : dividend)
    {
        remainder += digit;
        int count = 0;
        while (compare(remainder, divisor) >= 0)
        {
            remainder = subwithsign(remainder, divisor);
            if (remainder[0] == '-')
                remainder = remainder.substr(1);
            count++;
        }
        quotient += (count + '0');
    }
    int i = 0;
    while (i < quotient.size() - 1 && quotient[i] == '0')
        i++;
    quotient = quotient.substr(i);
    return {quotient, remainder};
}

struct bigint
{
    bool isNegative;
    string value;
};

bigint setbigint(const string &str)
{
    bigint result;
    if (str[0] == '-')
    {
        result.isNegative = true;
        result.value = str.substr(1);
    }
    else
    {
        result.isNegative = false;
        result.value = str;
    }
    return result;
}

string addorsub(const string &num1, const string &num2)
{
    bigint a = setbigint(num1);
    bigint b = setbigint(num2);

    if (!a.isNegative && !b.isNegative)
    {
        return vector_string(add(string_vector(a.value), string_vector(b.value)));
    }
    else if (a.isNegative && b.isNegative)
    {
        return "-" + vector_string(add(string_vector(a.value), string_vector(b.value)));
    }
    else if (a.isNegative && !b.isNegative)
    {
        return subwithsign(b.value, a.value);
    }
    else
    {
        return subwithsign(a.value, b.value);
    }
}

string factorial(const string &num)
{
    string result = "1";
    string counter = "2";
    while (compare(counter, num) <= 0)
    {
        result = vector_string(multiply(string_vector(result), string_vector(counter)));
        counter = addorsub(counter, "1");
    }
    return result;
}

string npr(const string &n, const string &r)
{
    string fectofn = factorial(n);
    string nminr = subwithsign(n, r);
    if (nminr[0] == '-')
        return "0";
    string nminrfect = factorial(nminr);
    pair<string, string> div = divide_mod(fectofn, nminrfect);
    return div.first;
}

string ncr(const string &n, const string &r)
{
    string fectofn = factorial(n);
    string rfect = factorial(r);
    string nminr = subwithsign(n, r);
    if (nminr[0] == '-')
        return "0";
    string nminrfect = factorial(nminr);
    string denom = vector_string(multiply(string_vector(rfect), string_vector(nminrfect)));
    pair<string, string> div = divide_mod(fectofn, denom);
    return div.first;
}

int main()
{
    string num1, num2;
    char op;

    string result;
    cout << "Enter first number: " << endl;
    cin >> num1;
    cout << endl
         << "Enter operator (+, -, *, /, %, !, P, C): " << endl;
    cin >> op;
    cout << endl;
    if (op == '!')
    {
        result = factorial(num1);
        cout << "result: " << endl
             << result << endl;
        return 0;
    }
    cout << "Enter second number: " << endl;
    cin >> num2;
    cout << endl;
    if (op == '+')
    {
        result = addorsub(num1, num2);
    }
    else if (op == '-')
    {
        if (num2[0] == '-')
            num2 = num2.substr(1);
        else
            num2 = "-" + num2;
        result = addorsub(num1, num2);
    }
    else if (op == '*')
    {
        bigint a = setbigint(num1);
        bigint b = setbigint(num2);
        string product = vector_string(multiply(string_vector(a.value), string_vector(b.value)));
        if (a.isNegative != b.isNegative && product != "0")
            product = "-" + product;
        result = product;
    }
    else if (op == '/' || op == '%')
    {
        bigint a = setbigint(num1);
        bigint b = setbigint(num2);
        pair<string, string> divmod = divide_mod(a.value, b.value);
        if (op == '/')
        {
            if (a.isNegative != b.isNegative && divmod.first != "0")
                divmod.first = "-" + divmod.first;
            result = divmod.first;
        }
        else
        {
            if (a.isNegative && divmod.second != "0")
                divmod.second = "-" + divmod.second;
            result = divmod.second;
        }
    }
    else if (op == 'P')
    {
        result = npr(num1, num2);
    }
    else if (op == 'C')
    {
        result = ncr(num1, num2);
    }
    else
    {
        cout << "Invalid operator!" << endl;
    }

    cout << "result: " << endl
         << result << endl;
    return 0;
}
