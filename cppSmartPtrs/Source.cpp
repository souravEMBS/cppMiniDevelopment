#include <iostream>
#include <string>
#include <memory>

class Entity
{
public:
	Entity();
	~Entity();

	void printTest(const int data) {
		std::cout << data << std::endl;
	}

private:

};

Entity::Entity()
{
	std::cout << "create entity" << std::endl;
}

Entity::~Entity()
{
	std::cout << "delete entity" << std::endl;
}


int main()
{
	//unique pointer start
	{
		//make_unique is a good way to use unique pointer for keeping exception safety
		std::unique_ptr<Entity> entity = std::make_unique<Entity>();
		//std::unique_ptr<Entity> e0 = entity; <- this line is note allowed in unique pointer
		entity->printTest(1);
	}
	//unique pointer end

	//shared pointer start
	{
		//make_shared removes the use of new and delete keyword, and helps in making the shared control block.
		std::shared_ptr<Entity> sharedEntity = std::make_shared<Entity>(); 
		sharedEntity->printTest(2);
		std::shared_ptr<Entity> e0 = sharedEntity; //<- this is allowed in shared pointer
		e0->printTest(3);
	}
	//shared pointer end

	//weak pointer start
	std::weak_ptr<Entity> e1;
	{
		//weak pointer doesn't increase the ref count in the control bock allocated as is done in shared pointer
		std::shared_ptr<Entity> sharedEntity = std::make_shared<Entity>();
		sharedEntity->printTest(4);
		std::shared_ptr<Entity> e0 = sharedEntity; //<- this is allowed in shared pointer
		e0->printTest(5);

	}
	//weak pointer end
	std::cin.get();

}