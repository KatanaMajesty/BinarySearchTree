#include <iostream>
#include <BinarySearchTree.h>
#include <string>
#include <set>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

// from 0 to 18 446 744 073 709 551 615
size_t generateRandLong()
{
	unsigned long long result = 0;
	size_t iters = rand() % 14 + 6;
	for (size_t i = 0; i < iters; i++)
		result += (rand() % 10) * pow(10, i);
	 
	return result;
}

template<typename T> bool testBinarySearchTree()
{
	srand(time(NULL));
	const int iters = 80000;
	const int keysAmount = iters * 2;
	const int itersToRangeQueries = 1000;
	std::vector<T> data(keysAmount);
	std::vector<T> dataToInsert(iters);
	std::vector<T> dataToErase(iters);
	std::vector<T> dataToFind(iters);
	std::vector<std::pair<T, T>> dataToRangeQueries;

	for (int i = 0; i < iters; i++)
	{
		dataToInsert[i] = data[generateRandLong() % keysAmount];
		dataToErase[i] = data[generateRandLong() % keysAmount];
		dataToFind[i] = data[generateRandLong() % keysAmount];
	}
	for (int i = 0; i < itersToRangeQueries; i++)
	{
		T minT = T();
		T maxT = T();
		if (maxT < minT)
		{
			std::swap(minT, maxT);
		}
		dataToRangeQueries.push_back({minT, maxT});
	}
	BinarySearchTree<T> myTree;
	clock_t myStart = clock();
	for (int i = 0; i < iters; i++)
	{
		myTree.Insert(std::forward<T>(dataToInsert[i]));
	}
	int myInsertSize = myTree.Size(myTree.Root());
	int myTreeHeight = myTree.Height(myTree.Root());
	int optimalTreeHeight = log2(myInsertSize) + 1;
	for (int i = 0; i < iters; i++)
	{

		myTree.Erase(myTree.Root(), dataToErase[i]);
	}
	int myEraseSize = myInsertSize - myTree.Size(myTree.Root());
	int myFoundAmount = 0;
	for (int i = 0; i < iters; i++)
	{
		if (myTree.Find(myTree.Root(), dataToFind[i]))
		{
			myFoundAmount++;
		}
	}
	clock_t myEnd = clock();
	float myTime = (float(myEnd - myStart)) / CLOCKS_PER_SEC;
	std::set<T> stlTree;
	clock_t stlStart = clock();
	for (int i = 0; i < iters; i++)
	{
		stlTree.insert(dataToInsert[i]);
	}
	int stlInsertSize = stlTree.size();
	for (int i = 0; i < iters; i++)
	{
		stlTree.erase(dataToErase[i]);
	}
	int stlEraseSize = stlInsertSize - stlTree.size();
	int stlFoundAmount = 0;
	for (int i = 0; i < iters; i++)
	{
		if (stlTree.find(dataToFind[i]) != stlTree.end())
		{
			stlFoundAmount++;
		}
	}
	clock_t stlEnd = clock();
	float stlTime = (float(stlEnd - stlStart)) / CLOCKS_PER_SEC;

	clock_t myRangeStart = clock();
	int myRangeFoundAmount = 0;
	for (int i = 0; i < itersToRangeQueries; i++)
	{
		myRangeFoundAmount += myTree.FindInRange(dataToRangeQueries[i].first,
		dataToRangeQueries[i].second)->size();
	}
	clock_t myRangeEnd = clock();
	float myRangeTime = (float(myRangeEnd - myRangeStart)) / CLOCKS_PER_SEC;
	clock_t stlRangeStart = clock();
	int stlRangeFoundAmount = 0;
	for (int i = 0; i < itersToRangeQueries; i++)
	{
		const auto& low = stlTree.lower_bound(dataToRangeQueries[i].first);
		const auto& up = stlTree.upper_bound(dataToRangeQueries[i].second);
		stlRangeFoundAmount += distance(low, up);
	}
	clock_t stlRangeEnd = clock();
	float stlRangeTime = (float(stlRangeEnd - stlRangeStart)) / CLOCKS_PER_SEC;
	std::cout << "My BinaryTree: height = " << myTreeHeight << ", optimal height = " <<
	optimalTreeHeight << std::endl;
	std::cout << "Time: " << myTime << ", size: " << myInsertSize << " - " << myEraseSize << ",found amount: " 
	<< myFoundAmount << std::endl;
	std::cout << "Range time: " << myRangeTime << ", range found amount: " << myRangeFoundAmount
	<< std::endl << std::endl;
	std::cout << "STL Tree:" << std::endl;
	std::cout << "Time: " << stlTime << ", size: " << stlInsertSize << " - " << stlEraseSize <<
	", found amount: " << stlFoundAmount << std::endl;
	std::cout << "Range time: " << stlRangeTime << ", range found amount: " <<
	stlRangeFoundAmount << std::endl << std::endl;
	if (myInsertSize == stlInsertSize && myEraseSize == stlEraseSize &&
	myFoundAmount == stlFoundAmount && myRangeFoundAmount == stlRangeFoundAmount)
	{
		std::cout << "The lab is completed" << std::endl;
		return true;
	}
	std::cerr << ":(" << std::endl;
	return false;
}

struct Teacher
{
	Teacher()
		: name("1"), reputation{static_cast<float>(rand())}
	{
	}

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
	using Node = BSTNode<int>;
	std::cout << "[LOG] Testing BST with testBinarySearchTree() function...\n";
	testBinarySearchTree<Teacher>();
	std::cout << "[LOG] Testing BST with testBinarySearchTree() function... - DONE\n";
	BinarySearchTree<int> tree;
	for (int i = 0; i < 30; i++)
	{
		tree.Insert(std::forward<int>(rand() % 3000));
	}
	std::cout << "[LOG] Before EraseRange: \n";
	tree.InorderTraversal(tree.Root());
	std::cout << "[LOG] Erasing range...\n";
	EraseRange(tree, 362, 2387);
	std::cout << "[LOG] Erasing range... - DONE\n";
	std::cout << "[LOG] After EraseRange: \n";
	BinarySearchTree<int>::InorderTraversal(tree.Root());
	return 0;
}