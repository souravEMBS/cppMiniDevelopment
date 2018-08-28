#include <iostream>
#include <string>
#include <vector>

void PrintValues(int values)
{
	std::cout << "func ptr with value: " << values << std::endl;
}

void ForEach(const std::vector<int>& values,void(*func)(int))
{
	for (int value : values)
		func(value);

}


int main()
{
	std::vector<int> values = { 1,4,2,6,7 };
	ForEach(values, PrintValues);
	std::cin.get();
}