#pragma once
#include<iostream>
using namespace std;
#include"tree.h"
#include<queue>
#include<stack>

namespace xdh {



	template<class T>
	class BinTree {
	public:
		typedef base_node<T> base_node;
		typedef BinTreeNode<T> node;


		template<class visit>
		struct adaptor {
			bool operator()(node* ptr) {
				visit vst;
				using RetType = decltype(vst(ptr->data));

				if constexpr (std::is_void_v<RetType>) {
					vst(ptr->data);
					return false;
				}
				else {
					return  vst(ptr->data);
				}
			}
		};

		struct print {
			void operator()(T const& e) {
				cout << e << ' ';
			}
		};

		struct del {
			void operator()(node* const& e) {
				delete e;
			}
		};

		struct judge {
			bool operator()(const T& e, bool newbase = false) {
				static T base;
				if (newbase) {
					base = e;
					return true;
				}
				return e == base;
			}
		};



	protected:
		base_node* _root = nullptr;
		size_t _size = 0;

	public:
		BinTree() {
			_root = nullptr;
			_size = 0;
		}
		BinTree(const BinTree& BinT) {
			if (this == &BinT)return;
			_root = nullptr; _size = 0;
			_root = CopyTree(BinT._root);
			_size = BinT._size;
		}
		virtual ~BinTree() {
			clear();
		}
		BinTree& operator=(BinTree BinT) {
			swap(BinT);
			return *this;
		}


		BinTree(const char* s) {
			int pos = 0;
			create_PRE(_root, s, pos);
		}
		BinTree(const vector<T>& inorder, const vector<T>& _order, bool pre) {
			if (pre) {
				create_PREIN(_root, inorder, _order);
			}
			else {
				create_POSTIN(_root, inorder, _order);
			}
		}

		size_t count(const T& key) {
			judge()(key, true);
			return LevelTraverse(judge());
		}

		bool empty() {
			return _size == 0;
		}

		size_t size() {
			return _size;
		}



		void swap(BinTree& BinT) {
			std::swap(*this->_root, BinT._root);
			std::swap(*this->_size, BinT._size);
		}
		void clear() {
			Postorder_Traverse(_root, del());
			_root = nullptr;
			_size = 0;
		}

		/*
		bool operator==(const BinTree<T> & BinT) {
			//判断数据是否相等不是指针是否相等
		}
		bool operator!=(const BinTree<T> & BinT) {
			return !operator==();
		}
		*/

		template<class visit = print>
		size_t PreorderTraverse(visit vst = visit()) {
			return Preorder_Traverse(_root, adaptor<visit>());
		}
		template<class visit = print>
		size_t InorderTraverse(visit vst = visit()) {
			return Inorder_Traverse(_root, adaptor<visit>());
		}
		template<class visit = print>
		size_t PostorderTraverse(visit vst = visit()) {
			return Postorder_Traverse(_root, adaptor<visit>());
		}
		template<class visit = print>//缺省值print不能放在参数里面，因为函数缺省值是给实例化的函数的参数使用的。但是这是
		size_t LevelTraverse(visit vst = visit()) {//函数模板，得先实例化。实例化就要根据给的参数来推导类型再实例化，不给参数
			//就不能推出类型然后实例化，然后使用给的缺省值
			return Level_Traverse(_root, adaptor<visit>());
		}

	protected:
		node* CopyTree(node* root) {
			if (!root)return nullptr;
			node* newnode = new node(*root);

			newnode->left = CopyTree(root->left);
			newnode->right = CopyTree(root->right);
			return newnode;
		}

		template<class visit>
		size_t Level_Traverse(node* root, visit vst) {
			if (!root)return 0;
			queue<node*> q;

			using RetType = decltype(vst(root)); size_t cnt = 0;
			int level = 1;
			q.push(root);
			node* nextlast = root;
			node* lastnode = root;
			node* prenode = nullptr;

			while (!q.empty()) {
				//cout << level << ':';
				node* cur;
				while (prenode != lastnode) {
					cur = q.front();
					q.pop();
					if constexpr (std::is_void_v<RetType>) {
						vst(cur); cnt++;
					}
					else {
						if (vst(cur))cnt++;
					}

					if (cur->left) {
						q.push(cur->left);
						nextlast = cur->left;
					}
					if (cur->right) {
						q.push(cur->right);
						nextlast = cur->right;
					}
					prenode = cur;
				}
				lastnode = nextlast;
				level++;
				//cout << endl;
			}
			return cnt;
		}
		template<class visit>
		void InorderTraverse(node* root, visit vst) {
			if (!root)return;

			InorderTraverse(root->left);
			vst(root);
			InorderTraverse(root->right);
		}
		template<class visit, class node_type = node>
		size_t Inorder_Traverse(node* root, visit vst) {
			stack<node*> stk;//非递归要思考递归时系统的函数栈帧里面本质上保存的是什么？

			using RetType = decltype(vst(root)); size_t cnt = 0;
			node* cur = root;//进入循环遍历以cur为根的树
			while (cur || !stk.empty()) {
				while (cur) {
					stk.push(cur);//保存栈帧
					cur = cur->left;//递归处理左子树——InorderTraverse(root->left);
				}
				//回溯取到根节点，此时左子树已经访问。
				node* top = stk.top();
				stk.pop();
				if constexpr (std::is_void_v<RetType>) {
					vst((node_type*)top); cnt++;
				}
				else {
					if (vst(top))cnt++;
				}

				//递归处理右子树——InorderTraverse(root->right);
				cur = top->right;
			}
			return cnt;
		}
		template<class visit>
		void PreorderTraverse(node* root, visit vst) {
			if (!root)return;

			vst(root);
			PreorderTraverse(root->left);
			PreorderTraverse(root->right);
		}
		template<class visit>
		size_t Preorder_Traverse(node* root, visit vst) {
			stack<node*> stk;

			using RetType = decltype(vst(root)); size_t cnt = 0;
			node* cur = root;
			while (cur || !stk.empty()) {
				while (cur) {
					if constexpr (std::is_void_v<RetType>) {
						vst(cur); cnt++;
					}
					else {
						if (vst(cur))cnt++;
					}

					stk.push(cur);
					cur = cur->left;
				}
				//取到根节点，此时左子树已经访问，根已访问。
				node* top = stk.top();
				stk.pop();

				//循环递归处理右子树
				cur = top->right;
			}
			return cnt;
		}
		template<class visit>
		void PostorderTraverse(node* root, visit vst) {
			if (!root)return;

			PostorderTraverse(root->left);
			PostorderTraverse(root->right);
			vst(root);
		}
		template<class visit>
		size_t Postorder_Traverse(node* root, visit vst) {
			stack<node*> stk;//非递归的核心，注意以下带括号的注释，与递归步骤一一对应

			using RetType = decltype(vst(root)); size_t cnt = 0;
			node* prenode = nullptr;
			node* cur = root;
			while (cur || !stk.empty()) {
				while (cur) {
					stk.push(cur);//保存栈帧
					cur = cur->left;//(递归处理左子树)
				}
				node* top = stk.top();//后序遍历，根要最后访问，现在不能pop。

				//先处理右子树.没有右子树或者刚访问完右子树(访问根节点)
				if (!top->right || prenode == top->right) {
					prenode = top;
					if constexpr (std::is_void_v<RetType>) {
						vst(top); cnt++;
					}
					else {
						if (vst(top))cnt++;
					}
					stk.pop();
				}//还没访问右子树,(递归处理右子树)
				else {
					cur = top->right;
				}
			}
			return cnt;
		}






	private:
		void create_PRE(node*& root, const char* s, int& pos) {
			if (s[pos] == '#') {
				pos++;
				return;
			}
			else {
				root = new node(s[pos++]);
				_size++;

				create_PRE(root->left, s, pos);
				create_PRE(root->right, s, pos);
			}
		}
		void create_PREIN(node*& root, const vector<T>& inorder, const vector<T>& preorder) {
			if (inorder.empty())return;

			size_t size = inorder.size();
			root = new node(preorder[0]); _size++;
			size_t pos;
			for (pos = 0; pos < size; pos++) {
				if (inorder[pos] == root->data)break;
			}
			size_t left_size = pos;
			size_t right_size = size - (pos + 1);

			//注意访问越界，&[pos+size]和&[pos]+size 的区别
			if (left_size > 0)
				create_PREIN(root->left, vector<T>(&inorder[0], &inorder[0] + left_size), vector<T>(&preorder[1], &preorder[1] + left_size));
			if (right_size > 0)
				create_PREIN(root->right, vector<T>(&inorder[pos + 1], &inorder[pos + 1] + right_size), vector<T>(&preorder[pos + 1], &preorder[pos + 1] + right_size));
		}
		void create_POSTIN(node*& root, const vector<T>& inorder, const vector<T>& postorder) {
			if (inorder.empty())return;

			size_t size = inorder.size();
			root = new node(postorder[size - 1]); _size++;
			size_t pos;
			for (pos = 0; pos < size; pos++) {
				if (inorder[pos] == root->data)break;
			}
			size_t left_size = pos;
			size_t right_size = size - (pos + 1);

			if (left_size > 0)
				create_POSTIN(root->left, vector<T>(&inorder[0], &inorder[0] + left_size), vector<T>(&postorder[0], &postorder[0] + left_size));
			if (right_size > 0)
				create_POSTIN(root->right, vector<T>(&inorder[pos + 1], &inorder[pos + 1] + right_size), vector<T>(&postorder[pos], &postorder[pos] + right_size));
		}

	};//类结束

	template<class T>
	void swap(BinTree<T>& BinT1, BinTree<T>& BinT2) {
		BinT1.swap(BinT2);
	}






	void testA1()
	{
		/*char s[] = "abc##de#g##f###";
		xdh::Tree<char> T(s);*/
		vector<int> inorder = { 9,3,15,20,7 };
		vector<int> preorder = { 3,9,20,15,7 };
		vector<int> postorder = { 9,15,7,20,3 };
		//vector<int> tmp(&inorder1[1], &inorder1[1]);

		//xdh::Tree<int> T(inorder, preorder, true);
		xdh::BinTree<int> T(inorder, postorder, false);
		T.LevelTraverse();
	}

	void testA2()
	{
		char s[] = "abc##de#g##f###";
		xdh::BinTree<char> T(s);

		T.LevelTraverse(); cout << endl;
		T.PreorderTraverse(); cout << endl;
		T.InorderTraverse(); cout << endl;
		T.PostorderTraverse(); cout << endl;
		cout << endl;

		xdh::BinTree<char> copyTree(T);

		copyTree.LevelTraverse(); cout << endl;
		copyTree.PreorderTraverse(); cout << endl;
		copyTree.InorderTraverse(); cout << endl;
		copyTree.PostorderTraverse(); cout << endl;

		size_t ret = copyTree.count('b');
		cout << ret;
	}

}