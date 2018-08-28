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


using namespace std;


class Fctor{

private:
	//define mutex
	std::mutex mutex1;
	std::mutex mutex2;
	ofstream f;

public:

	//constructor
	Fctor(){
		f.open("log.txt");
	}
	void operat1(std::string name,int value){

		//mutex trick-  lock all in the same order

		/* code */
		//std lock provides deadlock avoiding algorithm
		//(use only when 2 or more locks are needed
		std::lock(mutex1,mutex2);

		//Resource aqq is init technique for mutex lock and unlock

		//in this example one lock can also be used.
		//adopt_lock ensures that all resources are properly released
		std::lock_guard<std::mutex> locker1(mutex1,std::adopt_lock);
		std::lock_guard<std::mutex> locker2(mutex2,std::adopt_lock);
		cout << "from "<< name  << " : " << value << endl;
	}

	void operat2(std::string name,int value){

		/* code */
		//std lock provides deadlock avoiding algorithm
		std::lock(mutex1,mutex2);

		//Resource aqq is init technique for mutex lock and unlock
		std::lock_guard<std::mutex> locker1(mutex1,std::adopt_lock);
		std::lock_guard<std::mutex> locker2(mutex2,std::adopt_lock);
		cout << "from "<< name  << " : " << value << endl;
	}

	//destructor
	~Fctor(){
		cout << "destruct" << endl;
		f.close();
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

