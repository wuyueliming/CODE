#pragma once
#include"BSTree.h"
#include"SplayTree.h"

namespace STL {

	template<class Key, class T, class KeyOfData, class compare = less<Key>,class Allocator= CMP::TCMemAllocator>
	class RBTree :public SplayTree<Key, T, KeyOfData, compare,Allocator> {
	public:
		//typedef base_node<T> base_node;
		typedef RBTreeNode<T> node;
		typedef  typename BSTree<Key, T, KeyOfData, compare>::Iterator Iterator;
		typedef  typename BSTree<Key, T, KeyOfData, compare>::ConstIterator ConstIterator;

		struct update_H {
			void operator()(const base_node<T>* const pnode) {
				((node*)pnode)->update_height();
			}
		};

	public:
		RBTree() :SplayTree<Key, T, KeyOfData, compare>() {}
		RBTree(const RBTree& RBT) {
			if (&RBT == this)return;

			this->_root = SplayTree<Key, T, KeyOfData, compare>::template CopyTree<node>(nullptr, RBT._root);
			this->_size = RBT._size;
		}
		~RBTree() {}
		RBTree& operator=(RBTree RBT) {
			swap(RBT);
			return *this;
		}


	public:
		
		virtual pair<Iterator, bool> insert(const T& data) {
			KeyOfData KOD = KeyOfData(); compare cmp = compare();
			auto p = SplayTree<Key, T, KeyOfData, compare>::search(KOD(data));
			if (p.first)return pair<Iterator, bool>({ p.first,this->_root }, false);
			if (!p.second) {//空树
				//this->_root = new node(data); 
				this->_root = (base_node<T>*)Allocator::Alloc(sizeof(node));
				new(this->_root) node(data);

				this->_size++;
				node* root = (node*)this->_root;
				root->color = BLACK;
				return pair<Iterator, bool>({ this->_root,this->_root }, true);
			}

			base_node<T>* parent = p.second;
			//node* newnode = (node*)new node(data, nullptr, nullptr, parent);
			node* newnode = (node*)Allocator::Alloc(sizeof(node));
			new(newnode) node(data, nullptr, nullptr, parent);

			cmp(KOD(data), KOD(parent->data)) ? parent->left = newnode : parent->right = newnode;
			this->_size++;

			double_red(newnode);
			return pair<Iterator, bool>({ newnode,this->_root }, true);
		}

		virtual size_t erase(const Key& key) {
			auto p = SplayTree<Key, T, KeyOfData, compare>::search(key);
			if (!p.first)return 0;
			//可以提前记录删除节点颜色，不过也可以不记录用别的方式判断
			//remove实际删除节点只会是单分支节点，不会有双红。
			auto q = SplayTree<Key, T, KeyOfData, compare>::template remove<node>((node*)p.first);
			if (!q.second) {//删除根节点，不用管颜色如何
				node* root = (node*)this->_root;
				if (root) {//删除根节点的时候，有可能变成空树没有代替节点。
					root->color = BLACK; root->update_height();
				}
				this->_size--; return 1;
			}

			//排除删除根节点情况，以下必有parent不为空
			node* replace = (node*)q.first;
			base_node<T>* parent = q.second; this->_size--;
			if (dark_balanced(parent))return 1;//删除后黑高不变(del红 replace黑)
			if (replace && replace->color == RED) {//代替节点红则原节点必为黑(del黑 replace红)
				replace->color = BLACK; replace->dark_h++;
				this->_size--; return 1;
			}

			//replace可能为空(删除叶子节点时,但不影响。调整过程不涉及replace节点)
			double_black(parent);//此时parent左子树或者右子树黑高缺1
			this->_size--; return 1;
		}
		
		virtual Iterator find(const Key& key)override {
			return { SplayTree<Key, T, KeyOfData, compare>::search(key).first,this->_root };
		}

	protected:

		void double_red(base_node<T>* pos) {//pos:插入节点
			if (pos == this->_root) {//根节点没父亲
				node* root = (node*)this->_root;
				root->color = BLACK; root->dark_h++;
				return;
			}
			node* child = (node*)pos;
			node* parent = (node*)child->parent;
			if (parent->color == BLACK)return;//有黑父亲,不用调整
			
			//有红父亲，就必然有爷爷且黑色。(此时孙子、爷爷可能为根，孙子当前函数开始判断，爷爷递归判断)
			node* grandparent = (node*)parent->parent;
			node* uncle = (node*)parent->brother();
			if (!uncle || uncle->color == BLACK) {
				base_node<T>*& ptr = SplayTree<Key, T, KeyOfData, compare>::ParentPtrRefFrom(grandparent);
				if (parent->isleft() == child->isleft()) {//同侧
					parent->color = BLACK;
				}else {//异侧
					child->color = BLACK;
				}
				grandparent->color = RED;
				ptr = SplayTree<Key, T, KeyOfData, compare>:: template RotateAt<update_H>(grandparent, parent, child,true);
			}
			else {
				grandparent->color = RED;
				parent->dark_h++; uncle->dark_h++;
				parent->color = uncle->color = BLACK;
				double_red(grandparent);
			}
		}

		void double_black(base_node<T>* pos) {//pos:代替节点父亲
			node* parent = (node*)pos; if (!pos)return;
			node* child = (node*)parent->right;
			node* brother = (node*)parent->left;
			if (parent->RCH() > parent->LCH())std::swap(child, brother);
			//parent在child子树删除了一个黑节点，那么brother子树往下也必然有一个黑节点，则brother必不为空

			base_node<T>*& ptr = SplayTree<Key, T, KeyOfData, compare>::ParentPtrRefFrom(parent);
			if (brother->color==BLACK) {//兄弟为黑
				bool red_L = !brother->left ? false : ((node*)brother->left)->color == RED;
				bool red_R = !brother->right ? false : ((node*)brother->right)->color == RED;
				if (red_L || red_R) {//兄弟有红孩子->(BB-1)
					node* new_root;  
					auto old_color = parent->color;//一定要红色侄子旋转
					base_node<T>* nephew = red_L ? brother->left : brother->right;
					ptr = new_root = (node*)SplayTree<Key, T, KeyOfData, compare>:: template RotateAt<update_H>(parent, brother, nephew,true);

					node* new_L = (node*)new_root->left;
					node* new_R = (node*)new_root->right;
					new_L->color = new_R->color = BLACK; new_root->color = old_color;
					new_L->update_height(); new_R->update_height();
					new_root->update_height(); return;
				}
				else {//兄弟双黑孩子->(BB-2)
					if (parent->color == RED) {//(BB-2R)
						parent->color = BLACK; 
						brother->color = RED; brother->dark_h--;
						return;
					}
					else {//(BB-2B)
						brother->color = RED;//child黑高缺1，那我brother也减1。
						//把parent的child子树黑高缺1转化成grandparent的parent子树的黑高缺1。
						brother->dark_h--; parent->dark_h--;
						base_node<T>* grandparent = parent->parent;
						double_black(grandparent);
					}
				}
			}
			else {//兄弟为红->(BB-3)
				parent->color = RED; brother->color = BLACK;//取同侧的侄子进行旋转,方便染色
				base_node<T>* nephew = brother->isleft() ? brother->left : brother->right;
				ptr = SplayTree<Key, T, KeyOfData, compare>:: template RotateAt<update_H>(parent, brother, nephew,true);
				//因为brother和child是同一层的，而c黑bro红，又由于在出现
				//双黑问题之前是一颗红黑树，所以brother必有两个黑孩子保证旋转不会因为nephew为空而失败。
				double_black(parent);//将问题转化为(BB-1)或(BB-2R)
			}
		}

		bool check(base_node<T>* root) override {
			return checkRBT(this->_root);
		}

		bool checkRBT(base_node<T>* root) {
			node* pos = (node*)root;

			bool doublered = pos->parent ? ((node*)pos->parent)->color == RED : true;
			bool dark_balance = dark_balanced(root);

			return  doublered && dark_balance && checkRBT(root->left) && checkRBT(root->right);
		}
		bool dark_balanced(base_node<T>* root) {
			node* pos = (node*)root;

			bool balance = pos->LCH() == pos->RCH();
			bool dark = pos->color == BLACK ? pos->dark_h == pos->LCH() + 1 : pos->dark_h == pos->LCH();
			return  balance && dark;
		}


	};

	template<class Key, class T, class KeyOfData, class compare = less<Key>>
	void swap(RBTree<Key, T, KeyOfData, compare>& RBT1, RBTree<Key, T, KeyOfData, compare>& RBT2) {
		RBT1.swap(RBT2);
	}



	//void testE1() {//测试插入
	//	RBTree<int, int, KOD1<int>, less<int>> T;
	//	T.insert(55);
	//	T.insert(20);
	//	T.insert(25);
	//	T.insert(10);
	//	T.insert(5);
	//	T.insert(12);

	//	T.InorderTraverse();
	//}


	//void testE2() {//测试删除
	//	RBTree<int, int, KOD1<int>, less<int>> T;
	//	
	//	T.insert(55);
	//	T.insert(20);
	//	T.insert(25);
	//	T.insert(10);
	//	T.insert(5);
	//	T.insert(12);

	//	T.InorderTraverse(); cout << endl;

	//	T.erase(25);//双黑删除叶子节点—>(BB-3)

	//	T.erase(12);//—>(BB-2R)

	//	T.erase(5);//—>(BB-1)

	//	T.erase(10);//—>(BB-2B)



	//	T.InorderTraverse();

	//}


	//void testE3() {
	//	RBTree<int, int, KOD1<int>, less<int>> T;
	//	T.insert(55);
	//	T.insert(20);
	//	T.insert(25);
	//	T.insert(10);
	//	T.insert(5);
	//	T.insert(12);

	//	T.InorderTraverse(); cout << endl;

	//	auto copyT(T);

	//	copyT.InorderTraverse();
	//	copyT.insert(66);

	//}







}






