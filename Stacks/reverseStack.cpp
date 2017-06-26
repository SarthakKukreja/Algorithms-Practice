// Sarthak Kukreja.
// Reverses a stack using recursion.

#include <iostream>
#include <stack>
#include <string>
using namespace std;

template <typename t>
void display( stack<t> stk , string str )
{
	cout << str << " : ";

	while(!stk.empty())
	{
		cout << stk.top() << " ";
		stk.pop();
	}

	cout << "\n";
}

template <typename t>
void transfer( stack<t> &main_stack , stack<t> &helper_stack)
{
	if(main_stack.empty()) return;

	t elem = main_stack.top();
	main_stack.pop();
	transfer(main_stack , helper_stack);
	helper_stack.push(elem);
}

template <typename t>
void reverse( stack<t> &main_stack , stack<t> &helper_stack)
{
	transfer( main_stack , helper_stack );

	while(!helper_stack.empty())
	{
		t elem = helper_stack.top();
		helper_stack.pop();
		main_stack.push(elem);
	}

}

stack<int> inputIntegerStack()
{
	int n;
	stack<int> s;

	while( cin >> n && n != -1)
	{
		s.push(n);
	}

	return s;
}

int main()
{
	stack<int> main_stack = inputIntegerStack();
	stack<int> helper_stack;
	reverse( main_stack , helper_stack);
	display( main_stack , "Displaying Elements from orignal Stack in LIFO Manner");
	return 0;
}
