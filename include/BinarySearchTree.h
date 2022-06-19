#pragma once

#include <cstddef>
#include <optional>
#include <functional>
#include <vector>
#include <iostream>
#include <memory>

template<typename T> concept Comparable = requires(T t) { t < t; t == t; };

template<Comparable T> struct BSTNode
{
	BSTNode* left;
	BSTNode* right;
	T data;
};

template<Comparable T> BSTNode<T>* Minimum(BSTNode<T>* node)
{
	if (!node->left)
		return node;
	return Minimum(node->left);
}

template<Comparable T> class BinarySearchTree
{
public:
	using Node = BSTNode<T>;

	BinarySearchTree()
		: m_Root{nullptr}
	{
	}
	~BinarySearchTree()
	{
		this->Clear(Root());
	}

	// void Insert(const T& value) { m_Root = InnerInsert(m_Root, value); }
	// void Insert(const T& value) { m_Root = InnerInsert(m_Root, value); }
	void Insert(T&& value) { m_Root = InnerInsert(m_Root, std::forward<T>(value)); }
	Node* Find(Node* node, const T& value)
	{
		if (!node || node->data == value)
			return node;

		else if (value < node->data)
			return Find(node->left, value);

		else return Find(node->right, value);
	}
	Node* Erase(Node* node, const T& value)
	{
		if (!node)
			return nullptr;

		else if (value < node->data)
			node->left = Erase(node->left, value);

		else if (node->data < value)
			node->right = Erase(node->right, value);

		else
		{
			if (!node->left && !node->right)
			{
				delete node;
				node = nullptr;
			}
			else if (!node->left)
			{
				Node* temp = node;
				node = node->right;
				delete temp;
			}
			else if (!node->right)
			{
				Node* temp = node;
				node = node->left;
				delete temp;
			}
			else if (node->left && node->right)
			{
				Node* temp = Minimum(node->right);
				node->data = temp->data;
				node->right = Erase(node->right, temp->data);
			}
 		}
 		return node;
	}
	size_t Size(Node* node) const 
	{
		if (!node)
			return 0;

		size_t rightSize = Size(node->right);
		size_t leftSize = Size(node->left);
		return rightSize + leftSize + 1;
	}
	int Height(Node* node) const
	{
		if (!node)
			return -1;

		int rightHeight = Height(node->right);
		int leftHeight = Height(node->left);

		if (leftHeight > rightHeight)
			return leftHeight + 1;

		else return rightHeight + 1;
	}
	static void InorderTraversal(const Node* node)
	{
		if (node)
		{
			InorderTraversal(node->left);
			std::cout << node->data << std::endl;
			InorderTraversal(node->right);
		}
	}
	Node*& Root() { return this->m_Root; }
	const Node*& Root() const { return this->m_Root; }
	std::shared_ptr<std::vector<T>> FindInRange(const T& lhs, const T& rhs)
	{
		std::shared_ptr<std::vector<T>> vec = std::make_shared<std::vector<T>>();
		InnerFindInRange(*vec, this->Root(), lhs, rhs);
		return vec;
	}
	static void Clear(Node* node)
	{
		if (!node)
			return;
		
		if (node->left)
			Clear(node->left);

		if (node->right)
			Clear(node->right);

		delete node;
		node = nullptr;
	}
private:
	void InnerFindInRange(std::vector<T>& vec, Node* node, const T& lhs, const T& rhs)
	{
		if (!node)
			return;

		else if (node->data < lhs)
			InnerFindInRange(vec, node->right, lhs, rhs);

		else if (rhs < node->data)
			InnerFindInRange(vec, node->left, lhs, rhs);

		else 
		{
			vec.push_back(node->data);
			InnerFindInRange(vec, node->right, lhs, rhs);
			InnerFindInRange(vec, node->left, lhs, rhs);
		}
	}

	Node* InnerInsert(Node* node, T&& value)
	{
		if (!node)
		{
			return new Node{.data = value};
		}

		else if (value < node->data)
			node->left = InnerInsert(node->left, std::forward<T>(value));

		else if (node->data < value)
			node->right = InnerInsert(node->right, std::forward<T>(value));

		return node;
	}

	Node* InnerInsert(Node* node, const T& value)
	{
		if (!node)
		{
			return new Node{.data = value};
		}

		else if (value < node->data)
			node->left = InnerInsert(node->left, value);

		else if (node->data < value)
			node->right = InnerInsert(node->right, value);

		return node;
	}

	Node* m_Root;
};

template<Comparable T> 
std::pair<BSTNode<T>*, BSTNode<T>*> Split(BSTNode<T>* node, const T& value)
{
	using Node = BSTNode<T>;
	using Pair = std::pair<Node*, Node*>;

	if (!node)
		return std::make_pair(nullptr, nullptr);

	else if (node->data < value)
	{
		Pair pair = Split(node->right, value);
		node->right = pair.first;
		return std::make_pair(node, pair.second);
	}
	else
	{
		Pair pair = Split(node->left, value);
		node->left = pair.second;
		return std::make_pair(pair.first, node);
	}
}

template<Comparable T> 
BSTNode<T>* Merge(BSTNode<T>* first, BSTNode<T>* second)
{
	using Node = BSTNode<T>;

	if (!first)
		return second;

	if (!second)
		return first;

	else if (second->data < first->data)
	{
		first->right = Merge(first->right, second);
		return first;
	}
	else
	{
		second->left = Merge(first, second->left);
		return second;
	}
}

template<Comparable T> void EraseRange(BinarySearchTree<T>& tree, const T& lhs, const T& rhs)
{
	using Node = BSTNode<T>;

	std::pair<Node*, Node*> firstPair = Split(tree.Root(), lhs);
	std::pair<Node*, Node*> secondPair = Split(firstPair.second, rhs);
	BinarySearchTree<T>::Clear(secondPair.first);
	
	tree.Root() = Merge(firstPair.first, secondPair.second);
}