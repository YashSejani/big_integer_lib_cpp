#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> string_vector(string num) {
    vector<int> result;
    for (int i = num.size() - 1; i >= 0; --i) {
        result.push_back(num[i] - '0');
    }
    return result;
}

string vector_string(vector<int> numVec) {
    string result;
    bool leadingZero = true;
    for (int i = numVec.size() - 1; i >= 0; --i) {
        if (leadingZero && numVec[i] == 0) continue;
        leadingZero = false;
        result += (numVec[i] + '0');
    }
    return result.empty() ? "0" : result;
}

int compare(string num1, string num2) {
    if (num1.length() > num2.length()) return 1;
    if (num1.length() < num2.length()) return -1;
    for (size_t i = 0; i < num1.length(); ++i) {
        if (num1[i] > num2[i]) return 1;
        if (num1[i] < num2[i]) return -1;
    }
    return 0;
}

vector<int> subtract(vector<int> a, vector<int> b) {
    vector<int> result;
    int borrow = 0;
    for (int i = 0; i < a.size(); ++i) {
        int digitA = a[i];
        int digitB = (i < b.size()) ? b[i] : 0;
        int diff = digitA - digitB - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.push_back(diff);
    }
    while (result.size() > 1 && result.back() == 0)
        result.pop_back();
    return result;
}

vector<int> add(vector<int> a, vector<int> b) {
    vector<int> result;
    int carry = 0;
    int maxLength = max(a.size(), b.size());

    for (int i = 0; i < maxLength; ++i) {
        int digitA = (i < a.size()) ? a[i] : 0;
        int digitB = (i < b.size()) ? b[i] : 0;
        int sum = digitA + digitB + carry;
        result.push_back(sum % 10);
        carry = sum / 10;
    }
    if (carry) result.push_back(carry);
    return result;
}

string subwithsign(string num1, string num2) {
    int cmp = compare(num1, num2);
    vector<int> vec1 = string_vector(num1);
    vector<int> vec2 = string_vector(num2);
    vector<int> result;

    if (cmp == 0) {
        return "0";
    } else if (cmp > 0) {
        result = subtract(vec1, vec2);
        return vector_string(result);
    } else {
        result = subtract(vec2, vec1);
        return "-" + vector_string(result);
    }
}

struct bigint {
    bool isNegative;
    string value;
};

bigint setbigint(const string& str) {
    bigint result;
    if (str[0] == '-') {
        result.isNegative = true;
        result.value = str.substr(1);
    } else {
        result.isNegative = false;
        result.value = str;
    }
    return result;
}

// Add or subtract depending on sign
string addorsub(const string& num1, const string& num2) {
    bigint a = setbigint(num1);
    bigint b = setbigint(num2);

    if (!a.isNegative && !b.isNegative) {
        return vector_string(add(string_vector(a.value), string_vector(b.value)));
    } else if (a.isNegative && b.isNegative) {
        return "-" + vector_string(add(string_vector(a.value), string_vector(b.value)));
    } else if (a.isNegative && !b.isNegative) {
        return subwithsign(b.value, a.value);
    } else {
        return subwithsign(a.value, b.value);
    }
}

int main() {
    string num1, num2;
    char op;

    cout << "Enter first number: ";
    cin >> num1;
    cout << "Enter operatin (+, -, *, /, %): ";
    cin >> op;
    cout << "Enter second number: ";
    cin >> num2;

    string result;

    if (op == '+') {
        result = addorsub(num1, num2);
    } else if (op == '-') {
        if (num2[0] == '-') num2 = num2.substr(1);
        else num2 = "-" + num2;
        result = addorsub(num1, num2);
    } else if (op == '*')
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

    cout << "Result: " << result << endl;
    return 0;
}

