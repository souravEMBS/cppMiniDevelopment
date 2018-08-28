#include <iostream>
#include <thread>

using namespace std;

void foo_1()
{
	std::cout << "t1 thread" << std::endl;

}
class Fctor{
public:

	void operator()(std::string& name){
		for (int i = 10; i > 0; i--)
		{
			/* code */
			cout << "t1 thread: " << std::this_thread::get_id() << endl;
			cout << "from t1 " << name << ": " << i << endl;
		}
	}
};

int main()
{
	string s = "sourav";
	Fctor f1;
	unsigned int n = std::thread::hardware_concurrency(); //number of threads supported

	cout << "number of thread supported: "<< n << endl;
	//parent thread id
	cout << "main thread: " << std::this_thread::get_id() << endl;

 	/*t1 start, ref is used to pass a thread by refference,
	by standatd threads can only be passed by values*/
	std::thread t1(f1,std::ref(s)); 


	/*move function allows the thread to be passed by refference into the destination
	it is very efficient*/
	std::thread t2 = std::move(t1);

	try
	{	
		for (int i = 0; i < 10; ++i)
		{
			/* code */
			cout << "main: " << i << endl;
		}
	}
	catch(...){
		t1.join();
		throw;
	}
	t2.join();

	return 0;
}