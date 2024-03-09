#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

/* Enums */
enum class ObjectType {
	Integer,
	String
};

/* Structures */
struct BaseObject
{
	/*
		# Base Object (struct)

		## Description
		A base-class for all objects which stores a type value. This is used for 
		storing run-time type information used by this rudimentary "reflection" 
		system example.
	*/

	/* Elements */
	ObjectType type;
};

template <typename T>
struct TemplateObject : BaseObject
{
	/*
		# Template Object (struct)

		## Description
		A template object type that has an associated value. It inherits from the 
		base class, allowing classes derived from it with specialization to be 
		referenced by type-agnostic pointers while still being able to store distinct 
		types of data.
	*/

	/* Elements */
	T value;
};

struct IntegerObject : TemplateObject<int>
{
	/*
		# Integer Object (struct)
	*/

	/* Methods */
	IntegerObject()
	{
		this->type = ObjectType::Integer;
		this->value = 0;
	};
};

struct StringObject : TemplateObject<std::string>
{
	/*
		# String Object (struct)
	*/

	/* Methods */
	StringObject()
	{
		this->type = ObjectType::String;
		this->value = "";
	};
};

/* Type Definitions */
typedef BaseObject* BaseObjectPointer; // So that the BaseObject*& below doesn't get interpreted incorrectly. Alternatively, to avoid writing `const BaseObject* const&`.

/* Functions */
inline bool isString(const BaseObjectPointer& _object)
{
	return (_object->type == ObjectType::String);
};
inline bool isInteger(const BaseObjectPointer& _object)
{
	return (_object->type == ObjectType::Integer);
};

/* Main */
int main(int argc, char* argv[])
{
	// Allocate some variables,
	std::vector<BaseObject*> objects;
	StringObject* A = new StringObject();
	IntegerObject* B = new IntegerObject();

	// Make sure we can push different pointers to the vector,
	objects.push_back(A);
	objects.push_back(B);

	// For each pointer in the vector,
	for (auto object : objects)
	{
		// If a string, do some logic,
		if (isString(object))
		{
			((StringObject*)object)->value = "Hello World";
		}
		// Else, if an integer, do some other logic.
		else if (isInteger(object))
		{
			((IntegerObject*)object)->value = 10;
		};
	};

	// Now let's check this all worked.
	// For each pointer in the vector,
	for (auto object : objects)
	{
		// If a string, print it as-is,
		if (isString(object))
		{
			std::cout << ((StringObject*)object)->value << "\n";
		}
		// Else, if an integer, print it with some text to make it clear this logic was run.
		else if (isInteger(object))
		{
			std::cout << "Integer(" << ((IntegerObject*)object)->value << ")\n";
		};
	};

	// All done!
	std::cout << "Press [ENTER] to exit the program.\n";
	std::cin.get();
	return 0;
};