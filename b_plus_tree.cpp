#include <iostream>
#include <iomanip>
#include "b_plus_tree.hpp"
using namespace std;

#define DEBUG 1

BPlusTree::BPlusTree() {
	new (this) BPlusTree(DEFAULT_N);
}

BPlusTree::BPlusTree(int n) {
	pointer_num_ = n;
	root_ = -1;
	swapper = new Node(n + 1);
}

Node *BPlusTree::GetNode(int node_num) {
	return node_[node_num];
}

Node *BPlusTree::GetAnAvailableNode() {
	for(unsigned int i = 0; i < node_.size(); i++)
		if(node_[i]->state == EMPTY) return node_[i];
	Node *node = new Node(pointer_num_);
	node->num = node_.size();
	node_.push_back(node);
	return node_.back();
}

Node *BPlusTree::FindLeafNode(int value) {
if(DEBUG)
	cout << setw(20) << "FindLeafNode: " << setw(5) << value << endl;
	if(root_ == -1) return NULL;
	Node *node = GetNode(root_);
	queue_.clear();
	while(node->state != LEAF) {
		queue_.push_back(node->num);
		int i;
		for(i = 0; i < node->value_num; i++)
			if(value <= node->value[i]) break;
		if(i == node->value_num)
			node = GetNode(node->pointer[i]);
		else if(value == node->value[i])
			node = GetNode(node->pointer[i + 1]);
		else
			node = GetNode(node->pointer[i]);
	}
	return node;
}

void BPlusTree::Insert(int value, int pointer) {
if(DEBUG)
	cout << setw(20) << "Insert: " << setw(5) << value << " " << setw(5) << pointer << endl;
	if(root_ == -1) {
		Node *node = GetAnAvailableNode();
		node->state = LEAF;
		node->value_num = 1;
		node->value[0] = value;
		node->pointer[0] = pointer;
		node->pointer[LAST_POINTER] = -1;
		root_ = node->num;
		return;
	}
	Node *leaf_node = FindLeafNode(value);
	if(leaf_node->value_num < MAX_VALUE_NUM)
		InsertInLeaf(leaf_node, value, pointer);
	else {
		Node *node = GetAnAvailableNode();
		node->state = LEAF;
		for(int i = 0; i < MAX_VALUE_NUM; i++) swapper->value[i] = leaf_node->value[i];
		for(int i = 0; i < MAX_VALUE_NUM; i++) swapper->pointer[i] = leaf_node->pointer[i];
		swapper->value_num = MAX_VALUE_NUM;
		InsertInLeaf(swapper, value, pointer);
		node->pointer[LAST_POINTER] = leaf_node->pointer[LAST_POINTER];
		leaf_node->pointer[LAST_POINTER] = node->num;
		int mid = (pointer_num_ + 1) / 2;
		for(int i = 0; i < mid; i++) leaf_node->value[i] = swapper->value[i];
		for(int i = 0; i < mid; i++) leaf_node->pointer[i] = swapper->pointer[i];
		for(int i = mid; i < pointer_num_; i++) node->value[i - mid] = swapper->value[i];
		for(int i = mid; i < pointer_num_; i++) node->pointer[i - mid] = swapper->pointer[i];
		leaf_node->value_num = mid;
		node->value_num = pointer_num_ - mid;
		InsertInParent(leaf_node, node->value[0], node);
	}
}

void BPlusTree::InsertInLeaf(Node *node, int value, int pointer) {
if(DEBUG)
	cout << setw(20) << "InsertInLeaf: " << setw(5) << node->num << " " << setw(5) << value << " " << setw(5) << pointer << endl;
	if(value < node->value[0]) {
		for(int i = node->value_num - 1; i >= 0; i--) {
			node->value[i + 1] = node->value[i];
			node->pointer[i + 1] = node->pointer[i];
		}
		node->value[0] = value;
		node->pointer[0] = pointer;
		node->value_num++;
		return;
	}
	for(int i = node->value_num - 1; i >= 0; i--)
		if(value > node->value[i]) {
			for(int j = node->value_num - 1; j >= i + 1; j--) {
				node->value[j + 1] = node->value[j];
				node->pointer[j + 1] = node->pointer[j];
			}
			node->value[i + 1] = value;
			node->pointer[i + 1] = pointer;
			node->value_num++;
			return;
		}
}

void BPlusTree::InsertInNonleaf(Node *node, int pointer_left, int value, int pointer_right) {
if(DEBUG)
	cout << setw(20) << "InsertInNonleaf: " << setw(5) << node->num << " " << setw(5) << pointer_left << " " << setw(5) << value << " " << setw(5) << pointer_right << endl;
	for(int i = 0; i <= node->value_num; i++)
		if(node->pointer[i] == pointer_left) {
			node->value_num++;
			for(int j = node->value_num; j > i + 1; j--) {
				node->pointer[j] = node->pointer[j - 1];
				node->value[j - 1] = node->value[j - 2];
			}
			node->pointer[i + 1] = pointer_right;
			node->value[i] = value;
			return;
		}
}

void BPlusTree::InsertInParent(Node *node_left, int value, Node *node_right) {
if(DEBUG)
	cout << setw(20) << "InsertInParent: " << setw(5) << node_left->num << " " << setw(5) << value << " " << setw(5) << node_right->num << endl;
	if(node_left->num == root_) {
		Node *node = GetAnAvailableNode();
		node->state = NONLEAF;
		node->value_num = 1;
		node->pointer[0] = node_left->num;
		node->value[0] = value;
		node->pointer[1] = node_right->num;
		root_ = node->num;
		return;
	}
	Node *parent_node = GetNode(queue_.back());
	queue_.pop_back();
	if(parent_node->value_num < MAX_VALUE_NUM)
		InsertInNonleaf(parent_node, node_left->num, value, node_right->num);
	else {
		Node *node = GetAnAvailableNode();
		node->state = NONLEAF;
		for(int i = 0; i < MAX_VALUE_NUM; i++) swapper->value[i] = parent_node->value[i];
		for(int i = 0; i < pointer_num_; i++) swapper->pointer[i] = parent_node->pointer[i];
		swapper->value_num = MAX_VALUE_NUM;
		InsertInNonleaf(swapper, node_left->num, value, node_right->num);
		int mid = (pointer_num_ + 1) / 2;
		for(int i = 0; i < mid - 1; i++) parent_node->value[i] = swapper->value[i];
		for(int i = 0; i < mid; i++) parent_node->pointer[i] = swapper->pointer[i];
		for(int i = mid; i < pointer_num_; i++) node->value[i - mid] = swapper->value[i];
		for(int i = mid; i < pointer_num_ + 1; i++) node->pointer[i - mid] = swapper->pointer[i];
		parent_node->value_num = mid - 1;
		node->value_num = pointer_num_ - mid;
		InsertInParent(parent_node, swapper->value[mid - 1], node);
	}
}

void BPlusTree::Delete(int value) {
if(DEBUG)
	cout << setw(20) << "Delete: " << setw(5) << value << endl;
	Node *node = FindLeafNode(value);
	if(!node) {
if(DEBUG)
		cout << "Empty tree! Nothing to delete!" << endl;
		return;
	}
	DeleteEntry(node, value);
}

void BPlusTree::DeleteEntry(Node *node, int value) {
if(DEBUG)
	cout << setw(20) << "DeleteEntry: " << setw(5) << node->num << " " << setw(5) << value << endl;
	DeleteInNode(node, value);
	if(node->num == root_) {
		if(node->value_num == 0) {
			if(node->state == LEAF)
				root_ = -1;
			else
				root_ = node->pointer[0];
			node->state = EMPTY;
		}
		return;
	}
	if(node->state == LEAF) {
		if(node->value_num < pointer_num_ / 2) {
			Node *sibling_node;
			int seperator;
			bool is_predecessor = GetSiblingAndSeperator(GetNode(queue_.back()), node->num, sibling_node, seperator);
			if(sibling_node->value_num + node->value_num <= MAX_VALUE_NUM) {
				if(!is_predecessor) {
					Node *temp;
					temp = node;
					node = sibling_node;
					sibling_node = temp;
				}
				for(int i = 0; i < node->value_num; i++) {
					sibling_node->pointer[sibling_node->value_num + i] = node->pointer[i];
					sibling_node->value[sibling_node->value_num + i] = node->value[i];
				}
				sibling_node->value_num += node->value_num;
				sibling_node->pointer[LAST_POINTER] = node->pointer[LAST_POINTER];
				Node *parent = GetNode(queue_.back());
				queue_.pop_back();
				DeleteEntry(parent, seperator);
				node->state = EMPTY;
				return;
			} else {
				if(is_predecessor) {
					for(int i = node->value_num; i > 0; i--) {
						node->pointer[i] = node->pointer[i - 1];
						node->value[i] = node->value[i - 1];
					}
					node->pointer[0] = sibling_node->pointer[sibling_node->value_num - 1];
					node->value[0] = sibling_node->value[sibling_node->value_num - 1];
					node->value_num++;
					sibling_node->value_num--;
					ReplaceSeperator(GetNode(queue_.back()), seperator, node->value[0]); 
				} else {
					node->pointer[node->value_num] = sibling_node->pointer[0];
					node->value[node->value_num] = sibling_node->value[0];
					node->value_num++;
					for(int i = 0; i < sibling_node->value_num - 1; i++) {
						sibling_node->pointer[i] = sibling_node->pointer[i + 1];
						sibling_node->value[i] = sibling_node->value[i + 1];
					}
					sibling_node->value_num--;
					ReplaceSeperator(GetNode(queue_.back()), seperator, sibling_node->value[0]);
				}
			}
		}
	} else if(node->state == NONLEAF) {
		if(node->value_num < (pointer_num_ - 1) / 2) {
			Node *sibling_node;
			int seperator;
			bool is_predecessor = GetSiblingAndSeperator(GetNode(queue_.back()), node->num, sibling_node, seperator);
			if(sibling_node->value_num + node->value_num < MAX_VALUE_NUM) {
				if(!is_predecessor) {
					Node *temp;
					temp = node;
					node = sibling_node;
					sibling_node = temp;
				}
				sibling_node->value[sibling_node->value_num] = seperator;
				sibling_node->value_num++;
				for(int i = 0; i < node->value_num; i++) {
					sibling_node->pointer[sibling_node->value_num + i] = node->pointer[i];
					sibling_node->value[sibling_node->value_num + i] = node->value[i];
				}
				sibling_node->value_num += node->value_num;
				sibling_node->pointer[sibling_node->value_num] = node->pointer[node->value_num];
				Node *parent = GetNode(queue_.back());
				queue_.pop_back();
				DeleteEntry(parent, seperator);
				node->state = EMPTY;
				return;
			} else {
				if(is_predecessor) {
					node->pointer[node->value_num + 1] = node->pointer[node->value_num];
					for(int i = node->value_num; i > 0; i--) {
						node->pointer[i] = node->pointer[i - 1];
						node->value[i] = node->value[i - 1];
					}
					node->pointer[0] = sibling_node->pointer[sibling_node->value_num];
					node->value[0] = seperator;
					node->value_num++;
					sibling_node->value_num--;
					ReplaceSeperator(GetNode(queue_.back()), seperator, sibling_node->value[sibling_node->value_num]);
				} else {
					ReplaceSeperator(GetNode(queue_.back()), seperator, sibling_node->value[0]);
					node->pointer[node->value_num + 1] = sibling_node->pointer[0];
					node->value[node->value_num] = seperator;
					node->value_num++;
					for(int i = 0; i < sibling_node->value_num - 1; i++) {
						sibling_node->pointer[i] = sibling_node->pointer[i + 1];
						sibling_node->value[i] = sibling_node->value[i + 1];
					}
					sibling_node->value_num--;
					sibling_node->pointer[sibling_node->value_num] = sibling_node->pointer[sibling_node->value_num + 1];
				}
			}
		}
	}
}

void BPlusTree::DeleteInNode(Node *node, int value) {
if(DEBUG)
	cout << setw(20) << "DeleteInNode: " << setw(5) << node->num << " " << setw(5) << value << endl;
	for(int i = 0; i < node->value_num; i++)
		if(node->value[i] == value) {
			for(int j = i; j < node->value_num - 1; j++) {
				if(node->state == LEAF)
					node->pointer[j] = node->pointer[j + 1];
				else
					node->pointer[j + 1] = node->pointer[j + 2];
				node->value[j] = node->value[j + 1];
			}
			node->value_num--;
			return;
		}
}

bool BPlusTree::GetSiblingAndSeperator(Node *node, int pointer, Node *&sibling_node, int &seperator) {
	int i;
	for(i = 0; i <= node->value_num; i++)
		if(node->pointer[i] == pointer) break;
	if(i == node->value_num) {
		sibling_node = GetNode(node->pointer[i - 1]);
		seperator = node->value[i - 1];
		return true;
	} else {
		sibling_node = GetNode(node->pointer[i + 1]);
		seperator = node->value[i];
		return false;
	}
}

void BPlusTree::ReplaceSeperator(Node *node, int a, int b) {
if(DEBUG)
	cout << setw(20) << "ReplaceSeperator: " << setw(5) << node->num << " " << setw(5) << a << " " << setw(5) << b << endl;
	for(int i = 0; i < node->value_num; i++)
		if(node->value[i] == a) {
			node->value[i] = b;
			return;
		}
}
