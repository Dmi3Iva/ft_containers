#ifndef NODE_HPP
#define NODE_HPP

template<class _T1, class _T2>
struct Node {
	bool isRed;
	Node* parent;
	Node* left;
	Node* right;
	ft::pair<const _T1, _T2> data;
};

#endif
