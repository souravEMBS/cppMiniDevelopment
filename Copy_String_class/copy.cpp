#include <iostream>
#include <string>

class String
{
public:
	String (const char* string)
	{
		size = strlen(string);
		m_Buffer = new char[size+1];
		memcpy(m_Buffer, string, size);
		m_Buffer[size] = 0;
	}
	

	String(const String& other)
		: size(other.size)
	{
		m_Buffer = new char[size + 1];
		memcpy(m_Buffer, other.m_Buffer, size+1);
	}

	char& operator[](unsigned int index)
	{
		return m_Buffer[index];
	}

	~String()
	{
		delete[] m_Buffer;
	}

	friend std::ostream& operator<<(std::ostream& stream, const String& string);
private:
	char* m_Buffer;
	unsigned int size;
};

std::ostream& operator<<(std::ostream& stream, const String& string)
{
	stream << string.m_Buffer;
	return stream;
}

void printString(const String& str)
{
	std::cout << str << std::endl;
}
int main()
{
	String string = "Hello string class";
	String copiedString = string;

	copiedString[6] = 'S';

	printString(string);
	printString(copiedString);

	std::cin.get();
}