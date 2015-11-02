#include "b_plus_tree.hpp"
using namespace std;

#define DEBUG 1

template <class T>
BPlusTree<T>::BPlusTree() {
	new (this) BPlusTree(DEFAULT_N);
}

template <class T>
BPlusTree<T>::BPlusTree(int n) {
	pointer_num_ = n;
	root_ = -1;
	swapper = new Node<T>(n + 1);
}

template <class T>
Node<T> *BPlusTree<T>::GetNode(int node_num) {
	return node_[node_num];
}

template <class T>
Node<T> *BPlusTree<T>::GetAnAvailableNode() {
	for(unsigned int i = 0; i < node_.size(); i++)
		if(node_[i]->state == EMPTY) return node_[i];
	Node<T> *node = new Node<T>(pointer_num_);
	node->num = node_.size();
	node_.push_back(node);
	return node_.back();
}

template <class T>
Node<T> *BPlusTree<T>::FindLeafNode(T value) {
	if(root_ == -1) return 0;
	Node<T> *node = GetNode(root_);
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

template <class T>
void BPlusTree<T>::Insert(T value, int pointer) {
	if(root_ == -1) {
		Node<T> *node = GetAnAvailableNode();
		node->state = LEAF;
		node->value_num = 1;
		node->value[0] = value;
		node->pointer[0] = pointer;
		node->pointer[LAST_POINTER] = -1;
		root_ = node->num;
		return;
	}
	Node<T> *leaf_node = FindLeafNode(value);
	if(leaf_node->value_num < MAX_VALUE_NUM)
		InsertInLeaf(leaf_node, value, pointer);
	else {
		Node<T> *node = GetAnAvailableNode();
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

template <class T>
void BPlusTree<T>::InsertInLeaf(Node<T> *node, T value, int pointer) {
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

template <class T>
void BPlusTree<T>::InsertInNonleaf(Node<T> *node, int pointer_left, T value, int pointer_right) {
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

template <class T>
void BPlusTree<T>::InsertInParent(Node<T> *node_left, T value, Node<T> *node_right) {
	if(node_left->num == root_) {
		Node<T> *node = GetAnAvailableNode();
		node->state = NONLEAF;
		node->value_num = 1;
		node->pointer[0] = node_left->num;
		node->value[0] = value;
		node->pointer[1] = node_right->num;
		root_ = node->num;
		return;
	}
	Node<T> *parent_node = GetNode(queue_.back());
	queue_.pop_back();
	if(parent_node->value_num < MAX_VALUE_NUM)
		InsertInNonleaf(parent_node, node_left->num, value, node_right->num);
	else {
		Node<T> *node = GetAnAvailableNode();
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

template <class T>
void BPlusTree<T>::Delete(T value) {
	Node<T> *node = FindLeafNode(value);
	if(!node) return;
	DeleteEntry(node, value);
}

template <class T>
void BPlusTree<T>::DeleteEntry(Node<T> *node, T value) {
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
			Node<T> *sibling_node;
			T seperator;
			bool is_predecessor = GetSiblingAndSeperator(GetNode(queue_.back()), node->num, sibling_node, seperator);
			if(sibling_node->value_num + node->value_num <= MAX_VALUE_NUM) {
				if(!is_predecessor) {
					Node<T> *temp;
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
				Node<T> *parent = GetNode(queue_.back());
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
			Node<T> *sibling_node;
			T seperator;
			bool is_predecessor = GetSiblingAndSeperator(GetNode(queue_.back()), node->num, sibling_node, seperator);
			if(sibling_node->value_num + node->value_num < MAX_VALUE_NUM) {
				if(!is_predecessor) {
					Node<T> *temp;
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
				Node<T> *parent = GetNode(queue_.back());
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

template <class T>
void BPlusTree<T>::DeleteInNode(Node<T> *node, T value) {
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

template <class T>
bool BPlusTree<T>::GetSiblingAndSeperator(Node<T> *node, int pointer, Node<T> *&sibling_node, T &seperator) {
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

template <class T>
void BPlusTree<T>::ReplaceSeperator(Node<T> *node, T a, T b) {
	for(int i = 0; i < node->value_num; i++)
		if(node->value[i] == a) {
			node->value[i] = b;
			return;
		}
}
