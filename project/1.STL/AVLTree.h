#pragma once
#include"BSTree.h"
#include"SplayTree.h"

namespace STL {

	template<class Key, class T, class KeyOfData, class compare = less<Key>,class Allocator = CMP::TCMemAllocator>
	class AVLTree :public SplayTree<Key, T, KeyOfData, compare,Allocator> {
	public:
		//typedef base_node<T> base_node;
		typedef AVLTreeNode<T> node;
		typedef  typename BSTree<Key, T, KeyOfData, compare>::Iterator Iterator;
		typedef  typename BSTree<Key, T, KeyOfData, compare>::ConstIterator ConstIterator;

		struct update_H {
			void operator()(const base_node<T>* const pnode) {
				((node*)pnode)->update_height();
			}
		};

	public:
		AVLTree() :SplayTree<Key, T, KeyOfData, compare>() {}
		AVLTree(const AVLTree& AVLT) {
			if (&AVLT == this)return;

			this->_root = SplayTree<Key, T, KeyOfData, compare>::template CopyTree<node>(nullptr, AVLT._root);
			this->_size = AVLT._size;
		}
		~AVLTree() {}
		AVLTree& operator=(AVLTree AVLT) {
			swap(AVLT);
			return *this;
		}


	public:
		virtual pair<Iterator, bool> insert(const T& data) {
			KeyOfData KOD = KeyOfData(); compare cmp = compare();
			auto p = SplayTree<Key, T, KeyOfData, compare>::search(KOD(data));
			if (p.first)return pair<Iterator, bool>({ p.first,this->_root }, false);
			if (!p.second) {//ø’ ˜
				//this->_root = new node(data);
				this->root = (base_node<T>*)Allocator::Alloc(sizeof(node));
				new(this->root) node(data);
				this->_size++;
				return pair<Iterator, bool>({ this->_root,this->_root }, true);
			}

			base_node<T>* parent = p.second;
			//node* newnode = (node*)new node(data, nullptr, nullptr, parent);
			node* newnode = (node*)Allocator(sizeof(node));
			new(newnode) node(data, nullptr, nullptr, parent);
			cmp(KOD(data), KOD(parent->data)) ? parent->left = newnode : parent->right = newnode;
			this->_size++;

			node* pos = (node*)parent;
			while (pos) {
				if (pos->BF() < -1 || pos->BF() > 1) {
					base_node<T>* parent = pos->parent; node* child = (node*)pos->taller_child();
					base_node<T>*& ptr = SplayTree<Key, T, KeyOfData, compare>::ParentPtrRefFrom(pos);
					ptr = (node*)SplayTree<Key, T, KeyOfData, compare>:: template RotateAt<update_H>(pos, child, child->taller_child(), true);
					break;
				}
				if (!pos->update_height())break;
				pos = (node*)pos->parent;
			}
			return pair<Iterator, bool>({ newnode,this->_root }, true);
		}

		virtual size_t erase(const Key& key) {
			auto p = SplayTree<Key, T, KeyOfData, compare>::search(key);
			if (!p.first)return 0;

			auto q = SplayTree<Key, T, KeyOfData, compare>::template remove<node>((node*)p.first);
			base_node<T>* parent = q.second; this->_size--;

			node* pos = (node*)parent;
			while (pos) {
				if (pos->BF() < -1 || pos->BF() > 1) {
					base_node<T>* parent = pos->parent;  node* child = (node*)pos->taller_child();
					base_node<T>*& ptr = SplayTree<Key, T, KeyOfData, compare>::ParentPtrRefFrom(pos);
					ptr = pos = (node*)SplayTree<Key, T, KeyOfData, compare>::template RotateAt<update_H>(pos, child, child->taller_child(), true);
				}
				if (!pos->update_height())break;
				pos = (node*)pos->parent;
			}

			return 1;
		}

		virtual Iterator find(const Key& key) override {
			return { SplayTree<Key, T, KeyOfData, compare>::search(key).first,this->_root };
		}


	protected:
		bool check(base_node<T>* root) override {
			return checkAVL(root);
		}
		
		bool checkAVL(base_node<T>* root) {
			if (!root)return true;

			node* rt = (node*)root;
			bool ret = abs((long long)rt->LCH() - (long long)rt->RCH());
			return ret && checkAVL(root->left) && checkAVL(root->right);
		}

	};

	template<class Key, class T, class KeyOfData, class compare = less<Key>>
	void swap(AVLTree<Key, T, KeyOfData, compare>& AVLT1, AVLTree<Key, T, KeyOfData, compare>& AVLT2) {
		AVLT1.swap(AVLT2);
	}




	template<class T1, class T2>
	struct print_pair {
		void operator()(const pair<T1, T2>& p) {
			cout << p.first << ':' << p.second << ' ';
		}
	};

	//void testD1() {
	//	AVLTree<int, pair<int, char>, KOD2<int, char>, less<int>>T;
	//	T.insert(pair<int, char>(15, 'd'));
	//	T.insert(pair<int, char>(20, 'e'));
	//	T.insert(pair<int, char>(7, 'b'));
	//	T.insert(pair<int, char>(9, 'c'));
	//	T.insert(pair<int, char>(3, 'a'));
	//	T.insert(pair<int, char>(1, 'x'));//≤Â»Î–˝◊™
	//	T.insert(pair<int, char>(5, 'g'));

	//	T.insert(pair<int, char>(25, 'g'));
	//	T.InorderTraverse(print_pair<int, char>()); cout << endl;
	//	T.erase(9);//…æ≥˝–˝◊™
	//	T.InorderTraverse(print_pair<int, char>());
	//}

	//void testD2() {
	//	AVLTree<int, int, KOD1<int>, less<int>> T;

	//	T.insert(55);
	//	T.insert(30);
	//	T.insert(100);
	//	T.insert(15);
	//	T.insert(35);
	//	T.insert(75);
	//	T.insert(150);
	//	T.insert(10);
	//	T.insert(80);
	//	T.insert(125);
	//	T.insert(200);
	//	T.insert(250);

	//	T.erase(35);//≤‚ ‘…æ≥˝ ±œÚ…œµ›πÈ
	//	auto p = T.find(200);
	//	cout << *p << endl;

	//	T.InorderTraverse();
	//}

	//void testD3() {
	//	AVLTree<int, int, KOD1<int>, less<int>> T;

	//	T.insert(55);
	//	T.insert(30);
	//	T.insert(100);
	//	T.insert(15);
	//	T.InorderTraverse();
	//	cout << endl;

	//	auto CT(T);
	//	CT.InorderTraverse(); cout << endl;
	//	CT.insert(360);
	//	T.InorderTraverse();
	//}



}
