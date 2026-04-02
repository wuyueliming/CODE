#pragma once
#include <type_traits>
#include<iostream>
#include"CMalloc.h"

namespace STL {


	//————————————BinT
	template<class T>
	struct BinTreeNode;

	template<typename T>
	using base_node = BinTreeNode<T>;

	template<class T>
	struct BinTreeNode {
		T data;
		base_node<T>* left;
		base_node<T>* right;

		BinTreeNode(T Data = T(), base_node<T>* Left = nullptr, base_node<T>* Right = nullptr) :
			data(Data), left(Left), right(Right) {
		}
		virtual ~BinTreeNode() {//析构函数再处理的时候名字都是destruct，所以和子类析构函数同名，可以重载
			left = nullptr;
			right = nullptr;
		}
	};



	//——————————BST

	template<class T>
	struct BSTreeNode : public BinTreeNode<T> {
		base_node<T>* parent;

		BSTreeNode(T Data = T(), base_node<T>* Left = nullptr, base_node<T>* Right = nullptr, base_node<T>* Parent = nullptr)
			:BinTreeNode<T>(Data, Left, Right)
			, parent(Parent) {
		}
		~BSTreeNode() {
			parent = nullptr;
		}
	public:
		virtual void extra_copy(const BSTreeNode* pNode) {
			//this->data = pNode->data;
			/*if (pNode) {
				this->data.~T();
				new (&(this->data))T(pNode->data);
			}*/
		}

		base_node<T>* brother() {
			if (!parent)return nullptr;
			return this == parent->left ? parent->right : parent->left;
		}

		bool isleft() {
			return  !this || !this->parent ||this == parent->left;
		}
		bool isright() {
			return  !this || !this->parent || this == parent->right;
		}


		BSTreeNode* succ() {//按照中序遍历的顺序思考
			BSTreeNode* succ = nullptr;
			if (this->right) {//当前子树的右子树还未访问
				succ = (BSTreeNode*)this->right;
				while (succ->left)
					succ = (BSTreeNode*)succ->left;
			}
			else {//右子树空不用访问，当前子树已经访问完成
				succ = this;
				//父亲的右子树访问完成->父亲为根的树访问完成。
				while (succ->parent && succ == succ->parent->right) {
					succ = (BSTreeNode*)succ->parent;//当前的后继等价为父亲的后继
				}
				//为空就是最后一个，不为空则代表左子树访问完成，后继为父亲根节点。
				succ = succ->parent == nullptr ? nullptr : (BSTreeNode*)succ->parent;
			}
			return succ;
		}
		BSTreeNode* pred() {//按照中序遍历的顺序思考，取前驱可以看作是右子树-根-左子树的中序遍历
			BSTreeNode* pred = nullptr;
			if (this->left) {
				pred = (BSTreeNode*)this->left;
				while (pred->right)
					pred = (BSTreeNode*)pred->right;
			}
			else {//父亲的左子树this刚访问
				pred = this;
				//一直往右上找父亲到头，this是最右上父亲树的中序第一个
				while (pred->parent && pred == pred->parent->left) {
					pred = (BSTreeNode*)pred->parent;//this第一个访问，所以当前的前驱等价为最右上父亲树的前驱
				}
				//为空就是最后一个，不为空则代表右子树的中序第一个刚访问完，前驱为根
				pred = pred->parent == nullptr ? nullptr : (BSTreeNode*)pred->parent;
			}
			return pred;
		}
	};

	template<class T>
	struct SplayTreeNode : public BSTreeNode<T> {
		SplayTreeNode(T Data = T(), base_node<T>* Left = nullptr, base_node<T>* Right = nullptr, base_node<T>* Parent = nullptr)
			:BSTreeNode<T>(Data, Left, Right, Parent) {}
		~SplayTreeNode(){}
	};






	//————————BBST
	template<class T>
	struct AVLTreeNode : public SplayTreeNode<T> {
		size_t height;

		AVLTreeNode(T Data = T(), base_node<T>* Left = nullptr, base_node<T>* Right = nullptr, base_node<T>* Parent = nullptr, size_t Height = 1)
			:SplayTreeNode<T>(Data, Left, Right, Parent)
			, height(Height) {
		}
	public:
		base_node<T>* taller_child() {
			long long LH = LCH();
			long long RH = RCH();
			if (LH > RH)return this->left;
			else if (LH < RH)return this->right;
			else {
				return !this->parent ? this->left : (this == this->parent->left ? this->left : this->right);
			}
		}
		size_t LCH() {
			AVLTreeNode* left = (AVLTreeNode*)this->left;
			return left ? left->height : 0;
		}
		size_t RCH() {
			AVLTreeNode* right = (AVLTreeNode*)this->right;
			return right ? right->height : 0;
		}
		long long BF() {
			return (long long)LCH() - (long long)RCH();
		}
		bool update_height() {
			size_t  L = LCH();
			size_t  R = RCH();
			size_t oldheight = height;
			height = max(L, R) + 1;
			return height == oldheight ? false : true;
		}
		void update_above() {
			AVLTreeNode* cur = this;
			while (cur) {
				cur->update_height();
				cur = (AVLTreeNode*)cur->parent;
			}
		}
		virtual void extra_copy(const BSTreeNode<T>* pNode)override {
			AVLTreeNode* p = (AVLTreeNode*)pNode;
			
			this->height = p->height;
		}
	};

	template<class T>
	struct LeftHeapNode : public SplayTreeNode<T> {
		size_t npl;

		LeftHeapNode(T Data = T(), base_node<T>* Left = nullptr, base_node<T>* Right = nullptr, base_node<T>* Parent = nullptr, size_t NPL = 1)
			:SplayTreeNode<T>(Data, Left, Right, Parent)
			, npl(NPL) {
		}
	public:
		void update_npl() {
			size_t L = this->left ? this->left->npl : 0;
			size_t R = this->right ? this->right->npl : 0;
			npl = min(L, R) + 1;
		}
		virtual void extra_copy(const BSTreeNode<T>* pNode)override {
			LeftHeapNode* p = (LeftHeapNode*)pNode;
			
			this->npl = p->npl;
		}
	};

	enum COLOR {
		RED,
		BLACK
	};
	template<class T>
	struct RBTreeNode : public SplayTreeNode<T> {
		COLOR color;
		size_t dark_h;

		RBTreeNode(T Data = T(), base_node<T>* Left = nullptr, base_node<T>* Right = nullptr, base_node<T>* Parent = nullptr, COLOR Color = RED,size_t h=0)
			:SplayTreeNode<T>(Data, Left, Right, Parent)
			,color(Color) 
			,dark_h(h){
		}
	public:
		virtual void extra_copy(const BSTreeNode<T>* pNode)override {
			RBTreeNode* p = (RBTreeNode*)pNode;

			/*if (pNode) {
				this->data.~T();
				new (&(this->data)) const T(pNode->data);
			}*/
			//this->data = pNode->data;

			this->color = p->color;
			this->dark_h = p->dark_h;
		}
		size_t LCH() {
			RBTreeNode* left = (RBTreeNode*)this->left;
			return left ? left->dark_h : 0;
		}
		size_t RCH() {
			RBTreeNode* right = (RBTreeNode*)this->right;
			return right ? right->dark_h : 0;
		}
		void update_height() {
			size_t  L = LCH();
			size_t  R = RCH();
			dark_h = color == RED ? max(L, R) : max(L, R) + 1;
		}
		void update_above() {
			RBTreeNode* cur = this;
			while (cur) {
				cur->update_height();
				cur = (RBTreeNode*)cur->parent;
			}
		}
	};





}