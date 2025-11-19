#include "../lib_algorithms/algorithms.h"
bool check_breckets(std::string s) {
	Stack<char> brackets;
	for (int i = 0; i<s.length();i++) 
	{
		char c = s[i];
		if (c == '(' || c == '{' || c == '[') {
			brackets.push(c);
		}
		else if (c == ')' || c == '}' || c == ']') {
			if (brackets.is_empty()) {
				return false;
			}

			char top = brackets.top();
			brackets.pop();
			if ((c == ')' && top != '(') || (c == '}' && top != '{') || (c == ']' && top != '[')) {
				return false;
			}

		}

	}
	return brackets.is_empty();

}