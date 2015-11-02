#ifndef B_PLUS_TREE_HPP
#define B_PLUS_TREE_HPP

#include <vector>
#include <string>

#define LAST_POINTER (pointer_num_ - 1)
#define MAX_VALUE_NUM (pointer_num_ - 1)
#define DEFAULT_POINTER_NUM 4

enum NodeState {EMPTY, NONLEAF, LEAF};

template <class T>
struct Node {
	int num;
	char state;
	int value_num;
	int *pointer;
	T *value;
	Node(int n) {
		state = EMPTY;
		value_num = 0;
		pointer = new int[n];
		value = new T[n - 1];
	}
};

template <class T>
class BPlusTree {
	int pointer_num_;
	std::vector<Node<T> *> node_;
	Node<T> *swapper_;
	std::vector<int> queue_;
	int root_;
public:
	BPlusTree();
	BPlusTree(int n);
	Node<T> *GetNode(int node_num);
	Node<T> *GetAnAvailableNode();
	Node<T> *FindLeafNode(T value);
	void Insert(T value, int pointer);
	void InsertInLeaf(Node<T> *node, T value, int pointer);
	void InsertInNonleaf(Node<T> *node, int pointer_left, T value, int pointer_right);
	void InsertInParent(Node<T> *node_left, T value, Node<T> *node_right);
	void Delete(T value);
	void DeleteEntry(Node<T> *node, T value);
	void DeleteInNode(Node<T> *node, T value);
	bool GetSiblingAndSeperator(Node<T> *node, int pointer, Node<T> *&sibling_node, T &seperator);
	void ReplaceSeperator(Node<T> *node, T a, T b);
};

#include "b_plus_tree.cpp"

#endif // B_PLUS_TREE_HPP
