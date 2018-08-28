//============================================================================
// Name        : Stack.cpp
// Author      : Sourav
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stack>

using namespace std;

int main() {
	stack<int> myStack;

	myStack.push(1);
	myStack.push(2);
	myStack.push(3);
	myStack.push(4);
	myStack.push(5);


	cout << "stack size: " << myStack.size() << endl;
	cout << "stack top before pop: " << myStack.top() << endl;

	myStack.pop();
	cout << "stack top after pop: " << myStack.top() << endl;


	return 0;
}
