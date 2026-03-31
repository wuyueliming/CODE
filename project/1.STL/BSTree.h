#pragma once
#include"BinTree.h"
#include<assert.h>

namespace STL {

	template<class T>
	struct KOD1 {
		const T& operator()(const T& data) {
			return data;
		}
	};

	template<class T1, class T2>
	struct KOD2 {
		const T1& operator()(const pair<T1, T2>& data) {
			return data.first;
		}
	};

	template<class T, class ref, class ptr>
	struct BST_iterator {
	public:
		//typedef base_node<T> base_node;
		typedef BSTreeNode<T> node;
		typedef BST_iterator<T, ref, ptr> self;

		BST_iterator(base_node<T>* pnode, base_node<T>* root) {
			_pnode = (node*)pnode;
			_root = (node*)root;
		}

		template<class IT>
		BST_iterator(const IT& it) :_pnode(it._pnode), _root(it._root){}

		ref operator*() {
			return _pnode->data;
		}

		ptr operator ->() {
			return &(_pnode->data);
		}

		bool operator ==(const self& it) {
			return it._pnode == _pnode;
		}
		bool operator !=(const self& it) {
			return !operator == (it);
		}

		self operator++(int ) {
			self temp(*this);
			operator++();
			return temp;
		}
		self operator--(int) {
			self temp(*this);
			operator--();
			return temp;
		}

		self& operator++() {
			_pnode=(node*)_pnode->succ();
			return *this;
		}
		self& operator--() {
			if (!_root)return *this;
			if (!_pnode) {
				_pnode = _root;
				while (_root->right) {
					_pnode = (node*)_pnode->right;
				}
			}
			else {
				_pnode = (node*)_pnode->pred();
			}
			return *this;
		}

		explicit operator bool()const {
			return _pnode;
		}

		bool operator! () {
			return _pnode == nullptr;
		}

	public:
		node* _pnode;
		node* _root;
	};




	template<class Key, class T, class KeyOfData, class compare = less<Key>,class Allocator=CMP::TCMemAllocator>
	class BSTree :public BinTree<T,Allocator> {
	public:
		//typedef base_node<T> base_node;
		typedef BSTreeNode<T> node;//node内部存储指针都是base_node<T>*，除了使用指针访问特殊成员或者new node时用node*
		//其余传地址、访问data或者左右指针都使用base_node<T>*
		typedef BST_iterator<T, T&, T*> Iterator;
		typedef BST_iterator<T, const T&,const T*> ConstIterator;

		static bool equal(const Key& k1, const Key& k2) {
			compare cmp;
			return !cmp(k1, k2) && !cmp(k2, k1);
		}

		struct judge {
			bool operator()(const T& e, const Key& key = Key(), bool newbase = false) {
				KeyOfData KOD;
				static Key base(key);
				if (newbase) {
					base = key;
					return true;
				}
				return equal(base, KOD(e));
			}
		};

	public:
		BSTree() :BinTree<T>() {}
		BSTree(const BSTree<Key, T, KeyOfData, compare>& BST) {
			if (&BST == this)return;

			this->_root = CopyTree<node>(nullptr, BST._root);
			this->_size = BST._size;

		}
		~BSTree() {}
		BSTree& operator=(BSTree BST) {
			swap(BST);
			return *this;
		}

		//使用bintree的这个构造是没有构造parent指针的，不过copytree重新建一棵树就有了
		BSTree(const vector<T>& inorder, const vector<T>& _order, bool pre) :BinTree<T>(inorder, _order, pre) {}


	public:
		Iterator begin() {
			if(!this->_root)return { this->_root,this->_root };
			base_node<T>* first = this->_root;
			while (first->left) {
				first = first->left;
			}
			return { first,this->_root };
		}
		Iterator end() {
			return { nullptr,this->_root };
		}

		ConstIterator begin() const{
			if (!this->_root)return { this->_root,this->_root };
			base_node<T>* first = this->_root;
			while (first->left) {
				first = first->left;
			}
			return { first,this->_root };
		}
		ConstIterator end() const{
			return { nullptr,this->_root };
		}

		ConstIterator cbegin() const {
			return begin();
		}
		ConstIterator cend() const {
			return end();
		}


		//返回插入后pos的位置
		base_node<T>* insert(base_node<T>* pos, const T& data) {

		}
		//返回删除后pos的位置
		base_node<T>* erase(base_node<T>* pos) {

		}

		//返回插入的节点指针
		virtual pair<Iterator, bool> insert(const T& data) {
			KeyOfData KOD = KeyOfData(); compare cmp = compare();
			auto p = search(KOD(data)); 
			if (p.first) return pair<Iterator, bool>({ p.first, this->_root }, false);
			if (!p.second) {//this->_root为空，空树
				//this->_root = new node(data);
				this->_root = (base_node<T>*)Allocator::Alloc(sizeof(node));
				new(this->_root)node(data);
				this->_size++;
				return pair<Iterator, bool>({ this->_root, this->_root }, true);
			}
			base_node<T>* pre = p.second;

			//base_node<T>* newnode = new node(data, nullptr, nullptr, pre);
			base_node<T>* newnode = (base_node<T>*)Allocator::Alloc(sizeof(node));
			new (newnode) node(data, nullptr, nullptr, pre);

			cmp(KOD(data), KOD(pre->data)) ? pre->left = newnode : pre->right = newnode;
			this->_size++;
			return pair<Iterator, bool>({ newnode, this->_root }, true);
		}

		//返回删除节点个数
		virtual size_t erase(const Key& key) {
			auto p = search(key);
			if (!p.first)return 0;

			remove((node*)p.first); this->_size--;
			return 1;
		}

		virtual Iterator find(const Key& key) {
			return { search(key).first,this->_root };
		}

		virtual size_t count(const Key& key) final {
			judge()(T(), key, true);
			return this->BinTree<T>::LevelTraverse(judge());
		}

		

		//返回大于等于key第一个元素的迭代器
		virtual Iterator lower_bound(const Key& key) {
			auto p = search(key);
			KeyOfData KOD; compare cmp;
			if (!p.first) {
				if (!p.second)return Iterator(nullptr, this->_root);
				//没找到key并且有父亲时。那么插入key之后，父亲不是前驱就是后继
				if (cmp(key, KOD(p.second->data))) {//后继
					return Iterator(p.second, this->_root);
				}
				else {//前驱
					return Iterator(((node*)p.second)->succ(), this->_root);
				}
			}

			base_node<T>* ret = p.first;
			base_node<T>* next_ret = _search_(ret->left, key).first;
			while (next_ret) {
				ret = next_ret;
				next_ret= _search_(ret->left, key).first;
			}
			return Iterator(ret, this->_root);
		}

		//返回大于key第一个元素的迭代器
		virtual Iterator upper_bound(const Key& key) {
			auto p = search(key);
			KeyOfData KOD; compare cmp;
			if (!p.first) {
				if (!p.second)return Iterator(nullptr, this->_root);
				//没找到key并且有父亲时。那么插入key之后，父亲不是前驱就是后继
				if (cmp(key, KOD(p.second->data))) {//后继
					return Iterator(p.second, this->_root);
				}
				else {//前驱
					return Iterator(((node*)p.second)->succ(), this->_root);
				}
			}

			base_node<T>* ret = ((node*)p.first)->succ();
			return Iterator(ret,this->_root);
		}





	protected:
		

		base_node<T>*& ParentPtrRefFrom(base_node<T>* ptr) {
			node* p = (node*)ptr;
			if (!p->parent)return this->_root;
			if (p->isleft())return p->parent->left;
			else /*if (p->isright())*/return p->parent->right;
			assert(p->parent->left == p || p->parent->right == p);
		}

		template<class node_type=node>
		base_node<T>* CopyTree(base_node<T>* parent, base_node<T>* copyroot) {
			if (!copyroot)return nullptr;

			//由于data的const属性不能先构造再用copy赋值，所以构造时直接赋值
			//node_type* newnode = new node_type(copyroot->data);
			node_type* newnode = (node_type*)Allocator::Alloc(sizeof(node_type));
			new(newnode) node_type(copyroot->data);

			//使用extra_copy 复制额外的数据如height
			newnode->extra_copy((node_type*)copyroot);

			newnode->left = CopyTree<node_type>(newnode, newnode->left);
			newnode->right = CopyTree<node_type>(newnode, newnode->right);
			newnode->parent = parent;
			
			return newnode;
		}

		
		template<class node_type>
		pair<base_node<T>*, base_node<T>*> _remove_(node* del, node** return_add) {
			if (del->left && del->right) {
				node* succ = del->succ();

				//del->data = succ->data;//pair有const成员时不允许赋值
				if (succ) {
					auto old_left = del->left;
					auto old_right = del->right;
					auto old_parent = del->parent;

					//由于data的const属性不能先构造再用copy赋值，所以构造时直接赋值
					//node_type* newnode = new node_type(succ->data, old_left, old_right, old_parent);
					node_type* newnode = (node_type*)Allocator::Alloc(sizeof(node_type));
					new(newnode) node_type(succ->data, old_left, old_right, old_parent);
					//使用extra_copy 复制额外的数据如height
					newnode->extra_copy((node_type*)succ);

					*return_add = newnode;
				}
				return remove(succ);
				//return pair<base_node<T>*, base_node<T>*>(del, del->parent);
			}
			else {
				node* replace = del->left ? (node*)del->left : (node*)del->right;
				pair<base_node<T>*, base_node<T>*> ret(replace, del->parent);
				if (!del->parent) {
					this->_root = replace;
				}
				else {
					if (del == del->parent->left)del->parent->left = replace;
					else del->parent->right = replace;
				}
				if (replace)replace->parent = del->parent;
				//delete del;
				Allocator::Free(del);
				return ret;
			}
		}

		//返回实际删除后代替节点指针和父节点指针
		template<class node_type=node>
		pair<base_node<T>*, base_node<T>*> remove(node* del) {
			node* new_node;
			base_node<T>* parent_ptr = ParentPtrRefFrom(del);

			auto p = _remove_<node_type>(del,&new_node);
			parent_ptr = new_node;

			return p;
		}

		pair<base_node<T>*, base_node<T>*> _search_ (base_node<T>* root, const Key& key) {
			KeyOfData KOD = KeyOfData();
			compare cmp = compare();

			base_node<T>* pre = nullptr;
			base_node<T>* cur = root;//如果出现bug，把这里的root改成this->_root就是原来的search了。
			while (cur) {
				if (cmp(key, KOD(cur->data))) {
					pre = cur;
					cur = cur->left;
				}
				else if (cmp(KOD(cur->data), key)) {
					pre = cur;
					cur = cur->right;
				}
				else {
					return pair<base_node<T>*, base_node<T>*>(cur, pre);
				}
			}
			return pair<base_node<T>*, base_node<T>*>(nullptr, pre);
		}

		//返回查找节点指针和父节点指针
		pair<base_node<T>*, base_node<T>*> search(const Key& key) {
			return _search_(this->_root, key);
		}



		virtual bool check(base_node<T>* root) {
			if (!root)return true;
			compare cmp; KeyOfData KOD;

			bool L = root->left ? cmp(KOD(root->left->data),KOD(root->data)) : true;
			bool R = root->right ? cmp(KOD(root->data), KOD(root->right->data)) : true;
			if (L && R) {
				return check(root->left) && check(root->right);
			}

			return false;
		}

	};//类结束

	template<class Key, class T, class KeyOfData, class compare = less<Key>>
	void swap(BSTree<Key, T, KeyOfData, compare>& BST1, BSTree<Key, T, KeyOfData, compare>& BST2) {
		BST1.swap(BST2);
	}






	/*void testB1() {
		vector<int> inorder = { 9,3,15,20,7 };
		vector<int> preorder = { 3,9,20,15,7 };
		vector<int> postorder = { 9,15,7,20,3 };

		BSTree<int, int, KOD1< int>, less<int>> T(inorder, postorder, false);


		T.PreorderTraverse(); cout << endl;

		BSTree<int, int, KOD1<int>, less<int>> copy = T;
		copy.InorderTraverse();

		cout << endl <<"count 15:"<< copy.count(15) << endl;

		auto it = copy.lower_bound(10);
		cout << "lower_bound of 10:" << *it << endl;

		it = copy.upper_bound(10);
		cout << "upper_bound of 10:" << *it;

	}*/


	/*template<class T1, class T2 >
	struct v
	{
		void operator()(const pair<T1, T2>& p) {
			cout << p.first << ':' << p.second << ' ';
		}
	};

	void testB2() {
		BSTree<int, pair<int, char>, KOD2<int, char>, less<int>> T;

		T.insert(pair<int, char>(50, 'e'));
		T.InorderTraverse(v<int, char>()); cout << T.size() << endl;

		T.insert(pair<int, char>(10, 'a'));
		T.InorderTraverse(v<int, char>()); cout << T.size() << endl;

		T.insert(pair<int, char>(20, 'b'));
		T.InorderTraverse(v<int, char>()); cout << T.size() << endl;

		T.insert(pair<int, char>(30, 'c'));
		T.InorderTraverse(v<int, char>()); cout << T.size() << endl;

		T.insert(pair<int, char>(40, 'd'));
		T.InorderTraverse(v<int, char>()); cout << T.size() << endl;

		T.insert(pair<int, char>(60, 'f'));
		T.InorderTraverse(v<int, char>()); cout << T.size() << endl;

		T.insert(pair<int, char>(70, 'g'));
		T.InorderTraverse(v<int, char>()); cout << T.size() << endl;




		T.erase(50);
		T.InorderTraverse(v<int, char>()); cout << T.size() << endl;

		T.erase(40);
		T.InorderTraverse(v<int, char>()); cout << T.size() << endl;

		T.erase(30);
		T.InorderTraverse(v<int, char>()); cout << T.size() << endl;

		T.erase(20);
		T.InorderTraverse(v<int, char>()); cout << T.size() << endl;

		T.erase(60);
		T.InorderTraverse(v<int, char>()); cout << T.size() << endl;

		T.erase(70);
		T.InorderTraverse(v<int, char>()); cout << T.size() << endl;

	}

	
	void testB3() {
		BSTree<int, pair<const int, char>, KOD2<int, char>, less<int>> T;

		T.insert(pair<int, char>(50, 'e'));
		T.insert(pair<int, char>(10, 'a'));
		T.insert(pair<int, char>(20, 'b'));
		T.insert(pair<int, char>(30, 'c'));
		T.insert(pair<int, char>(40, 'd'));
		T.insert(pair<int, char>(60, 'f'));
		T.insert(pair<int, char>(70, 'g'));
		T.InorderTraverse(v<int, char>()); cout <<"size:" << T.size() << endl;

		auto copy_tree(T);
		copy_tree.InorderTraverse(v<int, char>());
		cout << endl;
		copy_tree.insert(pair<int, char>(80, 'h'));
		copy_tree.InorderTraverse(v<int, char>());

		BSTree<int, pair<const int, char>, KOD2<int, char>, less<int>>::Iterator it = copy_tree.begin();
		BSTree<int, pair<const int, char>, KOD2<int, char>, less<int>>::ConstIterator cit = it;
		

	}*/

}
