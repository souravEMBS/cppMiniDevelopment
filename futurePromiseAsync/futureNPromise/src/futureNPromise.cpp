//============================================================================
// Name        : futureNPromise.cpp
// Author      : Sourav
// Version     :
// Copyright   : Your copyright notice
// Description : Future and promise in C++, Ansi-style
//============================================================================

#include <iostream>
#include <thread>
#include <mutex>
#include <future>


using namespace std;


int factorial(std::future<int>& f){
	int res  = 1;
	int N = f.get();
	for(int i = N;i>1;i--)
		res *= i;
	cout << "factorial of " << N << " is " << res << endl;
	return res;
}

int main() {
	int x; // x is a shared variable between the child and parent thread
	//std::thread t1(factorial,4, std::ref(x)); //call by referrence

	std::promise<int> p;
	std::future<int> f = p.get_future();

	//to use multiple future use shared future
	std::future<int> fu = async(std::launch::async,factorial,std::ref(f));

	//.... do other stuffs

	std::this_thread::sleep_for(chrono::milliseconds(100));
	p.set_value(4);
	x = fu.get();//get function can be called only once

	cout << "Value returned from factorial: " << x << endl;

	//t1.join();


	return 0;
}
