#ifndef NODE_HPP
#define NODE_HPP

#include "utils.hpp"
#include <iostream>

namespace ft {

	enum NodeType {
		nilNodeType, // 0
		blackNodeType, // 1
		redNodeType // 2
	};

	template<class T1, class T2>
	struct Node {
		typedef ft::pair<const T1, T2> value_type;
		int nodeType;
		Node* parent;
		Node* left;
		Node* right;
		value_type* data;

		Node(T1 key, T2 value, Node* nil = NULL, int NodeType = blackNodeType)
				:nodeType(NodeType), parent(nil), left(nil), right(nil), data(new value_type(key, value)) { }

		Node(const Node& node)
		{
			*this = node;
		}

		Node& operator=(const Node& node)
		{
			if (this==&node)
				return *this;
			nodeType = node.nodeType;
			parent = node.parent;
			left = node.left;
			right = node.right;
			data = new value_type(node.data->first, node.data->second);
			return *this;
		}

		~Node()
		{
			if (data) {
				delete (data);
				data = NULL;
			}
		}
	};

}
#endif
