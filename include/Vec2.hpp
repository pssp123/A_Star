//
// Created by pierre on 18-5-2.
//
#ifndef A_START_VEC2I_HPP
#define A_START_VEC2I_HPP

#include <iostream>

#define BLACK 1
#define RED 0

using namespace std;

class Node {
public:

	Node(){}

	Node(int _x, int _y){
		x_ = _x;
		y_ = _y;
	}

	Node(int _x, int _y, double _f, int _g, double _h){
		x_ = _x;
		y_ = _y;
		f_ = _f;
		g_ = _g;
		h_ = _h;
	}

	Node& operator=(const Node& n){
		this->x_ = n.x_;
		this->y_ = n.y_;
		this->f_ = n.f_;
		this->g_ = n.g_;
		this->h_ = n.h_;
		return *this;
	}

	Node *grandparent() {
		if (parent == NULL) {
			return NULL;
		}
		return parent->parent;
	}

	Node *uncle() {
		if (grandparent() == NULL) {
			return NULL;
		}
		if (parent == grandparent()->rightTree)
			return grandparent()->leftTree;
		else
			return grandparent()->rightTree;
	}

	Node *sibling() {
		if (parent->leftTree == this)
			return parent->rightTree;
		else
			return parent->leftTree;
	}

	bool operator==(const Node& r) const{
		return this->x_ == r.x_ && this->y_ == r.y_;
	}

	Node operator+(const Node& r) const{
		return Node{this->x_ + r.x_, this->y_ + r.y_};
	}

	bool operator<(const Node& r) const{
		return this->f_ > r.f_;
	}

	int x_{0}, y_{0};
	double f_{0}, h_{0};
	int g_{0};
	bool color{RED};
	Node *leftTree{NULL}, *rightTree{NULL}, *parent{NULL};
};

class RBT{
private:
	void rotate_right(Node *p) {
		Node *gp = p->grandparent();
		Node *fa = p->parent;
		Node *y = p->rightTree;

		fa->leftTree = y;

		if (y != NIL_)
			y->parent = fa;
		p->rightTree = fa;
		fa->parent = p;

		if (root_ == fa)
			root_ = p;
		p->parent = gp;

		if (gp != NULL) {
			if (gp->leftTree == fa)
				gp->leftTree = p;
			else
				gp->rightTree = p;
		}
	}

	void rotate_left(Node *p) {
		if (p->parent == NULL) {
			root_ = p;
			return;
		}
		Node *gp = p->grandparent();
		Node *fa = p->parent;
		Node *y = p->leftTree;

		fa->rightTree = y;

		if (y != NIL_)
			y->parent = fa;
		p->leftTree = fa;
		fa->parent = p;

		if (root_ == fa)
			root_ = p;
		p->parent = gp;

		if (gp != NULL) {
			if (gp->leftTree == fa)
				gp->leftTree = p;
			else
				gp->rightTree = p;
		}
	}

	void inorder(Node *p) {
		if (p == NIL_)
			return;

		if (p->leftTree)
			inorder(p->leftTree);

		printf("(%d,%d),(%lf,%d,%lf)\n",p->x_,p->y_,p->f_,p->g_,p->h_);

		if (p->rightTree)
			inorder(p->rightTree);
	}

	string outputColor(bool color) {
		return color ? "BLACK" : "RED";
	}

	Node* getSmallestChild(Node *p) {
		if (p->leftTree == NIL_)
			return p;
		return getSmallestChild(p->leftTree);
	}

	void delete_one_child(Node *p) {
		Node *child = p->leftTree == NIL_ ? p->rightTree : p->leftTree;
		if (p->parent == NULL && p->leftTree == NIL_ && p->rightTree == NIL_) {
			p = NULL;
			root_ = p;
			return;
		}

		if (p->parent == NULL) {
			delete p;
			child->parent = NULL;
			root_ = child;
			root_->color = BLACK;
			return;
		}

		if (p->parent->leftTree == p) {
			p->parent->leftTree = child;
		} else {
			p->parent->rightTree = child;
		}
		child->parent = p->parent;

		if (p->color == BLACK) {
			if (child->color == RED) {
				child->color = BLACK;
			} else
				delete_case(child);
		}

		delete p;
	}

	void delete_case(Node *p) {
		if (p->parent == NULL) {
			p->color = BLACK;
			return;
		}
		if (p->sibling()->color == RED) {
			p->parent->color = RED;
			p->sibling()->color = BLACK;
			if (p == p->parent->leftTree)
				rotate_left(p->sibling());
			else
				rotate_right(p->sibling());
		}
		if (p->parent->color == BLACK && p->sibling()->color == BLACK
				&& p->sibling()->leftTree->color == BLACK && p->sibling()->rightTree->color == BLACK) {
			p->sibling()->color = RED;
			delete_case(p->parent);
		} else if (p->parent->color == RED && p->sibling()->color == BLACK
							 && p->sibling()->leftTree->color == BLACK && p->sibling()->rightTree->color == BLACK) {
			p->sibling()->color = RED;
			p->parent->color = BLACK;
		} else {
			if (p->sibling()->color == BLACK) {
				if (p == p->parent->leftTree && p->sibling()->leftTree->color == RED
						&& p->sibling()->rightTree->color == BLACK) {
					p->sibling()->color = RED;
					p->sibling()->leftTree->color = BLACK;
					rotate_right(p->sibling()->leftTree);
				} else if (p == p->parent->rightTree && p->sibling()->leftTree->color == BLACK
									 && p->sibling()->rightTree->color == RED) {
					p->sibling()->color = RED;
					p->sibling()->rightTree->color = BLACK;
					rotate_left(p->sibling()->rightTree);
				}
			}
			p->sibling()->color = p->parent->color;
			p->parent->color = BLACK;
			if (p == p->parent->leftTree) {
				p->sibling()->rightTree->color = BLACK;
				rotate_left(p->sibling());
			} else {
				p->sibling()->leftTree->color = BLACK;
				rotate_right(p->sibling());
			}
		}
	}

	void insert(Node *p, Node* insertData) {
		if (p->f_ > insertData->f_) {
			if (p->leftTree != NIL_)
				insert(p->leftTree, insertData);
			else {
				Node *tmp = new Node();
				*tmp = *insertData;
				tmp->leftTree = tmp->rightTree = NIL_;
				tmp->parent = p;
				p->leftTree = tmp;
				insert_case(tmp);
			}
		} else {
			if (p->rightTree != NIL_)
				insert(p->rightTree, insertData);
			else {
				Node *tmp = new Node();
				*tmp = *insertData;
				tmp->leftTree = tmp->rightTree = NIL_;
				tmp->parent = p;
				p->rightTree = tmp;
				insert_case(tmp);
			}
		}
	}

	void insert_case(Node *p) {
		if (p->parent == NULL) {
			root_ = p;
			p->color = BLACK;
			return;
		}
		if (p->parent->color == RED) {
			if (p->uncle()->color == RED) {
				p->parent->color = p->uncle()->color = BLACK;
				p->grandparent()->color = RED;
				insert_case(p->grandparent());
			} else {
				if (p->parent->rightTree == p && p->grandparent()->leftTree == p->parent) {
					rotate_left(p);
					rotate_right(p);
					p->color = BLACK;
					p->leftTree->color = p->rightTree->color = RED;
				} else if (p->parent->leftTree == p && p->grandparent()->rightTree == p->parent) {
					rotate_right(p);
					rotate_left(p);
					p->color = BLACK;
					p->leftTree->color = p->rightTree->color = RED;
				} else if (p->parent->leftTree == p && p->grandparent()->leftTree == p->parent) {
					p->parent->color = BLACK;
					p->grandparent()->color = RED;
					rotate_right(p->parent);
				} else if (p->parent->rightTree == p && p->grandparent()->rightTree == p->parent) {
					p->parent->color = BLACK;
					p->grandparent()->color = RED;
					rotate_left(p->parent);
				}
			}
		}
	}

	void DeleteTree(Node *p) {
		if (!p || p == NIL_) {
			return;
		}
		DeleteTree(p->leftTree);
		DeleteTree(p->rightTree);
		delete p;
	}

	bool isContain(Node* n, Node* p) {
		if (p == NIL_)
			return false;

		if (is_found_)
			return true;

		if (p->leftTree)
			isContain(n,p->leftTree);

		if(!is_found_)
			is_found_ = *p == *n;

		if (p->rightTree)
			isContain(n,p->rightTree);

		return is_found_;
	}

	Node* find(const Node& n, Node* p) {
		if (p == NIL_ || is_found_)
			return nullptr;

		if (p->leftTree)
			find(n, p->leftTree);

		if(!is_found_) {
			is_found_ = *p == n;
			if(is_found_)
				found_node_ = p;
		}

		if (p->rightTree)
			find(n, p->rightTree);

		return is_found_ ? found_node_ : false;
	}

	uint16_t size(Node* p) {
		if (p == NIL_)
			return 0;

		if (p->leftTree)
			size(p->leftTree);

		size_++;

		if (p->rightTree)
			size(p->rightTree);

		return size_;
	}
public:

	RBT() {
		NIL_ = new Node();
		NIL_->color = BLACK;
		root_ = NULL;
	}

	~RBT() {
		if (root_)
			DeleteTree(root_);
		delete NIL_;
	}

	uint16_t size(){
		size_ = 0;
		if (root_ == NULL)
			return 0;
		return size(root_);
	}

	bool isEmpty(){
			return root_ == NULL;
	}

	void inorder() {
		if (root_ == NULL)
			return;
		inorder(root_);
		cout << endl;
	}

	void insert(Node insetData) {
		if (root_ == NULL) {
			root_ = new Node();
			root_->color = BLACK;
			root_->leftTree = root_->rightTree = NIL_;
			root_->x_= insetData.x_;
			root_->y_= insetData.y_;
			root_->f_= insetData.f_;
			root_->g_= insetData.g_;
			root_->h_= insetData.h_;
		} else {
			insert(root_, &insetData);
		}
	}

	void deleteSmallestChild() {
		delete_one_child(getSmallestChild(root_));
	}

	Node getSmallestChild(){
		return *getSmallestChild(root_);
	}

	bool isContain(Node& n){
		if (root_ == NULL)
			return false;
		is_found_ = false;
		return isContain(&n, root_);
	}

	Node* find(Node& n) {
		if (root_ == NULL){
			return false;
		}
		is_found_ = false;
		return find(n, root_);
	}

private:
	Node *root_, *NIL_, *found_node_;
	bool is_found_{false};
	uint16_t size_{0};
};
/*
#include <queue>
#include <list>
#include <algorithm>
#include <cfloat>

template <typename T>
class Vec2{
public:
	Vec2(){};
	Vec2(T _x, T _y){
		x_ = _x;
		y_ = _y;
	}
	T x_;
	T y_;
	bool operator==(const Vec2<T>& r) const{
		return this->x_ == r.x_ && this->y_ == r.y_;
	}
};

class Vec2Set : public Vec2<int16_t>{
public:
	Vec2Set(){}
	Vec2Set(int _x, int _y){
		x_ = _x;
		y_ = _y;
	}
	Vec2Set(int _x, int _y, int _f, int _g, int _h){
		x_ = _x;
		y_ = _y;
		f_ = _f;
		g_ = _g;
		h_ = _h;
	}
	bool operator<(const Vec2Set& r) const{
		return this->f_ > r.f_;
	}
	Vec2Set operator+(const Vec2Set& r) const{
		return Vec2Set{this->x_ + r.x_, this->y_ + r.y_};
	}
	double f_{};
	int g_{};
	double h_{};
};

class PathSet : public std::list<Vec2Set>{
public:
	bool isContain(const Vec2Set& p){
		return std::any_of(this->begin(),this->end(),[&](const Vec2Set& it){
			return it == p;
		});
	}
	PathSet::iterator find(const Vec2Set& node){
		return std::find_if(this->begin(),this->end(),[&](Vec2Set& it){
			return it == node;
		});
	}
	Vec2Set findTheBestF() {
		double score = DBL_MAX;
		Vec2Set ret;
		for (auto &p : *this) {
			if (p.f_ < score) {
				score = p.f_;
				ret = p;
			}
		}
		return ret;
	}
};
*/

#endif
