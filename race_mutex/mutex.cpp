#include <iostream>
#include <thread>
#include <mutex>	
#include <fstream>


using namespace std;


class Fctor{

private:
	//define mutex
	std::mutex mutex1;
	ofstream f;

public:

	//constructor
	Fctor(){
		f.open("log.txt");
	}
	void operat(std::string name,int value){
		
			/* code */
			//Resource aqq is init technique for mutex lock and unlock
			std::lock_guard<std::mutex> locker(mutex1); 
			//mutex lock for the thread
			//mutex1.lock(); //not recommended
			//f << "from t1 " << name << ": " << i << endl;
			f << "from "<< name  << " : " << value << endl;

			//mutex unlock for the thread
			//mutex1.unlock();//not recommended
	}

	//destructor
	~Fctor(){
		cout << "destruct" << endl;
		f.close();
	}
};


class stack {
	int* _data;
	std::mutex _mu;
public:
	void pop(); //pops the item on top of stack
	int& top(); //returns the item on top

};

void foo_1(Fctor& foo)
{
	for (int i = 10; i > 0; i--)
	{
		foo.operat(string("thread"),i);
	}
}


int main()
{
	string thread1 = "thread 1";
	string thread2 = "thread 2";
	Fctor f1;
	std::string name = "sourav";
	//unsigned int n = std::thread::hardware_concurrency(); //number of threads supported

	//cout << "number of thread supported: "<< n << endl;
	//parent thread id
	//cout << "main thread: " << std::this_thread::get_id() << endl;

 	/*t1 start, ref is used to pass a thread by refference,
	by standatd threads can only be passed by values*/
	std::thread t1(foo_1,std::ref(f1)); 


	/*move function allows the thread to be passed by refference into the destination
	it is very efficient*/
	//std::thread t2(f1.operator(name),std::ref(f1));

	try
	{	
		for (int i = 0; i < 10; ++i)
		{
			/* code */
			f1.operat(string("main"),i);
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