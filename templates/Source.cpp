#include <iostream>
#include <string>

template <typename arrayType,int size>
class array{
private:
	arrayType m_Array[size];
public:
	int GetSize() const { return size;  }
	int GetType() const{ return sizeof(arrayType); }
};

template <typename t>
void print(t values)
{
	std::cout << values << std::endl;
}

int main()
{
	print(5);
	print("Hello");
	print(100.23);

	array<std::string, 5> a;
	std::cout << a.GetSize() << std::endl;
	std::cout << a.GetType() << std::endl;

	std::cin.get();
}