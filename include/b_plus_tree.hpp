#pragma once

#include <fstream>
#include <vector>

#include "buffer_manager.hpp"

namespace bpt {

#define LAST_POINTER (pointer_num_ - 1)
#define MAX_VALUE_NUM (pointer_num_ - 1)

template <class V, class P>
class BPlusTree {
	enum NodeState : unsigned char {EMPTY, NONLEAF, LEAF};
	struct Node {
		int *num;
		NodeState *state;
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

	std::string name_;
	int pointer_num_;
	int node_num_;
	int empty_node_num_;
	Node swapper_;
	std::vector<int> queue_;
	int root_;
	bm::BufferManager buffer_manager_;
	void AddOneBlock();
	Node GetNode(int node_num);
	Node GetAnAvailableNode();
	void Pin(Node &node);
	void Unpin(Node &node);
	Node FindLeafNode(V value);
	void InsertInLeaf(Node node, V value, P pointer);
	void InsertInNonleaf(Node node, int pointer_left_num, V value, int pointer_right_num);
	void InsertInParent(int node_left_int, V value, int node_right_num);
	void DeleteEntry(Node node, V value);
	void DeleteInNode(Node node, V value);
	bool GetSiblingAndSeperator(int node_num, int pointer_num, int &sibling_node_num, V &seperator);
	void ReplaceSeperator(int node_num, V value_old, V value_new);
public:
	BPlusTree(std::string name);
	~BPlusTree();
	P Find(V value);
	std::vector<P> FindFrom(V value, bool contained);
	std::vector<P> FindTo(V value, bool contained);
	std::vector<P> FindFromTo(V value_from, bool contained_from, V value_to, bool contained_to);
	void Insert(V value, P pointer);
	void Delete(V value);
};

/*********** **********/

template <class V>
bool operator==(const V &v0, const V &v1) {
	return !(v0 < v1) && !(v1 < v0);
}

template <class V, class P>
BPlusTree<V, P>::BPlusTree(std::string name) {
	name_ = name;
	pointer_num_ = (BLOCK_SIZE - sizeof(int) - sizeof(NodeState) - sizeof(int) - sizeof(P)) / (sizeof(P) + sizeof(V)) + 1;
	swapper_.value_num = new int;
	swapper_.pointer = new P[pointer_num_ + 1];
	swapper_.value = new V[pointer_num_];

	std::ifstream ifs((name_ + ".idxinfo").c_str());
	if(ifs.is_open()) {
		ifs >> root_ >> node_num_ >> empty_node_num_;
	} else {
		root_ = -1;
		node_num_ = 0;
		empty_node_num_ = 0;
		std::ofstream ofs((name_ + ".idx").c_str());
		ofs.close();
	}
	ifs.close();

	buffer_manager_.Init();
}

template <class V, class P>
BPlusTree<V, P>::~BPlusTree() {
	std::ofstream ofs((name_ + ".idxinfo").c_str());
	ofs << root_ << " " << node_num_ << " " << empty_node_num_;
	ofs.close();
	buffer_manager_.Terminate();
}

template <class V, class P>
void BPlusTree<V, P>::AddOneBlock() {
	static char empty_block[BLOCK_SIZE] = {0};
	std::ofstream ofs((name_ + ".idx").c_str(), std::ofstream::app | std::ofstream::binary);
	ofs.write(empty_block, BLOCK_SIZE);
	ofs.close();
}

template <class V, class P>
typename BPlusTree<V, P>::Node BPlusTree<V, P>::GetNode(int node_num) {
	if(node_num >= node_num_ || node_num < 0) {
		std::cerr << "Node " << node_num << " doesn't exist!" << std::endl;
		return Node();
	}
	char *block = buffer_manager_.GetFileBlock(name_ + ".idx", node_num);
	Node node;
	node.num = (int*)block;
	node.state = (BPlusTree<V, P>::NodeState*)block + sizeof(int);
	node.value_num = (int*)(block + sizeof(int) + sizeof(char));
	node.pointer = (P*)(block + sizeof(int) + sizeof(char) + sizeof(int));
	node.value = (V*)(block + sizeof(int) + sizeof(char) + sizeof(int) + sizeof(P) * pointer_num_);
	return node;
}

template <class V, class P>
typename BPlusTree<V, P>::Node BPlusTree<V, P>::GetAnAvailableNode() {
	if(empty_node_num_)
		for(int i = 0; i < node_num_; i++) {
			Node node = GetNode(i);
			if(*node.state == EMPTY) {
				empty_node_num_--;
				return node;
			}
		}
	AddOneBlock();
	node_num_++;
	Node node = GetNode(node_num_ - 1);
	*node.num = node_num_ - 1;
	*node.state = EMPTY;
	*node.value_num = 0;
	return node;
}

template <class V, class P>
void BPlusTree<V, P>::Pin(Node &node) {
	buffer_manager_.Pin((char*)node.num);
}

template <class V, class P>
void BPlusTree<V, P>::Unpin(Node &node) {
	buffer_manager_.Unpin((char*)node.num);
}

template <class V, class P>
typename BPlusTree<V, P>::Node BPlusTree<V, P>::FindLeafNode(V value) {
	if(root_ == -1) return Node();
	Node node = GetNode(root_);
	queue_.clear();
	while(*node.state != LEAF) {
		queue_.push_back(*node.num);
		int i;
		for(i = 0; i < *node.value_num; i++)
			if(value < node.value[i] || value == node.value[i]) break;
		if(i == *node.value_num)
			node = GetNode(node.pointer[i].num);
		else if(value == node.value[i])
			node = GetNode(node.pointer[i + 1].num);
		else
			node = GetNode(node.pointer[i].num);
	}
	return node;
}

template <class V, class P>
P BPlusTree<V, P>::Find(V value) {
	Node node = FindLeafNode(value);
	if(!node.num) return P();
	for(int i = 0; i < *node.value_num; i++)
		if(node.value[i] == value)
			return node.pointer[i];
	return P();
}

template <class V, class P>
std::vector<P> BPlusTree<V, P>::FindFrom(V value, bool contained) {
	std::vector<P> pointer;
	Node node = FindLeafNode(value);
	if(!node.num) return std::move(pointer);

	for(int i = 0; i < *node.value_num; i++)
		if(value < node.value[i] || (contained && node.value[i] == value))
			pointer.push_back(node.pointer[i]);
	while(node.pointer[LAST_POINTER].num != -1) {
		node = GetNode(node.pointer[LAST_POINTER].num);
		for(int i = 0; i < *node.value_num; i++)
			pointer.push_back(node.pointer[i]);
	}
	return std::move(pointer);
}

template <class V, class P>
std::vector<P> BPlusTree<V, P>::FindTo(V value, bool contained) {
	std::vector<P> pointer;
	Node node = FindLeafNode(value);
	if(!node.num) return std::move(pointer);

	std::vector<P> pointer_temp;
	for(int i = 0; i < *node.value_num; i++)
		if(node.value[i] < value || (contained && node.value[i] == value))
			pointer_temp.push_back(node.pointer[i]);
	int node_num_to = *node.num;
	if(node_num_to == 0) return std::move(pointer_temp);
	int node_num = 0;
	while(node_num != -1 && node_num != node_num_to) {
		Node node = GetNode(node_num);
		for(int i = 0; i < *node.value_num; i++)
			pointer.push_back(node.pointer[i]);
		node_num = node.pointer[LAST_POINTER].num;
	}
	pointer.insert(pointer.end(), pointer_temp.begin(), pointer_temp.end());
	return std::move(pointer);
}

template <class V, class P>
std::vector<P> BPlusTree<V, P>::FindFromTo(V value_from, bool contained_from, V value_to, bool contained_to) {
	std::vector<P> pointer;
	if(value_to < value_from) return std::move(pointer);
	Node node_from = FindLeafNode(value_from);
	Pin(node_from);
	Node node_to = FindLeafNode(value_to);
	Unpin(node_from);
	if(!node_from.num || !node_to.num) return std::move(pointer);

	if(*node_from.num == *node_to.num) {
		for(int i = 0; i < *node_from.value_num; i++)
			if((value_from < node_from.value[i] || (contained_from && node_from.value[i] == value_from)) && (node_from.value[i] < value_to || (contained_to && node_from.value[i] == value_to)))
				pointer.push_back(node_from.pointer[i]);
		return std::move(pointer);
	}
	for(int i = 0; i < *node_from.value_num; i++)
		if(value_from < node_from.value[i] || (contained_from && node_from.value[i] == value_from))
			pointer.push_back(node_from.pointer[i]);
	std::vector<P> pointer_temp;
	for(int i = 0; i < *node_to.value_num; i++)
		if(node_to.value[i] < value_to || (contained_to && node_to.value[i] == value_to))
			pointer_temp.push_back(node_to.pointer[i]);
	int node_num_to = *node_to.num;
	int node_num = node_from.pointer[LAST_POINTER].num;
	while(node_num != node_num_to) {
		Node node = GetNode(node_num);
		for(int i = 0; i < *node.value_num; i++)
			pointer.push_back(node.pointer[i]);
		node_num = node.pointer[LAST_POINTER].num;
	}
	for(unsigned int i = 0; i < pointer_temp.size(); i++)
		pointer.push_back(pointer_temp[i]);
	return std::move(pointer);
}

template <class V, class P>
void BPlusTree<V, P>::Insert(V value, P pointer) {
	if(root_ == -1) {
		Node node = GetAnAvailableNode();
		*node.state = LEAF;
		*node.value_num = 1;
		node.value[0] = value;
		node.pointer[0] = pointer;
		node.pointer[LAST_POINTER].num = -1;
		root_ = *node.num;
		return;
	}
	Node leaf_node = FindLeafNode(value);
	if(*leaf_node.value_num < MAX_VALUE_NUM)
		InsertInLeaf(leaf_node, value, pointer);
	else {
		Pin(leaf_node);
		Node node = GetAnAvailableNode();
		Unpin(leaf_node);
		*node.state = LEAF;
		for(int i = 0; i < MAX_VALUE_NUM; i++) swapper_.value[i] = leaf_node.value[i];
		for(int i = 0; i < MAX_VALUE_NUM; i++) swapper_.pointer[i] = leaf_node.pointer[i];
		*swapper_.value_num = MAX_VALUE_NUM;
		InsertInLeaf(swapper_, value, pointer);
		node.pointer[LAST_POINTER] = leaf_node.pointer[LAST_POINTER];
		leaf_node.pointer[LAST_POINTER].num = *node.num;
		int mid = (pointer_num_ + 1) / 2;
		for(int i = 0; i < mid; i++) leaf_node.value[i] = swapper_.value[i];
		for(int i = 0; i < mid; i++) leaf_node.pointer[i] = swapper_.pointer[i];
		for(int i = mid; i < pointer_num_; i++) node.value[i - mid] = swapper_.value[i];
		for(int i = mid; i < pointer_num_; i++) node.pointer[i - mid] = swapper_.pointer[i];
		*leaf_node.value_num = mid;
		*node.value_num = pointer_num_ - mid;
		InsertInParent(*leaf_node.num, node.value[0], *node.num);
	}
}

template <class V, class P>
void BPlusTree<V, P>::InsertInLeaf(Node node, V value, P pointer) {
	if(value < node.value[0]) {
		for(int i = *node.value_num - 1; i >= 0; i--) {
			node.value[i + 1] = node.value[i];
			node.pointer[i + 1] = node.pointer[i];
		}
		node.value[0] = value;
		node.pointer[0] = pointer;
		(*node.value_num)++;
		return;
	}
	for(int i = *node.value_num - 1; i >= 0; i--)
		if(node.value[i] < value) {
			for(int j = *node.value_num - 1; j >= i + 1; j--) {
				node.value[j + 1] = node.value[j];
				node.pointer[j + 1] = node.pointer[j];
			}
			node.value[i + 1] = value;
			node.pointer[i + 1] = pointer;
			(*node.value_num)++;
			return;
		}
}

template <class V, class P>
void BPlusTree<V, P>::InsertInNonleaf(Node node, int pointer_left_num, V value, int pointer_right_num) {
	for(int i = 0; i <= *node.value_num; i++)
		if(node.pointer[i].num == pointer_left_num) {
			(*node.value_num)++;
			for(int j = *node.value_num; j > i + 1; j--) {
				node.pointer[j] = node.pointer[j - 1];
				node.value[j - 1] = node.value[j - 2];
			}
			node.pointer[i + 1].num = pointer_right_num;
			node.value[i] = value;
			return;
		}
}

template <class V, class P>
void BPlusTree<V, P>::InsertInParent(int node_left_num, V value, int node_right_num) {
	if(node_left_num == root_) {
		Node node = GetAnAvailableNode();
		*node.state = NONLEAF;
		*node.value_num = 1;
		node.pointer[0].num = node_left_num;
		node.value[0] = value;
		node.pointer[1].num = node_right_num;
		root_ = *node.num;
		return;
	}
	Node parent_node = GetNode(queue_.back());
	queue_.pop_back();
	if(*parent_node.value_num < MAX_VALUE_NUM)
		InsertInNonleaf(parent_node, node_left_num, value, node_right_num);
	else {
		Pin(parent_node);
		Node node = GetAnAvailableNode();
		Unpin(parent_node);
		*node.state = NONLEAF;
		for(int i = 0; i < MAX_VALUE_NUM; i++) swapper_.value[i] = parent_node.value[i];
		for(int i = 0; i < pointer_num_; i++) swapper_.pointer[i] = parent_node.pointer[i];
		*swapper_.value_num = MAX_VALUE_NUM;
		InsertInNonleaf(swapper_, node_left_num, value, node_right_num);
		int mid = pointer_num_ / 2;
		for(int i = 0; i < mid; i++) parent_node.value[i] = swapper_.value[i];
		for(int i = 0; i < mid + 1; i++) parent_node.pointer[i] = swapper_.pointer[i];
		for(int i = mid + 1; i < pointer_num_; i++) node.value[i - mid - 1] = swapper_.value[i];
		for(int i = mid + 1; i < pointer_num_ + 1; i++) node.pointer[i - mid - 1] = swapper_.pointer[i];
		*parent_node.value_num = mid;
		*node.value_num = pointer_num_ - mid - 1;
		InsertInParent(*parent_node.num, swapper_.value[mid], *node.num);
	}
}

template <class V, class P>
void BPlusTree<V, P>::Delete(V value) {
	Node node = FindLeafNode(value);
	if(!node.num) {
		std::cerr << "The tree is empty. Nothing to delete." << std::endl;
		return;
	}
	DeleteEntry(node, value);
}

template <class V, class P>
void BPlusTree<V, P>::DeleteEntry(Node node, V value) {
	DeleteInNode(node, value);
	if(*node.num == root_) {
		if(*node.value_num == 0) {
			if(*node.state == LEAF)
				root_ = -1;
			else
				root_ = node.pointer[0].num;
			*node.state = EMPTY;
			empty_node_num_++;
		}
		return;
	}
	if(*node.state == LEAF) {
		if(*node.value_num < pointer_num_ / 2) {
			int sibling_node_num;
			V seperator;
			Pin(node);
			bool is_predecessor = GetSiblingAndSeperator(queue_.back(), *node.num, sibling_node_num, seperator);
			Node sibling_node = GetNode(sibling_node_num);
			Unpin(node);
			if(*sibling_node.value_num + *node.value_num <= MAX_VALUE_NUM) {
				if(!is_predecessor) {
					Node temp;
					temp = node;
					node = sibling_node;
					sibling_node = temp;
				}
				for(int i = 0; i < *node.value_num; i++) {
					sibling_node.pointer[*sibling_node.value_num + i] = node.pointer[i];
					sibling_node.value[*sibling_node.value_num + i] = node.value[i];
				}
				*sibling_node.value_num += *node.value_num;
				sibling_node.pointer[LAST_POINTER] = node.pointer[LAST_POINTER];
				*node.state = EMPTY;
				empty_node_num_++;
				Node parent_node = GetNode(queue_.back());
				queue_.pop_back();
				DeleteEntry(parent_node, seperator);
				return;
			} else {
				if(is_predecessor) {
					for(int i = *node.value_num; i > 0; i--) {
						node.pointer[i] = node.pointer[i - 1];
						node.value[i] = node.value[i - 1];
					}
					node.pointer[0] = sibling_node.pointer[*sibling_node.value_num - 1];
					node.value[0] = sibling_node.value[*sibling_node.value_num - 1];
					(*node.value_num)++;
					(*sibling_node.value_num)--;
					ReplaceSeperator(queue_.back(), seperator, node.value[0]);
				} else {
					node.pointer[*node.value_num] = sibling_node.pointer[0];
					node.value[*node.value_num] = sibling_node.value[0];
					(*node.value_num)++;
					for(int i = 0; i < *sibling_node.value_num - 1; i++) {
						sibling_node.pointer[i] = sibling_node.pointer[i + 1];
						sibling_node.value[i] = sibling_node.value[i + 1];
					}
					(*sibling_node.value_num)--;
					ReplaceSeperator(queue_.back(), seperator, sibling_node.value[0]);
				}
			}
		}
	} else if(*node.state == NONLEAF) {
		if(*node.value_num < MAX_VALUE_NUM / 2) {
			int sibling_node_num;
			V seperator;
			Pin(node);
			bool is_predecessor = GetSiblingAndSeperator(queue_.back(), *node.num, sibling_node_num, seperator);
			Node sibling_node = GetNode(sibling_node_num);
			Unpin(node);
			if(*sibling_node.value_num + *node.value_num < MAX_VALUE_NUM) {
				if(!is_predecessor) {
					Node temp;
					temp = node;
					node = sibling_node;
					sibling_node = temp;
				}
				sibling_node.value[*sibling_node.value_num] = seperator;
				(*sibling_node.value_num)++;
				for(int i = 0; i < *node.value_num; i++) {
					sibling_node.pointer[*sibling_node.value_num + i] = node.pointer[i];
					sibling_node.value[*sibling_node.value_num + i] = node.value[i];
				}
				*sibling_node.value_num += *node.value_num;
				sibling_node.pointer[*sibling_node.value_num] = node.pointer[*node.value_num];
				*node.state = EMPTY;
				empty_node_num_++;
				Node parent_node = GetNode(queue_.back());
				queue_.pop_back();
				DeleteEntry(parent_node, seperator);
				return;
			} else {
				if(is_predecessor) {
					node.pointer[*node.value_num + 1] = node.pointer[*node.value_num];
					for(int i = *node.value_num; i > 0; i--) {
						node.pointer[i] = node.pointer[i - 1];
						node.value[i] = node.value[i - 1];
					}
					node.pointer[0] = sibling_node.pointer[*sibling_node.value_num];
					node.value[0] = seperator;
					(*node.value_num)++;
					(*sibling_node.value_num)--;
					ReplaceSeperator(queue_.back(), seperator, sibling_node.value[*sibling_node.value_num]);
				} else {
					V seperator_new = sibling_node.value[0];
					node.pointer[*node.value_num + 1] = sibling_node.pointer[0];
					node.value[*node.value_num] = seperator;
					(*node.value_num)++;
					for(int i = 0; i < *sibling_node.value_num - 1; i++) {
						sibling_node.pointer[i] = sibling_node.pointer[i + 1];
						sibling_node.value[i] = sibling_node.value[i + 1];
					}
					(*sibling_node.value_num)--;
					sibling_node.pointer[*sibling_node.value_num] = sibling_node.pointer[*sibling_node.value_num + 1];
					ReplaceSeperator(queue_.back(), seperator, seperator_new);
				}
			}
		}
	}
}

template <class V, class P>
void BPlusTree<V, P>::DeleteInNode(Node node, V value) {
	for(int i = 0; i < *node.value_num; i++)
		if(node.value[i] == value) {
			for(int j = i; j < *node.value_num - 1; j++) {
				if(*node.state == LEAF)
					node.pointer[j] = node.pointer[j + 1];
				else
					node.pointer[j + 1] = node.pointer[j + 2];
				node.value[j] = node.value[j + 1];
			}
			(*node.value_num)--;
			return;
		}
}

template <class V, class P>
bool BPlusTree<V, P>::GetSiblingAndSeperator(int node_num, int pointer_num, int &sibling_node_num, V &seperator) {
	Node node = GetNode(node_num);
	int i;
	for(i = 0; i <= *node.value_num; i++)
		if(node.pointer[i].num == pointer_num) break;
	if(i == *node.value_num) {
		sibling_node_num = node.pointer[i - 1].num;
		seperator = node.value[i - 1];
		return true;
	} else {
		sibling_node_num = node.pointer[i + 1].num;
		seperator = node.value[i];
		return false;
	}
}

template <class V, class P>
void BPlusTree<V, P>::ReplaceSeperator(int node_num, V value_old, V value_new) {
	Node node = GetNode(node_num);
	for(int i = 0; i < *node.value_num; i++)
		if(node.value[i] == value_old) {
			node.value[i] = value_new;
			return;
		}
}

#undef LAST_POINTER
#undef MAX_VALUE_NUM

}
