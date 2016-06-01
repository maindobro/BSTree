#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "BSTreeException.h"
template <typename T>
class BSTree;

template <typename T>
struct Node;

template <typename T>
std::ostream & operator  << (std::ostream &output, BSTree<T> &);

template <typename T>
std::istream & operator >> (std::istream &input, BSTree<T> &);

template <typename T>
std::fstream & operator << (std::fstream &file, BSTree<T> &);

template <typename T>
std::fstream & operator >> (std::fstream &file, BSTree<T> &);

template <typename T>
class Iterator {
public:
	Iterator<T>(Node<T>* node) { fillvector(list_, node); }
	void fillvector(std::vector<T>& list, Node<T> * node)
	{
		if (node->left)
		{
			fillvector(list, node->left);
		}
		list.push_back(node->key);
		if (node->right)
		{
			fillvector(list, node->right);
		}
	}
private:
	std::vector<T> list_;
};

template <class T>
struct Node
{
	Node<T>() : key(0), left(nullptr), right(nullptr) {};
	Node<T>(const T &k) : key(k), left(nullptr), right(nullptr) {};

	T key;
	Node<T>* left;
	Node<T>* right;
	Node<T>* parent;

	static void fillList(std::vector<Node<T> *> & list, Node<T> * node)
	{
		if (node->left) 
		{
			fillList(list, node->left);
		}
		list.push_back(node);
		if (node->right) 
		{
			fillList(list, node->right);
		}
	}
	
};
template <typename T>
class BSTree
{
public:
	BSTree<T>() : root_(nullptr), size_(0) {};
	BSTree<T>(const std::initializer_list<T> &);
	~BSTree();
	Node<T>* root() { return root_; };
	Node<T>* search(const T &k) const;
	Node<T>* next(Node<T>* node) const;
	Node<T>* prev(Node<T>* node) const;
	Node<T>* min(Node<T>* node) const;
	Node<T>* max(Node<T>* node) const;
	void insert(const T &k);
	void remove(const T &k);
	void deletewithchild(const T &k);
	size_t size() { return size_; };
	void print(std::ostream &os/*=std::cout*/) const;
	friend std::ostream & operator << <>(std::ostream &output, BSTree &);
	friend std::istream & operator >> <>(std::istream &input, BSTree &);
	friend std::fstream & operator << <>(std::fstream &file, BSTree<T> &);
	friend std::fstream & operator >> <>(std::fstream &file, BSTree<T> &);
private:
	Node<T>* search(Node<T>* node, const T &k) const;
	void print(Node<T>*, std::ostream &) const;
	Node<T>* root_;
	size_t size_;
};
