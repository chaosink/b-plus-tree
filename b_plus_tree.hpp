#ifndef B_PLUS_TREE_HPP
#define B_PLUS_TREE_HPP

#include <vector>

#define LAST_POINTER (pointer_num_ - 1)
#define MAX_VALUE_NUM (pointer_num_ - 1)
#define DEFAULT_N 4

enum NodeState {EMPTY, NONLEAF, LEAF};

struct Node {
	int num;
	char state;
	int value_num;
	int *pointer;
	int *value;
	Node(int n) {
		state = EMPTY;
		value_num = 0;
		pointer = new int[n];
		value = new int[n - 1];
	}
};

class BPlusTree {
	int pointer_num_;
	std::vector<Node *> node_;
	Node *swapper;
	std::vector<int> queue_;
	int root_;
public:
	BPlusTree();
	BPlusTree(int n);
	Node *GetNode(int node_num);
	Node *GetAnAvailableNode();
	Node *FindLeafNode(int value);
	void Insert(int value, int pointer);
	void InsertInLeaf(Node *node, int value, int pointer);
	void InsertInNonleaf(Node *node, int pointer_left, int value, int pointer_right);
	void InsertInParent(Node *node_left, int value, Node *node_right);
	void Delete(int value);
	void DeleteEntry(Node *node, int value);
	void DeleteInNode(Node *node, int value);
	bool GetSiblingAndSeperator(Node *node, int pointer, Node *&sibling_node, int &seperator);
	void ReplaceSeperator(Node *node, int a, int b);
};

#endif // B_PLUS_TREE_HPP
