//
// Created by Shandy Mephesto on 11/28/21.
//

#ifndef RBTREE_HPP
#define RBTREE_HPP
#include "Node.hpp"

// Source https://github.com/Bibeknam/algorithmtutorprograms/blob/master/data-structures/red-black-trees/RedBlackTree.cpp
namespace ft {

	template<class _T1, class _T2>
	class RBTree {
	private:
		typedef Node<_T1, _T2>* NodePointer;
		NodePointer root;

		// initializes the nodes with appropirate values
		// all the pointers are set to point to the null pointer
		void initializeNULLNode(NodePointer node, NodePointer parent)
		{
			node->pair = new pair<_T1, _T2>(); // TODO:: maybe it is incorrect
			node->parent = parent;
			node->left = NULL;
			node->right = NULL;
			node->isRed = false;
		}

		void preOrderHelper(NodePointer node)
		{
			if (node!=NULL) {
				preOrderHelper(node->left);
				preOrderHelper(node->right);
			}
		}

		void inOrderHelper(NodePointer node)
		{
			if (node!=NULL) {
				inOrderHelper(node->left);
				inOrderHelper(node->right);
			}
		}

		void postOrderHelper(NodePointer node)
		{
			if (node!=NULL) {
				postOrderHelper(node->left);
				postOrderHelper(node->right);
			}
		}

		NodePointer searchTreeHelper(NodePointer node, _T1 key)
		{
			if (node==NULL || key==node->data->first) { return node; }
			if (key<node->data->first) { return searchTreeHelper(node->left, key); }
			return searchTreeHelper(node->right, key);
		}

		// fix the rb tree modified by the delete operation
		void fixDelete(NodePointer x)
		{
			NodePointer s;
			while (x!=root && x->isRed==false) {
				if (x==x->parent->left) {
					s = x->parent->right;
					if (s->isRed==true) {
						// case 3.1
						s->isRed = false;
						x->parent->isRed = true;
						leftRotate(x->parent);
						s = x->parent->right;
					}

					if (s->left->isRed==false && s->right->isRed==false) {
						// case 3.2
						s->isRed = true;
						x = x->parent;
					}
					else {
						if (s->right->isRed==false) {
							// case 3.3
							s->left->isRed = false;
							s->isRed = true;
							rightRotate(s);
							s = x->parent->right;
						}

						// case 3.4
						s->isRed = x->parent->isRed;
						x->parent->isRed = false;
						s->right->isRed = false;
						leftRotate(x->parent);
						x = root;
					}
				}
				else {
					s = x->parent->left;
					if (s->isRed==true) {
						// case 3.1
						s->isRed = false;
						x->parent->isRed = true;
						rightRotate(x->parent);
						s = x->parent->left;
					}

					if (s->right->isRed==false && s->right->isRed==false) {
						// case 3.2
						s->isRed = true;
						x = x->parent;
					}
					else {
						if (s->left->isRed==false) {
							// case 3.3
							s->right->isRed = false;
							s->isRed = true;
							leftRotate(s);
							s = x->parent->left;
						}

						// case 3.4
						s->isRed = x->parent->isRed;
						x->parent->isRed = false;
						s->left->isRed = false;
						rightRotate(x->parent);
						x = root;
					}
				}
			}
			x->isRed = false;
		}

		void rbTransplant(NodePointer u, NodePointer v)
		{
			if (u->parent==NULL) {
				root = v;
			}
			else if (u==u->parent->left) {
				u->parent->left = v;
			}
			else {
				u->parent->right = v;
			}
			v->parent = u->parent;
		}

		void deleteNodeHelper(NodePointer node, _T1 key)
		{
			// find the node containing key
			NodePointer z = NULL;
			NodePointer x, y;
			while (node!=NULL) {
				if (node->data->first==key) {
					z = node;
				}
				if (node->data->first<=key) {
					node = node->right;
				}
				else {
					node = node->left;
				}
			}

			if (z==NULL) {
//				cout << "Couldn't find key in the tree" << endl;
				return;
			}

			y = z;
			int y_original_isRed = y->isRed;
			if (z->left==NULL) {
				x = z->right;
				rbTransplant(z, z->right);
			}
			else if (z->right==NULL) {
				x = z->left;
				rbTransplant(z, z->left);
			}
			else {
				y = minimum(z->right);
				y_original_isRed = y->isRed;
				x = y->right;
				if (y->parent==z) {
					x->parent = y;
				}
				else {
					rbTransplant(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}

				rbTransplant(z, y);
				y->left = z->left;
				y->left->parent = y;
				y->isRed = z->isRed;
			}
			delete z;
			if (y_original_isRed==false) {
				fixDelete(x);
			}
		}

		// fix the red-black tree
		void fixInsert(NodePointer k)
		{
			NodePointer u;
			while (k->parent->isRed==true) {
				if (k->parent==k->parent->parent->right) {
					u = k->parent->parent->left; // uncle
					if (u->isRed==true) {
						// case 3.1
						u->isRed = false;
						k->parent->isRed = false;
						k->parent->parent->isRed = true;
						k = k->parent->parent;
					}
					else {
						if (k==k->parent->left) {
							// case 3.2.2
							k = k->parent;
							rightRotate(k);
						}
						// case 3.2.1
						k->parent->isRed = false;
						k->parent->parent->isRed = true;
						leftRotate(k->parent->parent);
					}
				}
				else {
					u = k->parent->parent->right; // uncle

					if (u->isRed==true) {
						// mirror case 3.1
						u->isRed = false;
						k->parent->isRed = false;
						k->parent->parent->isRed = true;
						k = k->parent->parent;
					}
					else {
						if (k==k->parent->right) {
							// mirror case 3.2.2
							k = k->parent;
							leftRotate(k);
						}
						// mirror case 3.2.1
						k->parent->isRed = false;
						k->parent->parent->isRed = true;
						rightRotate(k->parent->parent);
					}
				}
				if (k==root) {
					break;
				}
			}
			root->isRed = false;
		}

//		void printHelper(NodePointer root, string indent, bool last)
//		{
//			// print the tree structure on the screen
//			if (root!=NULL) {
////				cout << indent;
//				if (last) {
//					cout << "R----";
//					indent += "     ";
//				}
//				else {
//					cout << "L----";
//					indent += "|    ";
//				}
//
//				string sColor = root->isRed ? "RED" : "BLACK";
////				cout << root->data << "(" << sColor << ")" << endl;
//				printHelper(root->left, indent, false);
//				printHelper(root->right, indent, true);
//			}
//			// cout<<root->left->data<<endl;
//		}

	public:
		RBTree()
		{
//			NULL = new Node<_T1, _T2>;
//			NULL->isRed = false;
//			NULL->left = NULL;
//			NULL->right = NULL;
			root = NULL;
		}

		// Pre-Order traversal
		// Node->Left Subtree->Right Subtree
		void preorder()
		{
			preOrderHelper(this->root);
		}

		// In-Order traversal
		// Left Subtree -> Node -> Right Subtree
		void inorder()
		{
			inOrderHelper(this->root);
		}

		// Post-Order traversal
		// Left Subtree -> Right Subtree -> Node
		void postorder()
		{
			postOrderHelper(this->root);
		}

		// search the tree for the key k
		// and return the corresponding node
		NodePointer searchTree(_T1 k)
		{
			return searchTreeHelper(this->root, k);
		}

		// find the node with the minimum key
		NodePointer minimum(NodePointer node)
		{
			while (node->left!=NULL) {
				node = node->left;
			}
			return node;
		}

		// find the node with the maximum key
		NodePointer maximum(NodePointer node)
		{
			while (node->right!=NULL) {
				node = node->right;
			}
			return node;
		}

		// TODO:: what is it? Looks like it is ++ operation
		// find the successor of a given node
		NodePointer successor(NodePointer x)
		{
			// if the right subtree is not null,
			// the successor is the leftmost node in the
			// right subtree
			if (x->right!=NULL) {
				return minimum(x->right);
			}

			// else it is the lowest ancestor of x whose
			// left child is also an ancestor of x.
			NodePointer y = x->parent;
			while (y!=NULL && x==y->right) {
				x = y;
				y = y->parent;
			}
			return y;
		}

		// TODO:: looks like it is -- operation
		// find the predecessor of a given node
		NodePointer predecessor(NodePointer x)
		{
			// if the left subtree is not null,
			// the predecessor is the rightmost node in the
			// left subtree
			if (x->left!=NULL) {
				return maximum(x->left);
			}

			NodePointer y = x->parent;
			while (y!=NULL && x==y->left) {
				x = y;
				y = y->parent;
			}

			return y;
		}

		// rotate left at node x
		void leftRotate(NodePointer x)
		{
			NodePointer y = x->right;
			x->right = y->left;
			if (y->left!=NULL) {
				y->left->parent = x;
			}
			y->parent = x->parent;
			if (x->parent==NULL) {
				this->root = y;
			}
			else if (x==x->parent->left) {
				x->parent->left = y;
			}
			else {
				x->parent->right = y;
			}
			y->left = x;
			x->parent = y;
		}

		// rotate right at node x
		void rightRotate(NodePointer x)
		{
			NodePointer y = x->left;
			x->left = y->right;
			if (y->right!=NULL) {
				y->right->parent = x;
			}
			y->parent = x->parent;
			if (x->parent==NULL) {
				this->root = y;
			}
			else if (x==x->parent->right) {
				x->parent->right = y;
			}
			else {
				x->parent->left = y;
			}
			y->right = x;
			x->parent = y;
		}

		// TODO:: replace key to pair
		// insert the key to the tree in its appropriate position
		// and fix the tree
		template<class U, class V>
		NodePointer insert(U key, V value)
		{
			// Ordinary Binary Search Insertion
			NodePointer node = new Node<const U, V>();
			node->parent = NULL;
			node->data = pair<U, V>(key, value);
			node->left = NULL;
			node->right = NULL;
			node->isRed = true; // new node must be red

			NodePointer y = NULL;
			NodePointer x = this->root;

			while (x!=NULL) {
				y = x;
				if (node->data<x->data) {
					x = x->left;
				}
				else {
					x = x->right;
				}
			}

			// y is parent of x
			node->parent = y;
			if (y==NULL) {
				root = node;
			}
			else if (node->data<y->data) {
				y->left = node;
			}
			else {
				y->right = node;
			}

			// if new node is a root node, simply return
			if (node->parent==NULL) {
				node->isRed = false;
				return NULL;
			}

			// if the grandparent is null, simply return
			if (node->parent->parent==NULL) {
				return NULL;
			}

			// Fix the tree
			fixInsert(node);
			return node;
		}

		NodePointer getRoot()
		{
			return this->root;
		}

		// delete the node from the tree
		void deleteNode(_T2 data)
		{
			deleteNodeHelper(this->root, data);
		}

		NodePointer search(_T1 key)
		{
			NodePointer node = root;
			return searchTreeHelper(root, key);
		}

		// print the tree structure on the screen
//		void prettyPrint()
//		{
//			if (root) {
//				printHelper(this->root, "", true);
//			}
//		}

	};
}

#endif