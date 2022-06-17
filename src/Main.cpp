#include <iostream>
#include <BinarySearchTree.h>
#include <string>

struct Teacher
{
	std::string name;
	float reputation;

	bool operator<(const Teacher& other) const { return this->reputation < other.reputation; }
	bool operator==(const Teacher& other) const { return this->name == other.name && this->reputation == other.reputation; }
	bool operator!=(const Teacher& other) const { return !(*this == other); }

	friend std::ostream& operator<<(std::ostream& stream, const Teacher& teacher)
	{
		stream << teacher.name << ", reputation: " << teacher.reputation;
		return stream;
	}
};

int main()
{
	Teacher errorTeacher = {"Error!", -1.0f};
	Teacher teacher1 = {"Alex", 3.0f};
	Teacher teacher2 = {"Alexasd", 20.0f};
	Teacher teacher3 = {"Tur", 2.0f};
	Teacher teacher4 = {"Tuasdr", 25.0f};
	Teacher teacher5 = {"asdTuasdr", 29.0f};
	BinarySearchTree<Teacher> tree;
	tree.Insert(teacher1);
	tree.Insert(teacher2);
	tree.Insert(teacher3);
	tree.Insert(teacher4);
	tree.Insert(teacher5);
	std::cout << "\n\nBefore erase!\n\n";
	tree.InorderTraversal(tree.Root());
	std::cout << "\nBST Size: " << tree.Size() << std::endl;
	std::cout << "BST Height: " << tree.Height() << std::endl;
	std::cout << "\n\nAfter erase!\n\n";
	tree.Erase(tree.Root(), teacher4);
	tree.InorderTraversal(tree.Root());
	std::cout << "\nBST Size: " << tree.Size() << std::endl;
	std::cout << "BST Height: " << tree.Height() << std::endl;
	std::cout << "Searching for a teacher3...\n";
	auto val = tree.Find(teacher3);
	if (val)
	{
		std::cout << "Result: " << tree.Find(teacher3)->data << std::endl;
	}
	std::cout << "Searching for a teacher3... - done\n";
	std::cout << "Hello, World!\n";

	BinarySearchTree<int> tree2;
	for (int i = 0; i < 100; i++)
	{
		tree2.Insert(rand() % 1000);
	}

	// tree.InorderTraversal(tree.Root());
	auto vec = tree2.FindInRange(100, 300);
	for (int& i : *vec)
		std::cout << i << std::endl;
	return 0;
}