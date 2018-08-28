#include <iostream>
#include <string>
#include <vector>


struct vertex {
	float x, y, z;
	
	vertex(float x, float y, float z) 
		: x(x), y(y),z(z)
	{}

	vertex(const vertex& vert)
		: x(vert.x), y(vert.y), z(vert.z)
	{
		std::cout << "copied" << std::endl;
	}
};


std::ostream& operator<<(std::ostream& stream, const vertex& vertex)
{
	stream << vertex.x << "," << vertex.y << "," << vertex.z;
	return stream;
}
int main()
{
	std::vector<vertex> vert;
	vert.reserve(3);
	vert.emplace_back( 1,2,3 );
	vert.emplace_back( 4,5,6 );
	vert.emplace_back( 7,8,9 );
	for (int i = 0; i < vert.size(); i++)
		std::cout << vert[i] << std::endl;

	vert.erase(vert.begin() + 1);

	for (const vertex& v : vert)
		std::cout << v << std::endl;

	vert.clear();
	std::cin.get();
}