//============================================================================
// Name        : conditionalVariables.cpp
// Author      : Sourav
// Version     :
// Copyright   : Your copyright notice
// Description : Condition Variables in C++, Ansi-style
//============================================================================

#include <iostream>
#include <thread>
#include <mutex>
#include <deque>
#include <condition_variable>

/* Unique lock can be less performance friendly
 than lock guard but provides more flexibility
 performace = lockguard
 flexibility = uniqulock
 */


using namespace std;
std::mutex _mu1;
std::deque<int> q;
std::condition_variable cond;

//producer of data
void func1(){
	int count = 10;
	while(count>0){
		std::unique_lock<mutex> locker(_mu1);
		q.push_front(count);
		locker.unlock();
		//cond.notify_all() to wake up all the threads
		cond.notify_one();//wake up one thread, if there is one.
		std::this_thread::sleep_for(chrono::seconds(1));
		count--;
	}
}

//consumer of data
void func2()
{
	int data =0;
	while(data != 1)
	{
		std::unique_lock<mutex> locker(_mu1);
		cond.wait(locker,[](){return !q.empty();});//interrupt based data push pop, avoids spurious wait
		data = q.back();
		q.pop_back();
		locker.unlock();
		cout << "t2 got a value from t1: " << data << endl;
	}
}

int main()
{
	std::thread t1(func1);
	std::thread t2(func2);
	t1.join();
	t2.join();
	return 0;
}

