#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> string_vector(const string &num)
{
    vector<int> result;
    for (int i = num.size() - 1; i >= 0; i--)
    {
        result.push_back(num[i] - '0');
    }
    return result;
}

string vector_string(vector<int> nums)
{
    if (nums.size() == 0)
        return "0";
    string result;
    for (int i = nums.size() - 1; i >= 0; i--)
        result += (nums[i] + '0');
    return result;
}

vector<int> add(vector<int> a, vector<int> b)
{
    vector<int> result;
    int carry = 0;
    int n = max(a.size(), b.size());

    for (int i = 0; i < n; ++i)
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

int main()
{
    string num1, num2;
    string result;
    vector<int> vnum1, vnum2;
    char op;

    cout << "Enter first big integer: ";
    cin >> num1;
    cout << "Enter operator (+, -, *, /, %): ";
    cin >> op;
    cout << "Enter second big integer: ";
    cin >> num2;
    if (op == '+')
    {
        result = vector_string(add(string_vector(num1), string_vector(num2)));
        cout << result;
    }
    else if (op == '-')
    {
    }
    else if (op == '*')
    {
    }
    else if (op == '/')
    {
    }
    else if (op == '%')
    {
    }
    else
    {
        cout << "Invalid operator!" << endl;
    }

    return 0;
}
