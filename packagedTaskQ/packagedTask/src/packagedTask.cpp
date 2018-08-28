//============================================================================
// Name        : packagedTask.cpp
// Author      : Sourav
// Version     :
// Copyright   : Your copyright notice
// Description : Packaged tasks in C++, Ansi-style
//============================================================================

#include <iostream>
#include <thread>
#include <future>
#include <mutex>
#include <functional>
#include <deque>
#include <string>
#include <condition_variable>

using namespace std;

int factorial(int N)
{
	int res =1;
	for (int i=N; i>1; i--)
		res *= i;
	cout << "factorial of " << N << " is " << res << endl;
	return res;
}

std::deque<std::packaged_task<int()> > task_q;
std::mutex mu;
std::condition_variable cond;

void thread_1(){
	std::packaged_task<int()> t;
	{
		std::unique_lock<std::mutex> locker(mu);
		cond.wait(locker,[](){return !task_q.empty();});
		t= std::move(task_q.front());
		task_q.pop_front();
	}
	t();
}

int main() {

	std::thread t1(thread_1);

	//packaged task is a template class int(int) is the function paremeter
	std::packaged_task<int()> t(bind(factorial,6));

	std::future<int> fu = t.get_future();

	//to pass the parameter into the packaged task bind function is used

	//std::packaged_task<int(int)> t(std::bind(factorial,6));

	{
		std::lock_guard<std::mutex> locker(mu);
		task_q.push_back(std::move(t));
	}
	cond.notify_one();

	//task can be executed in a later time in a different context

	//to get the return value of the function

	//int x = t.get_future().get();

	cout << "x :" << fu.get() << endl;

	t1.join();

	return 0;
}
