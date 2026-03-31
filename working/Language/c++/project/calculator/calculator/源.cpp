#include<iostream>
using namespace std;
#include<vector>
#include<string>
#include<stack>
#include<map>
#include<assert.h>

size_t priority_of(char a) {
	map<char, size_t> priority = { {'+',1},{'-',1},{ '*',2},{'/',2} };
	return priority[a];
}

void toRPN(string& s, size_t& pos ,vector<string>& RPN) {
	stack<char> stk;

	while (pos < s.size()) {
		if (isdigit(s[pos])) {
			string item;
			while (isdigit(s[pos])) {
				item += s[pos++];
			}
			RPN.push_back(item);
		}
		else if (s[pos] == '(') {
			++pos;
			toRPN(s, pos, RPN);
		}
		else if (s[pos] == ')') {
			while (!stk.empty()) {
				RPN.push_back(string(1, stk.top()));
				stk.pop();
			}
			++pos;
			return;
		}
		else {
			while (!stk.empty() && priority_of(s[pos]) <= priority_of(stk.top())) {
				RPN.push_back(string(1, stk.top()));
				stk.pop();
			}
			stk.push(s[pos++]);
		}
	}
	while (!stk.empty()) {
		RPN.push_back(string(1, stk.top()));
		stk.pop();
	}
}

int calculate(const vector<string>& RPN) {
	stack<int> stk;

	for (auto& item : RPN) {
		if (isdigit(item[0])) {
			stk.push(atoi(item.c_str()));
		}
		else {
			int right = stk.top();
			stk.pop();
			int left = stk.top();
			stk.pop();
			switch (item[0])
			{
			case '+':
				stk.push(left + right); break;
			case '-':
				stk.push(left - right); break;
			case'*':
				stk.push(left * right); break;
			case'/':
				stk.push(left / right); break;
			default:
				assert(false);
				break;
			}
		}
	}
	return stk.top();
}


int solve(const string& str) {
	string news;
	string stds;
	for (auto& e: str) {
		if (e != ' ') {
			news.push_back(e);
		}
	}
	for (size_t i = 0; i < news.size(); i++) {
		if (news[i] == '-') {
			if (i == 0 || (!isdigit(news[i - 1]) && news[i - 1] != ')')) {
				stds += "0-";
			}
			else {
				stds += '-';
			}
		}
		else {
			stds += news[i];
		}
	}
	//cout << news << endl;

	vector<string> RPN;
	size_t pos = 0;
	toRPN(stds, pos, RPN);

	/*for (auto& e : RPN) {
		cout << e;
	
	}*/

	return calculate(RPN);
}

int main()
{
	string s;
	getline(cin, s);

	int d = solve(s);

	cout << d;







	return 0;
}










