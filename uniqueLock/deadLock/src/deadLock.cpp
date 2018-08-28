//============================================================================
// Name        : deadLock.cpp
// Author      : Sourav
// Version     :
// Copyright   : Your copyright notice
// Description : Deadlock in C++, Ansi-style
//============================================================================

#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>

/* Unique lock can be less performance friendly
 than lock guard but provides more flexibility
 performace = lockguard
 flexibility = uniqulock
 */


using namespace std;


class Fctor{

private:
	//define mutex
	std::mutex mutex1;
	std::once_flag _oFlag;
	std::once_flag _cFlag;
	ofstream f;

public:

	//constructor
	Fctor(){}

	void operat1(std::string name,int value){

		//mutex trick-  lock all in the same order

		/* code */
		//std lock provides deadlock avoiding algorithm
		//(use only when 2 or more locks are needed
		//std::lock(mutex1,mutex2);

		//lazy innitialisation, checks if file is open or not.
//		{
//			std::unique_lock<mutex> locker3(mutex2);
//			if(!f.is_open()){
//				f.open("log.txt");
//			}
//		}

		//lamda function to call only once
		std::call_once(_oFlag,[&](){f.open("log.txt");});

		//Resource aqq is init technique for mutex lock and unlock

				//in this example one lock can also be used.
				//adopt_lock ensures that all resources are properly released
		std::unique_lock<mutex> locker1(mutex1,std::defer_lock);

		locker1.lock();
		f << "from "<< name  << " : " << value << endl;
		locker1.unlock();
	}

	void operat2(std::string name,int value){

		/* code */
		//std lock provides deadlock avoiding algorithm
		//std::lock(mutex1,mutex2);

		//Resource aqq is init technique for mutex lock and unlock
		std::unique_lock<mutex> locker2(mutex1,std::defer_lock);

		locker2.lock();
		f << "from "<< name  << " : " << value << endl;
		locker2.unlock();
	}

	//destructor
	~Fctor(){
		f << "destruct" << endl;
//		if(f.is_open()){
//			f.close();
//		}
		std::call_once(_cFlag,[&](){f.close();});
	}
};



void foo_1(Fctor& foo)
{
	for (int i = 100; i > 0; i--)
	{
		foo.operat2(string("thread"),i);
	}
}




int main()
{
	Fctor f1;
	std::string name = "sourav";

 	/*t1 start, ref is used to pass a thread by refference,
	by standatd threads can only be passed by values*/
	std::thread t1(foo_1,std::ref(f1));

	/*move function allows the thread to be passed by refference into the destination
	it is very efficient*/
	//std::thread t2(f1.operator(name),std::ref(f1));

	try
	{
		for (int i = 0; i < 100; ++i)
		{
			/* code */
			f1.operat1(string("main"),i);
		}
	}
	catch(...){
		t1.join();
		//t2.join();
		throw;
	}
	t1.join();
	//t2.join();

	return 0;
}

