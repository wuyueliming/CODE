#pragma once
#include"BSTree.h"


namespace STL {


	template<class Key, class T, class KeyOfData, class compare = less<Key>,class Allocator=CMP::TCMemAllocator>
	class SplayTree :public BSTree<Key, T, KeyOfData, compare,Allocator> {
	public:
		//typedef base_node<T> base_node;
		typedef SplayTreeNode<T> node;
		typedef BST_iterator<T, T&, T*> Iterator;
		typedef BST_iterator<T, const T&, const T*> ConstIterator;

		struct default_update {
			void operator()(base_node<T>* pnode) {}
		};

	public:
		SplayTree():BSTree<Key, T, KeyOfData, compare>(){}
		SplayTree(const SplayTree& ST) {
			if (&ST == this)return;
			this->_root = BSTree<Key, T, KeyOfData, compare>::template CopyTree<node>(nullptr,ST._root);
			this->_size = ST._size;
		}
		SplayTree& operator=(SplayTree ST) {
			swap(ST);
			return *this;
		}
		~SplayTree() {}


	public:
		
		pair<Iterator, bool> insert(const T& data) override {
			KeyOfData KOD; compare cmp;// 5  4  6  2  3
			if (!this->_root) {//空树特殊处理
				//this->_root = new node(data);
				this->_root = (base_node<T>*)Allocator::Alloc(sizeof(node));
				new(this->_root)node(data);
				this->_size++;
			}

			Iterator pos = find(KOD(data));//KOD(*pos) == KOD(data)
			if (pos && BSTree<Key, T, KeyOfData, compare>::equal(KOD(*pos),KOD(data))) 
				return pair<Iterator, bool>(pos, false);

			node* newL, * newR;
			node* root = (node*)this->_root;
			//base_node<T>* newnode = new node(data);
			base_node<T>* newnode = (base_node<T>*)Allocator::Alloc(sizeof(node));
			new(newnode) node(data);
			if (cmp(KOD(root->data), KOD(data))) {
				newL = (node*)this->_root; newR = (node*)this->_root->right;
				newL->right = nullptr;
			}
			else {
				newR = (node*)this->_root; newL = (node*)this->_root->left;
				newR->left = nullptr;
			}
			this->_root = newnode;
			newnode->left = newL;  if(newL)newL->parent = newnode;
			newnode->right = newR; if(newR)newR->parent = newnode;
			
			return pair<Iterator, bool>({ newnode, this->_root }, true);
		}

		size_t erase(const Key& key) override {
			auto p = BSTree<Key, T, KeyOfData, compare>::search(key);
			if (!p.first)return 0;

			auto q = BSTree<Key, T, KeyOfData, compare>::template remove<node>((node*)p.first);
			base_node<T>* parent = q.second; this->_size--;
			if (!q. second)return 1;

			splay(q.second);
			
			return 1;
		}

		Iterator  find(const Key& key) override{
			auto p = BSTree<Key, T, KeyOfData, compare>:: search(key);
			splay( p.first ? p.first : p.second);
			return Iterator(p.first, this->_root);
		}


	protected:

		//可以让AVLT，RBT，LeftHeap不继承BST，继承SplayTree：
		void splay(base_node<T>* pos) {
			node* child = (node*)pos;
			node* parent = (node*)child->parent;
			node* grandparent = parent ? (node*)parent->parent: nullptr;

			//每次child高度上升2层
			while (parent && grandparent) {
				base_node<T>*& ptr = BSTree<Key, T, KeyOfData, compare>::ParentPtrRefFrom(grandparent);
				base_node<T>* newroot = RotateAt(grandparent, parent, child);//要双旋转而不是平衡的旋转
				ptr = newroot;
				//child指针始终指向那个pos，不用更新
				parent = (node*)child->parent;
				if(parent)grandparent = (node*)parent->parent;
			}
			if (parent) {//最后多余一层进行左(右)单旋，此时parent为根
				base_node<T>*& ptr = BSTree<Key, T, KeyOfData, compare>::ParentPtrRefFrom(parent);
				base_node<T>* grandchild = child->isleft() ? child->left : child->right;
				ptr = RotateAt(parent,child,grandchild,true);
			}
		}


		template<class extra_update = default_update>
		base_node<T>* RotateAt(base_node<T>* parent, base_node<T>* root, base_node<T>* child, bool toBalance = false) {
			base_node<T>* grandparent = ((node*)parent)->parent;
			node* C = (node*)child; node* R = (node*)root; node* P = (node*)parent;
			node* a, * b, * c; a = b = c = nullptr;


			if (toBalance) {//平衡旋转
				//一般平衡二叉树都一定有三个非空节点参与旋转。为处理child为空特殊判断并且使用zig(zag)
				if (P->left==R && R->left== C) {//左(右)单旋(平衡)
					//zig右单旋
					R->parent = grandparent;
					return zig<extra_update>(parent, root);
					/*a = C; b = R; c = P;
					return reconstruct34<extra_update>(a, b, c, a->left, a->right, b->right, c->right);*/
				}
				else if (P->right == R && R->right == C) {//——可用zig zag也可reconstruct34
					//zag左单旋
					R->parent = grandparent;
					return zag<extra_update>(parent, root);
					/*a = P; b = R; c = C;
					return reconstruct34<extra_update>(a, b, c, a->left, b->left, c->left, c->right);*/
				}
			}
			else {//伸展旋转
				//双旋上升两层,不能提前改parent，会影响R的左右判断
				if (R->isleft() && C->isleft()) {//左(右)双旋(child升两层)
					//zig右双旋
					C->parent = grandparent;
					return double_zig<extra_update>(parent, root, child);
				}
				else if(R->isright() && C->isright()){
					//zag左双旋
					C->parent = grandparent;
					return double_zag<extra_update>(parent, root, child);
				}
			}


			if (R->isleft() != C->isleft()) {//左右双旋(平衡+child升两层)
				if (R->isleft() && C->isright()) {
					C->parent = grandparent;
					a = R; b = C; c = P;
					return reconstruct34<extra_update>(a, b, c, a->left, b->left, b->right, c->right);
				}
				else if (R->isright() && C->isleft()) {
					C->parent = grandparent;
					a = P; b = C; c = R;
					return reconstruct34<extra_update>(a, b, c, a->left, b->left, b->right, c->right);
				}
			}

			assert(false);
			return nullptr;//错误关系
		}
		
		
		template<class extra_update>
		base_node<T>* double_zig(base_node<T>* parent, base_node<T>* root, base_node<T>* child) {
			zig<extra_update>(parent, root);
			zig<extra_update>(root, child);
			return child;
		}


		template<class extra_update>
		base_node<T>* double_zag(base_node<T>* parent, base_node<T>* root, base_node<T>* child) {
			zag<extra_update>(parent, root);
			zag<extra_update>(root, child);
			return child;
		}

		template<class extra_update>
		base_node<T>* zig(base_node<T>* parent, base_node<T>* child) {
			extra_update update;
			node* swing_node = (node*)child->right;
			parent->left = swing_node;
			if (swing_node)swing_node->parent = parent;

			child->right = parent; 
			((node*)parent)->parent = child;
		
			update(parent); update(child);
			return child;
		}

		template<class extra_update>
		base_node<T>* zag(base_node<T>* parent, base_node<T>* child) {
			extra_update update;
			node* swing_node = (node*)child->left;

			parent->right = swing_node;
			if (swing_node)swing_node->parent = parent;

			child->left = parent; 
			((node*)parent)->parent = child;
			
			update(parent); update(child);
			return child;
		}

		template<class extra_update>
		base_node<T>* reconstruct34(base_node<T>* a, base_node<T>* b, base_node<T>* c, base_node<T>* x1, base_node<T>* x2, base_node<T>* x3, base_node<T>* x4) {
			node* A = (node*)a; node* B = (node*)b; node* C = (node*)c;
			node* X1 = (node*)x1; node* X2 = (node*)x2;
			node* X3 = (node*)x3; node* X4 = (node*)x4;
			extra_update update;

			A->left = X1; A->right = X2; update(A);
			if (X1)X1->parent = A; if (X2)X2->parent = A;

			if (B) {
				B->left = A; B->right = C; update(C);
				A->parent = B; C->parent = B;
			}
			if (C) {
				C->left = X3; C->right = X4; update(B);
				if (X3)X3->parent = C; if (X4)X4->parent = C;
			}
			return b;
		}

	};






	///*void testZ1() {
	//	SplayTree<int, int, KOD1<int>, less<int>> ST;

	//	ST.insert(5);
	//	ST.insert(4);
	//	ST.insert(6);
	//	ST.insert(2);
	//	ST.insert(3);

	//	auto it = ST.find(5);
	//	ST.erase(3);

	//	cout << *it;
	//}

	//void testZ2() {
	//	SplayTree<int, int, KOD1<int>, less<int>> ST;

	//	ST.insert(5);
	//	ST.insert(4);
	//	ST.insert(6);
	//	ST.insert(2);
	//	ST.insert(3);

	//	ST.InorderTraverse(); cout << endl;
	//	auto copt_st(ST);
	//	ST.insert(7);
	//	ST.InorderTraverse();

	//}*/


}





















