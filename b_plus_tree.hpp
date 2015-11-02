#ifndef B_PLUS_TREE_HPP
#define B_PLUS_TREE_HPP

#include <vector>
#include <string>

#define LAST_POINTER (pointer_num_ - 1)
#define MAX_VALUE_NUM (pointer_num_ - 1)
#define DEFAULT_POINTER_NUM 4

enum NodeState {EMPTY, NONLEAF, LEAF};

template <class V, class P>
struct Node {
	char state;
	int num;
	int value_num;
	P *pointer;
	V *value;
	Node(int n) {
		state = EMPTY;
		num = -1;
		value_num = 0;
		pointer = new P[n];
		value = new V[n - 1];
	}
};

template <class V, class P>
class BPlusTree {
	int pointer_num_;
	std::vector<Node<V, P> *> node_;
	Node<V, P> *swapper_;
	std::vector<int> queue_;
	int root_;
public:
	BPlusTree();
	BPlusTree(int n);
	Node<V, P> *GetNode(int node_num);
	Node<V, P> *GetAnAvailableNode();
	Node<V, P> *FindLeafNode(V value);
	void Insert(V value, P pointer);
	void InsertInLeaf(Node<V, P> *node, V value, P pointer);
	void InsertInNonleaf(Node<V, P> *node, P pointer_left, V value, P pointer_right);
	void InsertInParent(Node<V, P> *node_left, V value, Node<V, P> *node_right);
	void Delete(V value);
	void DeleteEntry(Node<V, P> *node, V value);
	void DeleteInNode(Node<V, P> *node, V value);
	bool GetSiblingAndSeperator(Node<V, P> *node, P pointer, Node<V, P> *&sibling_node, V &seperator);
	void ReplaceSeperator(Node<V, P> *node, V value_old, V value_new);
};

#include "b_plus_tree.cpp"

#endif // B_PLUS_TREE_HPP
