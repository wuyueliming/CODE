#pragma once
#include"BSTree.h"



namespace xdh {



	template<class T, class compare = less<T>>
	class LeftHeap :public SplayTree<T, T, KOD1<T>, compare> {
	public:
		typedef base_node<T> base_node;
		typedef LeftHeapNode<T> node;
		typedef  typename BSTree<T, T, KOD1<T>, compare>::Iterator Iterator;
		typedef  typename BSTree<T, T, KOD1<T>, compare>::ConstIterator ConstIterator;
	public:
		LeftHeap() :SplayTree<T, T, KOD1<T>, compare>() {}

		LeftHeap(const LeftHeap& LH) {
			if (&LH == this)return;

			this->_root = SplayTree<T, T, KOD1<T>, compare>::template CopyTree<node>(nullptr, LH._root);
			node* p = (node*)this->_root;
			this->_size = LH._size;
		}

		LeftHeap& operator=(LeftHeap LH) {
			swap(LH);
			return *this;
		}

		~LeftHeap() {}

	public:
		void push(const T& data) {
			insert(data);
		}

		void pop() {
			erase(this->_root->data);
		}

		T& top() {
			return this->_root->data;
		}

		bool check() {
			return check(this->_root);
		}

	protected:
		bool check(base_node* root) override{
			if (!root)return true;
			compare cmp;

			bool L = root->left ? cmp(root->left->data, root->data) : true;
			bool R = root->right ? cmp(root->right->data, root->data) : true;
			if (L && R) {
				return check(root->left) && check(root->right);
			}
			return false;
		}

		pair<Iterator, bool> insert(const T& data)override {
			node* newnode = new node(data);

			this->_root = merge(this->_root, newnode);
			this->_size++;
			return pair<Iterator, bool>({ this->_root,this->_root }, true);
		}

		size_t erase(const T& key)override {
			if (!this->_root)return 0;
			base_node* L = this->_root->left;
			base_node* R = this->_root->right;

			delete this->_root;
			this->_size--;
			this->_root = merge(L, R);
			node* r = (node*)this->_root; if(r)r->parent = nullptr;
			return 1;
		}

		virtual Iterator find(const T& key) override {
			return { SplayTree<T, T, KOD1<T>, compare>::search(key).first,this->_root };
		}

		base_node* merge_heap(LeftHeap& LH) {
			LH._root = nullptr; LH._size = 0;
			return this->_root = merge(this->_root, LH._root);
		}

		static base_node* merge(base_node* a, base_node* b) {
			if (!a)return b;
			if (!b)return a;

			if (a->data < b->data)std::swap(a, b);
			node* A = (node*)a; node* B = (node*)b;

			node* L = (node*)a->left;
			node* R = (node*)merge(a->right, b);
			A->right = R; R->parent = A;

			if (!L || (L->npl < R->npl && R)) {
				std::swap(a->left, a->right);
				std::swap(L, R);
			}

			A->npl = R ? R->npl + 1 : 1;
			return A;
		}
	};

	template<class T, class compare>
	void swap(LeftHeap<T, compare>& LH1, LeftHeap<T, compare>& LH2) {
		LH1.swap(LH2);
	}



	void testC1() {
		LeftHeap<int> LH;

		vector<int> v = { 1,2,3,4,5,6,7 };

		for (int i = 0; i < v.size(); i++) {
			LH.push(v[i]);
			cout << LH.top() << ' ';
		}
		cout << LH.size();
		cout << endl;

		if (LH.check()) {
			cout << 1;
		}
		else {
			cout << 0;
		}

		LeftHeap<int> copy(LH);
		if (copy.check()) {
			cout << 1;
		}
		else {
			cout << 0;
		}

		/*cout << endl;
		LeftHeapNode<int>* n1 = new LeftHeapNode<int>(1);
		n1->npl = 20;

		LeftHeapNode<int>* n2 = new LeftHeapNode<int>(2);

		BSTreeNode<int>* p = n2;
		p->copy(n1);
		cout << n2->npl;*/

	}
		
	void testC2() {
		LeftHeap<int> LH;

		vector<int> v = { 5,6,7,1,4,2,3 };
		for (int i = 0; i < v.size(); i++) {
			LH.push(v[i]);
			//cout << LH.top() << ' ';
		}
		cout << endl;

		LH.LevelTraverse(); cout << endl;
		cout << endl << endl;

		auto copy(LH);
		copy.LevelTraverse(); cout << endl;
		copy.push(8);
		copy.LevelTraverse();

	}




}