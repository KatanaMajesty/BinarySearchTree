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
		: m_Root{nullptr}, m_Size(0)
	{
		std::cout << "Constructing BST\n";
	}
	~BinarySearchTree()
	{
		this->Clear(Root());
		std::cout << "Destroying BST\n";
	}

	void Insert(const T& value) { m_Root = InnerInsertLval(m_Root, value); }
	void Insert(T&& value) { m_Root = InnerInsertRval(m_Root, std::move(value)); }
	Node* Find(const T& value)
	{
		return InnerFind(this->Root(), value);
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
				m_Size--;
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
	size_t Size() const { return m_Size; }
	size_t Height() const
	{
		return static_cast<size_t>(InnerHeight(this->Root()));
	}
	void InorderTraversal(const Node* node) const
	{
		if (node)
		{
			InorderTraversal(node->left);
			std::cout << node->data << std::endl;
			InorderTraversal(node->right);
		}
	}
	Node* Root() { return this->m_Root; }
	const Node* Root() const { return this->m_Root; }
	// returns a vector of pointers
	std::shared_ptr<std::vector<T>> FindInRange(const T& lhs, const T& rhs)
	{
		std::shared_ptr<std::vector<T>> vec = std::make_shared<std::vector<T>>();
		InnerFindInRange(*vec, this->Root(), lhs, rhs);
		return vec;
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
			std::cout << "Adding data: " << node->data << std::endl;
			vec.push_back(node->data);
			InnerFindInRange(vec, node->right, lhs, rhs);
			InnerFindInRange(vec, node->left, lhs, rhs);
		}
	}
	int InnerHeight(const Node* node) const
	{
		if (!node)
			return -1;

		int rightHeight = InnerHeight(node->right);
		int leftHeight = InnerHeight(node->left);

		if (leftHeight > rightHeight)
			return leftHeight + 1;

		else return rightHeight + 1;
	}
	void Clear(Node* node)
	{
		if (!node)
			return;
		
		if (node->left)
			Clear(node->left);

		if (node->right)
			Clear(node->right);

		delete node;
	}
	Node* InnerFind(Node* node, const T& value) const
	{
		if (!node || node->data == value)
			return node;

		else if (value < node->data)
			return InnerFind(node->left, value);

		else return InnerFind(node->right, value);
	}
	Node* InnerInsertLval(Node* node, const T& value)
	{
		if (!node)
		{
			m_Size++;
			return new Node{.data = value};
		}

		else if (value < node->data)
			node->left = InnerInsertLval(node->left, value);

		else if (node->data < value)
			node->right = InnerInsertLval(node->right, value);

		return node;
	}
	Node* InnerInsertRval(Node* node, T&& value)
	{
		if (!node)
		{
			m_Size++;
			return new Node{.data = std::move(value)};
		}

		else if (value < node->data)
			node->left = InnerInsertLval(node->left, std::move(value));

		else if (node->data < value)
			node->right = InnerInsertLval(node->right, std::move(value));

		return node;
	}
	Node* m_Root;
	size_t m_Size;
};