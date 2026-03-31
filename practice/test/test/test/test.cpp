#include <iostream>
using namespace std;

int main() {
    int n = 0;
    cin >> n;

    string str;
    cin >> str;

    char s;
    for (int i = 0; i < str.size() / 2; i++) {
        s = str[i];
        str[i] = str[str.size() - 1 - i];
        str[str.size() - 1] = s;
    }
    cout << str;
}