#ifndef B_PLUS_TREE_HPP
#define B_PLUS_TREE_HPP

#include "buffer_manager.hpp"
#include <fstream>
#include <vector>
#include <iostream>

#define LAST_POINTER (pointer_num_ - 1)
#define MAX_VALUE_NUM (pointer_num_ - 1)

enum NodeState {EMPTY, NONLEAF, LEAF};

template <class V, class P>
struct Node {
	int *num;
	char *state;
	int *value_num;
	P *pointer;
	V *value;
	Node() {
		num = NULL;
		state = NULL;
		value_num = NULL;
		pointer = NULL;
		value = NULL;
	}
};

template <class V, class P>
class BPlusTree {
	std::string name_;
	int pointer_num_;
	int node_num_;
	int empty_node_num_;
	Node<V, P> swapper_;
	std::vector<int> queue_;
	int root_;
	BufferManager buffer_manager_;
	void AddOneBlock();
	Node<V, P> GetNode(int node_num);
	Node<V, P> GetAnAvailableNode();
	Node<V, P> FindLeafNode(V value);
	void InsertInLeaf(Node<V, P> node, V value, P pointer);
	void InsertInNonleaf(Node<V, P> node, int pointer_left_num, V value, int pointer_right_num);
	void InsertInParent(Node<V, P> node_left, V value, Node<V, P> node_right);
	void DeleteEntry(Node<V, P> node, V value);
	void DeleteInNode(Node<V, P> node, V value);
	bool GetSiblingAndSeperator(Node<V, P> node, P pointer, Node<V, P> &sibling_node, V &seperator);
	void ReplaceSeperator(Node<V, P> node, V value_old, V value_new);
public:
	BPlusTree(std::string name);
	~BPlusTree();
	P Find(V value);
	void Insert(V value, P pointer);
	void Delete(V value);
};

#include "b_plus_tree.cpp"

#endif // B_PLUS_TREE_HPP
