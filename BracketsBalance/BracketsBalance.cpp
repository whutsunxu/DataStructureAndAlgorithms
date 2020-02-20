#include "BracketsBalance.h"
#include <iostream>
#include <stack>

bool BracketsBalance(const char* a, int M)
{
	using namespace std;
	stack<char> txt;

	for (int i = 0; i < M; i++)
	{
		if (a[i] == '{' || a[i] == '[' || a[i] == '(')
		{
			txt.push(a[i]);
		}
		else if (a[i] == '}')
		{
			if (txt.top() == '{')
				txt.pop();
			else
				break;
		}
		else if (a[i] == ']')
		{
			if (txt.top() == '[')
				txt.pop();
			else
				break;
		}
		else if (a[i] == ')')
		{
			if (txt.top() == '(')
				txt.pop();
			else
				break;
		}			
	}
	if (txt.empty())
	{
		cout << "Leagal Text!" << endl;
		return true;;
	}
	else
	{
		cout << "Illeagal Text" << endl;
		return false;
	}
}