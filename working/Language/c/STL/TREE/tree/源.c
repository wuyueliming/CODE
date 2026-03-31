#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>                树                >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  
/*  
一、纯顺序结构（双亲表示法）
	用数组存储：数组的每一个元素都是一个结构体，括号中的是可要可不要的域。
		结构体包含：数值域、父亲域、（长子域）、（右兄弟域）
		1、其中数值域用来存放这个节点的信息，其他的域用来存放对应的双亲/长子/右兄弟在数组中的位置（下标），如果没有则用-1来表示
		
二、纯链表结构（孩子兄弟表示法）
	用链来存储：链树的每一个节点都是一个结构体，括号中的是可要可不要的域。
		节点包含：数值域、长子域、右兄弟域、（双亲域）
		1、其中数值域用来存放这个节点的信息，其他的域用来存放对应的双亲/长子/右兄弟在数组中的位置（地址），如果没有则用NULL来表示

																		

																		总结
							1、这两种表示树的方式本质相同，可以通过添加不同的域来提高搜索、修改时的便捷程度
							2、这两种表示方法本质上也是二叉树，将长子域看作左子树根节点，将右兄弟域看作右子树根节点
*/


/*
三、孩子表示法
	（1）数组+单链表
		数组：用数组存结构体，结构体有数值域、（双亲域）、一个链表指针（长子指针）。
		链表：数组元素的长子指针指向链表的第一个节点（长子节点），每一个节点存放一个数值和右兄弟的地址


	（2）纯链表：每一个节点都有数值域和若干个孩子域，也可以加上双亲域。
		1、孩子域的数量可以统一都用树的度来作为每个节点的孩子域的数量
		2、也可以不统一，在每个节点里面加一个度域来存放该节点的度，然后根据度来确定孩子域的数量。
*/


                                //总之，实现一个树的方法有很多种，其本质都差不多，都是通过双亲域、长子域、兄弟域来确定前后的关系
 

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>               二叉树                >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/*
一、二叉树的分类
	1、斜树：只有左子树或者只有右子树（其实算是一种特殊的单链表，以不同的视角来看待链表）

	2、满二叉树：完全对称，每一个节点都有左子树和右子树（除了叶子），
		（1）叶子只能出现在最下层
		（2）非叶子的度一定是2，否则就缺胳膊少腿了
		（3）在同样深度的二叉树中，满二叉树的结点是最多的
	3、完全二叉树：倒数第二层是一个满二叉树，最下面一层从左到右是连续中间没有空位的。
		（1）叶子结点只能出现在最下面两层
		（2）最下面的叶子一定集中在左部连续位置
		（3）倒数第二层若有叶子结点，一定在右部连续位置
		（4）如果结点的度为1，那么一定是左子树而不是右子树
		（5）同样结点数的二叉树，完全二叉树的深度最小
*/


/*
二、二叉树的性质
	1、二叉树的第i层的结点个数最多为2的i-1次方。

	2、深度为i的二叉树的总结点数最大是2的i次方减1。

	3、叶子结点的度为0，个数为n0。以此类推有n1个度为1的结点，有n2个度为2的结点。那么n0=n2+1。

	4、若一个完全二叉树的结点有n个，那么它的深度为[log2^n]+1

	5、对于结点数为n的完全二叉树，将每个结点从上到下、从左往右编号，那么对于任一结点其号码为i
	(1)如果i==1，那么这个结点就是根结点，没有双亲结点；如果i!=1，那么i/2为它的双亲结点。
	(2)如果2i>n,那么该结点没有左孩子；否则左孩子就是2i
	(3)如果2i+1>n,那么该结点没有右孩子；否则右孩子就是2i+1

*/


/*
三、二叉树的遍历
	1、前序遍历：先访问根结点再访问左右结点
	2、中序遍历：先访问左结点再访问根结点最后访问右结点
	3、后序遍历：先访问左右结点再访问根结点
	4、层序遍历；从上到下，从左到右，一层层遍历
*/
#if 0
typedef int status;
enum {son,thread};
typedef struct TREENODE {
	int Ltag;
	struct TREENODE* left;
	char data;
	struct TREENODE* right;
	int Rtag;
} TREENODE;
typedef TREENODE* TREE;
#define OVERFLOW 0
#define OK 1
TREENODE* pre = NULL;
TREENODE* head;


void PreOrderTraverse(TREENODE* tree);
void InOrderTraverse(TREENODE* tree);
void PostOrderTraverse(TREENODE* tree);

void PreOrderCreate(TREE* tree, char* str) {//按照先序建立二叉树
	static int index=0;
	char ch;
	ch = str[index++];

	if (ch == '#') {
		*tree = NULL;
	}
	else {
		*tree = (TREE)malloc(sizeof(TREENODE));
		if (!*tree) {
			exit(OVERFLOW);
		}
		(*tree)->data = ch;
		(*tree)->Ltag = 0;
		(*tree)->Rtag = 0;
		PreOrderCreate(&(*tree)->left, str);
		PreOrderCreate(&(*tree)->right, str);
	}
}

void AddHeadNode(TREE* tree);
status PreThreading(TREE tree);
status PreThreadTraverse(TREE tree);
status InThreading(TREE tree);
status InThreadTraverse(TREE tree);
status PostThreading(TREE tree);
status PostThreadTraverse(TREE tree);


int main()
{
	TREE tree = (TREE)malloc(sizeof(TREENODE));
	TREENODE* pre = (TREENODE*)malloc(sizeof(TREENODE));

	char str[] = {"AB#D##C##"};
	PreOrderCreate(&tree, str);
	PreOrderTraverse(tree);
	printf("<<<先序\n");
	InOrderTraverse(tree);
	printf("<<<中序\n");
	PostOrderTraverse(tree);
	printf("<<<后序\n");
	printf("-----------------\n");
	
	
	
	/*{
		PreThreading(tree);
		AddHeadNode(&tree);
		PreThreadTraverse(tree);
	}*/
	/*{
		InThreading(tree);
		AddHeadNode(&tree);
		InThreadTraverse(tree);
	}*/
	{
		PostThreading(tree);
		AddHeadNode(&tree);
		//PostThreadTraverse(tree);
	}




	return 0;
}
void PreOrderTraverse(TREENODE* tree) {
	if (tree == NULL) {
		return;
	}
	printf("%c", tree->data);
	PreOrderTraverse(tree->left);
	PreOrderTraverse(tree->right);
}

void InOrderTraverse(TREENODE* tree) {
	if (tree == NULL) {
		return;
	}
	InOrderTraverse(tree->left);
	printf("%c", tree->data);
	InOrderTraverse(tree->right);
}
void PostOrderTraverse(TREENODE* tree) {
	if (tree == NULL) {
		return;
	}
	PostOrderTraverse(tree->left);
	PostOrderTraverse(tree->right);
	printf("%c", tree->data);
}
void AddHeadNode(TREE* tree) {
	head = (TREENODE*)malloc(sizeof(TREENODE));
	head->Ltag = 0;
	head->Rtag = 1;
	head->right = pre;
	head->left = *tree;

	pre->right = head;
	*tree = head;
}
status PreThreading(TREE tree) {
	if (tree) {
		if (!tree->left) {
			tree->Ltag = 1;
			tree->left = pre;
		}
		if (pre && !pre->right) {
			pre->Rtag = 1;
			pre->right = tree;
		}
		pre = tree;
		if (tree->Ltag == 0) {//有可能在上面将左指针指向了前驱，然后这里回到前驱，前驱又回到这里一直死循环
			PreThreading(tree->left);
		}
		if (tree->Rtag == 0) {//遍历中序线索二叉树则不需要，因为中序是一直找左子树直到找到第一个结点之后就一直找右子树或者后继了
			PreThreading(tree->right);
		}
	}
	
}
status PreThreadTraverse(TREE TREE) {
	TREENODE* tree = TREE->left;
	while (tree != head) {
		printf("%c", tree->data);
		while (tree->Ltag == 0) {
			tree = tree->left;
			printf("%c", tree->data);
		}
		while (tree->Rtag == 1 && tree->right != head) {
			tree = tree->right;
			printf("%c", tree->data);
		}
		tree = tree->right;
	}
}
status InThreading(TREE tree) {//中序线索化
	if (tree) {
		InThreading(tree->left);
		if (!tree->left) {
			tree->Ltag = thread;
			tree->left = pre;
		}
		if (pre && !pre->right ) {
			pre->Rtag = thread;
			pre->right = tree;
		}
		pre = tree;
		InThreading(tree->right);
	}

}

status InThreadTraverse(TREE TREE) {//中序遍历
	TREENODE* tree = TREE->left;
	while (tree!=head) {
		while (tree->Ltag == 0) {
			tree = tree->left;
		}
		printf("%c", tree->data);
		while (tree->Rtag == 1 && tree!=head) {
			tree = tree->right;
			printf("%c", tree->data);
		}
		tree = tree->right;
	}
}
status PostThreading(TREE tree) {
	if (tree) {
		PostThreading(tree->left);
		PostThreading(tree->right);
		if (pre && !pre->right) {
			pre->Rtag = 1;
			pre->right = tree;
		}
		if (!tree->left) {
			tree->Ltag = 1;
			tree->left = pre;
		}
		pre = tree;
	}
}
status PostThreadTraverse(TREE TREE) {
	TREENODE* tree = TREE->left;
	while (tree != head) {
		while (tree->Ltag == 0) {
			tree = tree->left;
		}




	}
}



#endif

























//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>               哈夫曼树                >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/*

哈夫曼是一种总权最小的树：总权=每个结点到根的距离*这个结点所占的权




*/














//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>                 刷题                  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>



#if 0
int i, j, k;
void preorder(struct TreeNode* root, int* col) {
	if (!root) {
		return;
	}
	//static int i=0;
	col[i++] = root->val;
	preorder(root->left, col);

	preorder(root->right, col);
}
void inorder(struct TreeNode* root, int* col) {
	if (!root) {
		return;
	}
	//static int j=0;

	inorder(root->left, col);
	col[j++] = root->val;
	inorder(root->right, col);
}
void postorder(struct TreeNode* root, int* col) {
	if (!root) {
		return;
	}
	//static int k=0;
	postorder(root->left, col);
	postorder(root->right, col);
	col[k++] = root->val;
}

int** threeOrders(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
	// write code here
	int** matrix = (int**)malloc(sizeof(int*) * 3);
	for (int i = 0; i < 3; i++) {
		matrix[i] = (int*)malloc(sizeof(int) * 1000000);
	}

	preorder(root, matrix[0]);
	inorder(root, matrix[1]);
	postorder(root, matrix[2]);

	*returnSize = 3;
	int* columns = (int*)malloc(sizeof(int) * 3);
	columns[0] = columns[1] = columns[2] = j;
	*returnColumnSizes = columns;

	return matrix;
}
#endif

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>



#if 0

struct TreeNode {
   int val;
   struct TreeNode *left;
  struct TreeNode *right;
};
 
int devide(int* inorder, int* postorder, int Len, struct TreeNode** root) {
	if (Len == 0) {
		/*
		*root=(struct TreeNode*)malloc(sizeof(struct TreeNode));
		(*root)->val='#';
		(*root)->left=NULL;
		(*root)->right=NULL;
		*/
		return 0;
	}
	
	int rootval = postorder[Len - 1];
	printf("%d", rootval);

	*root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	(*root)->val = rootval;
	(*root)->left = NULL;
	(*root)->right = NULL;


	int* lefttree_in = (int*)malloc(sizeof(int) * 1000);
	int* righttree_in = (int*)malloc(sizeof(int) * 1000);
	int* lefttree_post = (int*)malloc(sizeof(int) * 1000);
	int* righttree_post = (int*)malloc(sizeof(int) * 1000);

	int leftnum = 0;
	int rightnum = 0;

	int sign = 0;
	for (int i = 0; i < Len; i++) { //拿到中序的左子树和右子树
		if (inorder[i] == rootval) {
			sign = 1;
			continue;
		}
		if (!sign) {
			lefttree_in[leftnum++] = inorder[i];
		}
		else {
			righttree_in[rightnum++] = inorder[i];
		}
	}

	for (int i = 0; i < Len - 1;i++) { //拿到后序的左子树和右子树
		if (i < leftnum) {
			lefttree_post[i] = postorder[i];
		}
		else {
			righttree_post[i - leftnum] = postorder[i];
		}
	}

	devide(lefttree_in, lefttree_post, leftnum, &(*root)->left);
	devide(righttree_in, righttree_post, rightnum, &(*root)->right);

	return 1;
}

struct TreeNode* buildTree(int* inorder, int inorderLen, int* postorder, int postorderLen) {
	// write code here
	struct TreeNode* head;
	
	devide(inorder, postorder, inorderLen, &head);
	return head;
}

int main()
{
	int* inorder = (int*)malloc(sizeof(int) * 1000);
	int* postorder = (int*)malloc(sizeof(int) * 1000);

	int inorder_[] = {2,1,4,3,5,};
	int postorder_[] = { 2,4,5,3,1 };
	int inlen = sizeof(inorder_) / sizeof(inorder_[0]);
	int postlen = sizeof(postorder_) / sizeof(postorder_[0]);
	for (int i = 0; i < inlen; i++) {
		inorder[i] = inorder_[i];
		postorder[i] = postorder_[i];
	}


	buildTree(inorder_,inlen, postorder_, postlen);


	return 0;
}



#endif
















//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                   //带有双亲指针的后序线索二叉树及其后序遍历
#if 0
typedef int status;
enum { son, thread };
typedef struct TREENODE {
	int Ltag;
	struct TREENODE* left;
	char data;
	struct TREENODE* parent;
	struct TREENODE* right;
	int Rtag;
} TREENODE;
typedef TREENODE* TREE;
#define OVERFLOW 0
#define OK 1
TREENODE* pre = NULL;
TREENODE* head;




void PreOrderCreate(TREE* tree, char* str) {//按照先序建立二叉树
	static int index = 0;
	char ch;
	ch = str[index++];

	if (ch == '#') {
		*tree = NULL;
	}
	else {
		*tree = (TREE)malloc(sizeof(TREENODE));
		if (!*tree) {
			exit(OVERFLOW);
		}
		(*tree)->data = ch;
		(*tree)->Ltag = 0;
		(*tree)->Rtag = 0;
		PreOrderCreate(&(*tree)->left, str);
		PreOrderCreate(&(*tree)->right, str);
	}
}
void AddHeadNode(TREE* tree);
status PostThreading(TREE tree);
status PostThreadTraverse(TREE tree);

int main()
{
	TREE tree = (TREE)malloc(sizeof(TREENODE));
	TREENODE* pre = (TREENODE*)malloc(sizeof(TREENODE));

	char str[] = { "AB#D##C##" };
	PreOrderCreate(&tree, str);//创建基本的二叉树，双亲结点全都没有初始化
	

	PostOrderTraverse(tree);
	printf("<<<后序\n");
	printf("-----------------\n");


	{
		PostThreading(tree);
		AddHeadNode(&tree);
		//PostThreadTraverse(tree);
	}




	return 0;
}


void AddHeadNode(TREE* tree) {
	head = (TREENODE*)malloc(sizeof(TREENODE));
	head->Ltag = 0;
	head->Rtag = 1;
	head->right = pre;
	head->left = *tree;

	pre->right = head;

	*tree = head;
}

status PostThreading(TREE tree) {
	if (tree) {
		PostThreading(tree->left);
		PostThreading(tree->right);
		if (pre && !pre->right) {
			pre->Rtag = 1;
			pre->right = tree;
		}
		if (!tree->left) {
			tree->Ltag = 1;
			tree->left = pre;
		}
		pre = tree;
	}
}
status PostThreadTraverse(TREE TREE) {
	TREENODE* tree = TREE->left;
	TREENODE* pCur = tree;
	TREENODE* preV = NULL;
	while (pCur != head) {
		while (pCur->Ltag == son && pCur->left!=preV) {//(找到最左边结点)&&(防止死循环)
			pCur = pCur->left;
		}//最左边结点可能有右子树也可能没有。如果没有右子树就循环遍历后继（线索），如果有右子树那么右指针是son而不是线索，直接跳到最后的if语句中，pCur指向右子树
		                                                                                                                         

		while (pCur->Rtag == thread && pCur!=head) {//(如果右指针是线索)&&(当树为左单只时，一直找到了根结点，根结点的右指针为线索且为NULL)
			printf("%c", pCur->data);
			preV = pCur;
			pCur = pCur->right;
		}//退出循环后pCur的右指针为子树而不是线索(除根结点)
		if (pCur == tree && pCur->right==preV) {  //   --> 判断是否为根结点，如果是就访问直接退出；如果不是，就必有右子树，因为线索二叉树的空指针都变成线索了
			printf("%c", pCur->data);                                              //右子树是双亲的前驱，双亲是右子树的后继
			return;                                                                //所以pCur指向双亲时，preV指向pCur的右子树
		}


		while (pCur->right == preV && pCur!=head) {//(上一个循环结束时pCur必有右子树且preV指向这个右子树)&&(右单只时，访问双亲结点直到根结点，根结点的双亲为NULL)
			printf("%c", pCur->data);
			preV = pCur;
			pCur = pCur->parent;
		}//退出循环要么是右单只的特殊情况(必有右子树)，要么就是pCur作为左子树指向双亲结点后，preV是pCur这个双亲结点的左子树而不是右子树了(不一定有右子树)
		if (pCur->Rtag == son && pCur!=head) {//如果没有右子树那么就有右线索，重新进入大循环并直接开始第二个小循环
			pCur = pCur->right;
		}
	}
}

#if 0
void _PostOrder(BinaryTreeNodeThd<T>* pRoot)
{
	BinaryTreeNodeThd<T>* pCur = pRoot;
	BinaryTreeNodeThd<T>* prev = NULL; //保存上一次访问的节点
	while (pCur)
	{
		//找最左边的节点(通过左子树来找)
		while (pCur->_LeftThread == LINK && pCur->_pLeft != prev) //防止陷入死循环(下一次进入这个循环又从Pcur找到最左边的结点)  
		{
			pCur = pCur->_pLeft;
		} //跳出循环的条件：pCur为最左边的节点

		//访问节点的后继
		while (pCur && THREAD == pCur->_RightThread) 
		{
			cout << pCur->_data << " ";
			prev = pCur; //perv记录已经访问过的节点
			pCur = pCur->_pRight;
		}//跳出循环的条件：pCur为空（即左单支情况） 节点有右子树，节点为根节点

		//跳出循环，判断是否为根节点
		if (pCur == pRoot && pCur->_pRight == prev)//如果是根结点，直接访问然后退出
		{
			cout << pCur->_data << " ";
			return;
		}
		//不是根节点，访问当前节点的双亲节点
		while (pCur && pCur->_pRight == prev) // 注意 右单支情况
		{
			cout << pCur->_data << " ";
			prev = pCur;//因为指向了上一个结点，所以while里面是说访问双亲结点直到没有右子树，因为prev就是pcur的右子树
			pCur = pCur->_pParent;
		}

		// 判断根节点是否有右子树
		if (pCur && pCur->_RightThread == LINK)
		{
			pCur = pCur->_pRight;
		}
	}
}
#endif
#endif




















#if 0
typedef struct Node {
	int val;
	struct Node* left;
	int Ltag;
	int Rtag;
	struct Node* parent;
	struct Node* right;
} NODE;
enum{son,thread};
enum{L,R,ROOT};
typedef NODE* TREE;
#define OVERFLOW 0
#define OK 1
NODE* pre = NULL;
typedef struct PRE {
	NODE* prenode;
	int presign;
} PRE;
PRE stack[2024];
PRE preV;
NODE* head;

void PostOrderTraverse(NODE* tree) {
	if (tree == NULL) {
		return;
	}
	PostOrderTraverse(tree->left);
	PostOrderTraverse(tree->right);
	if (tree->parent == NULL) {
		printf("当前结点是%d，无双亲\n",tree->val);
	}
	else {
		printf("当前结点:%d,双亲结点:%d\n", tree->val, tree->parent->val);
	}
}
void AddHeadNode(TREE* tree);
void PostThreading(TREE tree);
void PostThreadTraverse_yeshead(TREE root);
void PostThreadTraverse_nohead(TREE root);
int devide(int* inorder, int* postorder, int Len, NODE** root,int sign);
NODE* buildTree(int* inorder, int inorderLen, int* postorder, int postorderLen);

int main()
{
	/*int inorder_[] = { 2,1,4,3,5, };
	int postorder_[] = { 2,4,5,3,1 };*/
	/*int inorder_[] = { 1,2,3,4,5,6,7,8,9 };
	int postorder_[] = { 1,3,5,4,2,8,9,7,6 };*/
	int inorder_[] = { 2,3,4,1,6,5,10,8,9,7};
	int postorder_[] = {4,3,2,6,10,9,8,7,5,1 };
	
	int inlen = sizeof(inorder_) / sizeof(inorder_[0]);
	int postlen = sizeof(postorder_) / sizeof(postorder_[0]);

	buildTree(inorder_, inlen, postorder_, postlen);
	PostOrderTraverse(head);
	printf("\n---------------------\n");
	{
		PostThreading(head);
		AddHeadNode(&head);
		PostThreadTraverse_yeshead(head);
		//PostThreadTraverse_nohead(head);
	}


	return 0;
}
void PostThreadTraverse_yeshead(TREE head) {//在根节点前加上头结点
	NODE* root = head->left;
	NODE* pCur = head->left;
	NODE* preV = NULL;
	while (pCur != head) {
		while (pCur->Ltag == son && pCur->left != preV) {//(找到最左边的结点)&&(防止反复找最左边的结点进入死循环)
			pCur = pCur->left;
		}//退出循环后，最左边的结点可能有右子树，可能没有。如果没右子树就访问后继，如果有就跳到最后的if遍历右子树

		while (pCur != head && pCur->Rtag == thread  ) {//(循环访问后继直到有右子树)&&(左单只特殊情况->直接遍历完所有结点并退出大循环)
			printf("%d", pCur->val);
			preV = pCur;
			pCur = pCur->right;
		}//要么左单只直接遍历完，要么就不是左单只然后遍历到一个有右子树的结点--->>>后序遍历的原理就是左子树-右子树-双亲结点
		if (pCur == root && pCur->right==preV) {//如果不是左单只直接遍历完，那么就是有右子树的，限定右子树刚才访问过了后再来判断是否为根节点
			printf("%d", pCur->val);
			return;
		}

		while (pCur != head && pCur->right == preV ) {//(循环访问双亲结点直到当前结点不是一个右子树)&&(右单只特殊情况->直接遍历完所有结点并退出大循环)
			printf("%d", pCur->val);
			preV = pCur;
			pCur = pCur->parent;
		}//退出循环时一定是preV是pCur的左子树的情况，preV是一个弯折点。这时pCur的左子树遍历完成，要先遍历右子树之后再来遍历pCur这个双亲结点
		if (pCur != head&&pCur->Rtag == son ) {
			pCur = pCur->right;
		}
	}
}
void PostThreadTraverse_nohead(TREE head) {//根结点前不加头结点
	NODE* root = head;
	NODE* pCur = head;
	NODE* preV = NULL;
	while (pCur) {
		while (pCur->Ltag == son && pCur->left != preV) {//(找到最左边的结点)&&(防止反复找最左边的结点进入死循环)
			pCur = pCur->left;
		}//退出循环后，最左边的结点可能有右子树，可能没有。如果没右子树就访问后继，如果有就跳到最后的if遍历右子树

		while (pCur && pCur->Rtag == thread) {//(左单只特殊情况->直接遍历完所有结点并退出大循环)&&(循环访问后继直到有右子树)
			printf("%d ", pCur->val);
			preV = pCur;
			pCur = pCur->right;
		}//要么左单只直接遍历完，要么就不是左单只然后遍历到一个有右子树的结点--->>>后序遍历的原理就是左子树-右子树-双亲结点
		if (pCur == root && pCur->right == preV) {//如果不是左单只直接遍历完，那么就是有右子树的，限定右子树刚才访问过了后再来判断是否为根节点
			printf("%d ", pCur->val);
			return;
		}

		while (pCur&& pCur->right == preV) {//(右单只特殊情况->直接遍历完所有结点并退出大循环)&&(循环访问双亲结点直到当前结点不是一个右子树)
			printf("%d ", pCur->val);
			preV = pCur;
			pCur = pCur->parent;
		}//退出循环时一定是preV是pCur的左子树的情况，preV是一个弯折点。这时pCur的左子树遍历完成，要先遍历右子树之后再来遍历pCur这个双亲结点
		if (pCur && pCur->Rtag == son) {//注意pCur在&&的前面先判断，不然pCur为空的时候访问pCur->Rtag会出错
			pCur = pCur->right;
		}
	}
}
void AddHeadNode(TREE* tree) {
	NODE* newhead;
	newhead = (NODE*)malloc(sizeof(NODE));
	newhead->Ltag = 0;
	newhead->Rtag = 1;
	newhead->right = pre;//指向后序遍历的最后一个结点
	newhead->left = *tree;//指向根结点

	newhead->parent = NULL;
	(*tree)->parent = newhead;
	
	//pre->right = newhead;<<<---先序和中序线索二叉树可以有这个，因为中序和先序的最后一个结点一定是最右边的一个叶子结点(右指针一定空着，可以用来指向头结点)
	//而后序的最后一个结点一定是整棵树的根结点，右指针不一定是空的，可能有右子树。如果让右指针指向头节点就可能会直接将整棵树的右子树全删掉。
	*tree = newhead;//把头指针指向新的头节点
	newhead = NULL;//废除这个指针
}
void PostThreading(TREE tree) {
	if (tree) {
		PostThreading(tree->left);
		PostThreading(tree->right);
		if (pre && !pre->right) {
			pre->Rtag = 1;
			pre->right = tree;
		}
		if (!tree->left) {
			tree->Ltag = 1;
			tree->left = pre;
		}
		pre = tree;
	}
}

int devide(int* inorder, int* postorder, int Len, NODE** root,int cursign) {
	if (Len == 0) {
		return 0;
	}
	static int top = -1;
	static int first = 1;
	int rootval = postorder[Len - 1];
	*root = (NODE*)malloc(sizeof(NODE));
	if (first) {
		head = *root;//------<<<左子树遍历完后判断当前结点是否为根结点的右结点
		first--;
	}
	(*root)->val = rootval;
	(*root)->left = NULL;
	(*root)->right = NULL;
	(*root)->Ltag = son;
	(*root)->Rtag = son;
	
	if (head->right == *root) {
		(*root)->parent = stack[top].prenode;
		if (cursign == R) {
			top--;
		}
	}
	else {
		if (preV.presign == R) {
			(*root)->parent = preV.prenode;
		}
		else if (preV.presign == L) {
			(*root)->parent = stack[top].prenode;
			if (cursign == R) {
				top--;
			}
		}
		else {
			(*root)->parent = preV.prenode;
		}
	}
	
	int* lefttree_in = (int*)malloc(sizeof(int) * 1000);
	int* righttree_in = (int*)malloc(sizeof(int) * 1000);
	int* lefttree_post = (int*)malloc(sizeof(int) * 1000);
	int* righttree_post = (int*)malloc(sizeof(int) * 1000);
	int leftnum = 0;
	int rightnum = 0;

	int sign = 0;
	for (int i = 0; i < Len; i++) { //拿到中序的左子树和右子树
		if (inorder[i] == rootval) {
			sign = 1;
			continue;
		}
		if (!sign) {
			lefttree_in[leftnum++] = inorder[i];
		}
		else {
			righttree_in[rightnum++] = inorder[i];
		}
	}
	for (int i = 0; i < Len - 1; i++) { //拿到后序的左子树和右子树
		if (i < leftnum) {
			lefttree_post[i] = postorder[i];
		}
		else {
			righttree_post[i - leftnum] = postorder[i];
		}
	}
	if (leftnum != 0 || rightnum != 0) {
		if (cursign == R) {
			preV.prenode = *root;
			preV.presign = cursign;
		}
		else {
			preV.prenode = *root;
			preV.presign = cursign;
			stack[++top] = preV;

		}
	}
	devide(lefttree_in, lefttree_post, leftnum, &(*root)->left,L);
	devide(righttree_in, righttree_post, rightnum, &(*root)->right,R);
	return 1;
}

NODE* buildTree(int* inorder, int inorderLen, int* postorder, int postorderLen) {
	NODE* _head_;
	preV.prenode = NULL;
	preV.presign = ROOT;
	devide(inorder, postorder, inorderLen, &_head_,ROOT);
	return head;
}
#endif






//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                                      //AVL
#if 0

//typedef int ElementType;
//typedef struct AVLNode* Position;
//typedef Position AVLTree; /* AVL树类型 */
//
//struct AVLNode {
//    ElementType Data; /* 结点数据 */
//    AVLTree Left; /* 指向左子树 */
//    AVLTree Right; /* 指向右子树 */
//    int Height; /* 树高 */
//};
//
//int Max(int a, int b) {
//    return a > b ? a : b;
//}
//
//AVLTree SingleLeftRotation(AVLTree A) {
//    /* 注意：A必须有一个左子结点B */
//    /* 将A与B做左单旋，更新A与B的高度，返回新的根结点B */
//    AVLTree B = A->Left;
//    A->Left = B->Right;
//    B->Right = A;
//    A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
//    B->Height = Max(GetHeight(B->Left), A->Height) + 1;
//    return B;
//}
//
//AVLTree DoubleLeftRightRotation(AVLTree A) {
//    /* 注意：A必须有一个左子结点B，且B必须有一个右子结点C */
//    /* 将A、B与C做两次单旋，返回新的根结点C */
//    /* 将B与C做右单旋，C被返回 */
//    A->Left = SingleRightRotation(A->Left);
//    /* 将A与C做左单旋，C被返回 */
//    return SingleLeftRotation(A);
//}
//
//
//AVLTree Insert(AVLTree T, ElementType X) {
//    /* 将X插入AVL树T中，并且返回调整后的AVL树 */
//    if (!T) {
//        /* 若插入空树，则新建包含一个结点的树 */
//        T = (AVLTree)malloc(sizeof(struct AVLNode));//////////////////////////浙大版插入
//        T->Data = X;
//        T->Height = 0;
//        T->Left = T->Right = NULL;
//    } /* if (插入空树) 结束 */
//    else if (X < T->Data) {
//        /* 插入T的左子树 */
//        T->Left = Insert(T->Left, X);
//        /* 如果需要左旋 */
//        if (GetHeight(T->Left) - GetHeight(T->Right) == 2)
//            if (X < T->Left->Data)
//                T = SingleLeftRotation(T); /* 左单旋 */
//            else
//                T = DoubleLeftRightRotation(T); /* 左-右双旋 */
//    } /* else if (插入左子树) 结束 */
//    else if (X > T->Data) {
//        /* 插入T的右子树 */
//        T->Right = Insert(T->Right, X);
//        /* 如果需要右旋 */
//        if (GetHeight(T->Left) - GetHeight(T->Right) == -2)
//            if (X > T->Right->Data)
//                T = SingleRightRotation(T); /* 右单旋 */
//            else
//                T = DoubleRightLeftRotation(T); /* 右-左双旋 */
//    } /* else if (插入右子树) 结束 */
//    /* else X == T->Data，无须插入 */
//    /* 别忘了更新树高 */
//    T->Height = Max(GetHeight(T->Left), GetHeight(T->Right)) + 1;
//
//    return T;
//}

 
#include<stdbool.h>
enum BF { LH = 1, EH = 0, RH = -1 };//  bf为左子树高度减去右子树高度
typedef struct NODE {
	int data;
	struct NODE* left;
	struct NODE* right;
	enum BF bf;
}NODE;
typedef int status;


void L_rotate(NODE** T) {
	NODE* R = (*T)->right;
	(*T)->right = R->left;
	R->left = *T;
	*T = R;
}

void R_rotate(NODE** T) {
	NODE* L = (*T)->left;
	(*T)->left = L->right;
	L->right = *T;
	*T = L;
}

void left_balance(NODE** T) {//在insert中T的左子树比右子树高度超过2时才会调用当前函数，所以T的bf默认为2
	NODE* L = (*T)->left;
	NODE* LR = L->right;
	switch (L->bf) {
	case LH://T本来是左子树高，如果L也是左高就直接右旋
		(*T)->bf = L->bf = EH;//右旋后会平衡
		R_rotate(T);
		break;
	case RH://如果L是右高，就先左旋(以L为根节点的左旋)，让L变成左高，然后再右旋(以T为根节点)
		switch (LR->bf) {
		case LH:
			(*T)->bf = RH;
			L->bf = EH;
			break;
		case EH:
			(*T)->bf = L->bf = EH;//先左旋后右旋后，各个节点的bf值。
			break;
		case RH:
			(*T)->bf = EH;
			L->bf = LH;
			break;
		}
		LR->bf = EH;
		L_rotate(&(*T)->left);
		R_rotate(T);
	}
}

void right_balance(NODE** T) {//bf默认为-2
	NODE* R = (*T)->right;
	NODE* RL = R->left;
	switch (R->bf) {
	case RH:
		(*T)->bf = R->bf = EH;
		L_rotate(T);
		break;
	case LH:
		switch (RL->bf) {
		case RH:
			(*T)->bf = LH;
			R->bf = EH;
			break;
		case EH:
			(*T)->bf = R->bf = EH;
			break;
		case LH:
			(*T)->bf  = EH;
			R->bf = RH;
			break;
		}
		RL->bf = EH;
		R_rotate(&(*T)->right);
		L_rotate(T);
	}
}

status insert_AVL(NODE** T, int x, status* taller) {
	if (!(*T)) {
		*T = (NODE*)malloc(sizeof(NODE));
		(*T)->left = (*T)->right = NULL;
		(*T)->data = x;
		(*T)->bf = EH;
		*taller = true;
	}
	else 
	{
		if ( x == (*T)->data ) {
			*taller = false;
			return false;
		}
		else if (x < (*T)->data){
			if (!insert_AVL(&(*T)->left, x, taller)) {//递归的进入左子树插入
				return false;
			}
			if (*taller) {//插入完了节点后，从递归栈中一层一层的返回，如果树变高了就进入switch
				switch ((*T)->bf) {
				case LH:
					*taller = false;//在这层递归中，如果进入switch说明T的左子树的根节点一定是EH，才能使taller为true，在这一层进入switch，所以*T->left的bf从EH增高
					left_balance(T);//后要么是LH，要么是RH。             如果插入前左高，那么现在bf就会超过2，进入left_balance处理
					break;
				case EH:
					*taller = true;//如果在左子树中插入之前是等高的，那么插入后树就变高
					(*T)->bf = LH;//只有插入前是等高的，插入后树才会变高。
					break;
				case RH:
					*taller = false;//如果插入前右边高，那么现在等高。
					(*T)->bf = EH;
					break;
				}
			}
		}else if (x > (*T)->data){
			if (!insert_AVL(&(*T)->right, x, taller)) {//每一层递归都是比过大小进入不同的if分支语句，知道节点是在
				return false;                    //当前节点的左子树还是右子树中插入的。
			}
			if (*taller) {
				switch ((*T)->bf) {
				case LH:
					*taller = false;
					(*T)->bf = EH;
					break;
				case EH:
					*taller = true;
					(*T)->bf = RH;
					break;
				case RH:
					*taller = false;
					right_balance(T);
					break;
				}
			}
		}
	}
	return true;
}

void in_T(NODE* head)
{
	if (head) {
		in_T(head->left);
		printf("%d ", head->data);
		in_T(head->right);
	}
}

int main()
{
	NODE* head = NULL;
	status taller;
	int a[10] = { 3,2,1,4,5,6,7,10,9,8 };
	for (int i = 0; i < 10; i++) {
		insert_AVL(&head, a[i],&taller);
	}
	in_T(head);
	printf("are you OK?");

	return 0;
}
#endif
     


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 
                                                                         //堆

#if 1
void insert(int* data, int* N, int x) {
	data[++*N] = x;
	if (*N == 1)return;

	int i;
	for (i = *N; i > 1 && x < data[i / 2]; i /= 2) {//大于1的时候进入，等于1说明已经是根节点了，不需要继续比较了
		data[i ] = data[i/2];
	}
	data[i] = x;
}

int delete(int* data, int* N) {//本质上是一个根节点，和它的左右子树(已经是两个堆)。将一个节点和两个堆合成一个堆的过程。
	int min = data[0];
	data[1] = data[*N--];//把根节点和最后一个元素交换，最后一个元素退出堆中。

	int parent = 1;
	int temp = data[parent];
	for (int child = parent * 2; child <= *N; child *= 2) {
		if (child < *N && data[child + 1] < data[child]) {//找到左右子树中较小的那一个
			child++;
		}
		if (temp <= data[child]) {//最小堆，从上往下值是递增的，找到左右子树中较小的那一个之后。如果比进入该循环时的夫节点更大就不用交换
			break;    //将这一个节点的值向上移，然后往下一层去寻找。如果找到比它更小的就break，将开始的parent的值插入到这里。
		}                      //简单来说就是在一个递增的序列向后遍历，找到自己的位置然后插入，思路和直接插入排序几乎一样

		data[parent] = data[child];
		parent = child;
	}
	data[parent] = temp;//退出循环后，parent指向原本的parent现在应该插入的位置


	return min;
}

void  build_heap(int* data, int N) {
 	for (int i = N / 2; i > 0; i--) {
		int parent = i;
		int temp = data[parent];
		for (int child = parent * 2; child <= N; child *= 2) {
			if (child < N && data[child + 1] < data[child]) {//找到左右子树中较小的那一个
				child++;
			}
			if (temp <= data[child]) {//最小堆，从上往下值是递增的，找到左右子树中较小的那一个之后。如果比进入该循环时的夫节点更大就不用交换
				break;    //将这一个节点的值向上移，然后往下一层去寻找。如果找到比它更小的就break，将开始的parent的值插入到这里。
			}                      //简单来说就是在一个递增的序列向后遍历，找到自己的位置然后插入，思路和直接插入排序几乎一样
			
			data[parent] = data[child];
			parent = child;
		}
		data[parent] = temp;//退出循环后，parent指向原本的parent现在应该插入的位置
	}
}


int main()
{
	int n, m;
	scanf("%d %d", &n, &m);

	int* data = (int*)malloc(sizeof(int) * (n + 1));
	int x = 0,cnt=0;
	for (int i = 0; i < n; i++) {
		scanf("%d", &x);
		insert(data, &cnt, x);
	}




	int index = 0;
	for (int i = 0; i < m; i++) {
		scanf("%d", &index);
		while (index) {
			if (index / 2 == 0) {
				printf("%d\n", data[index]);
				break;
			}
			else {
				printf("%d ", data[index]);
				index /= 2;
			}
		}
	}


	return 0;
}

#endif


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                                  //哈夫曼树
#if 0
//
//void insert(DATA* data, int* N, DATA x) {
//	data[++*N] = x;
//	if (*N == 1)return;
//
//	int i;
//	for (i = *N; i > 1 && x.frequency < data[i / 2].frequency; i /= 2) {//大于1的时候进入，等于1说明已经是根节点了，不需要继续比较了
//		data[i] = data[i / 2];
//	}
//	data[i] = x;
//}
//
//DATA delete(DATA* data, int* N) {//本质上是一个根节点，和它的左右子树(已经是两个堆)。将一个节点和两个堆合成一个堆的过程。
//	DATA min = data[1];
//	data[1] = data[(*N)--];//把根节点和最后一个元素交换，最后一个元素退出堆中。
//
//	int parent = 1;
//	DATA temp = data[parent];
//	for (int child = parent * 2; child <= *N; child *= 2) {
//		if (child < *N && data[child + 1].frequency < data[child].frequency) {//找到左右子树中较小的那一个
//			child++;
//		}
//		if (temp.frequency <= data[child].frequency) {//最小堆，从上往下值是递增的，找到左右子树中较小的那一个之后。如果比进入该循环时的夫节点更大就不用交换
//			break;    //将这一个节点的值向上移，然后往下一层去寻找。如果找到比它更小的就break，将开始的parent的值插入到这里。
//		}                      //简单来说就是在一个递增的序列向后遍历，找到自己的位置然后插入，思路和直接插入排序几乎一样
//
//		data[parent] = data[child];
//		parent = child;
//	}
//	data[parent] = temp;//退出循环后，parent指向原本的parent现在应该插入的位置
//
//	return min;
//}
typedef struct TreeNode* HuffmanTree;
struct TreeNode {
	int Weight;
	HuffmanTree Left, Right;
};

HuffmanTree Huffman(MinHeap H)
{
	int i;
	HuffmanTree T;
	BuildMinHeap(H); /* 将H->Elements[]按权值调整为最小堆 */
	for (i = 1; i < H->Size; i++)
	{
		T = malloc(sizeof(struct TreeNode)); /* 建立新结点 */
		T->Left = DeleteMin(H);
		/* 从最小堆中删除一个结点，作为新T的左子结点 */
		T->Right = DeleteMin(H);
		/* 从最小堆中删除一个结点，作为新T的右子结点 */
		T->Weight = T->Left->Weight + T->Right->Weight;
		/* 计算新权值 */
		Insert(H, T); /* 将新T插入最小堆 */
	}
	T = DeleteMin(H);
	return T;
}



int main()
{
	//已经写废了，



	return 0;
}
#endif


#include <stdio.h>
#include<stdlib.h>

typedef struct NODE {
	int index;
	int weight;
	struct NODE* left;
	struct NODE* right;
}NODE;

void insert(NODE** heap, int* N, NODE* x) {
	heap[++(*N)] = x;
	if (*N == 1)return;

	int i;
	for (i = *N; i > 1 && x->weight < heap[i / 2]->weight; i /= 2) {
		heap[i] = heap[i / 2];
	}
	heap[i] = x;
}

NODE* delete(NODE** heap, int* N) {
	NODE* ret = heap[1];
	heap[1] = heap[(*N)--];

	int parent = 1;
	NODE* new = heap[1];
	for (int child = parent * 2; child <= *N; child *= 2) {
		if (child < *N && heap[child + 1]->weight < heap[child]->weight) {//牛客的哈夫曼题
			child++;
		}
		if (heap[child]->weight > new->weight) {
			break;
		}
		heap[parent] = heap[child];
		parent = child;
	}
	heap[parent] = new;

	return ret;
}

NODE* build_tree(NODE** heap, int* size, int type) {
	NODE* p1, * p2;
	while (*size != 1) {
		p1 = delete(heap, size);
		p2 = delete(heap, size);
		NODE* mix = (NODE*)malloc(sizeof(NODE));
		mix->left = p1; mix->right = p2;
		mix->index = 0;
		mix->weight = p1->weight + p2->weight;
		insert(heap, size, mix);
	}
	return heap[*size];
}

int get_codelen(NODE* root, int depth, int index) {
	if (!root) {
		return 0;
	}
	if (root->index == index) {
		return depth;
	}
	int ret1 = get_codelen(root->left, depth + 1, index);
	int ret2 = get_codelen(root->right, depth + 1, index);
	return ret2 > ret1 ? ret2 : ret1;
}

int get_min(NODE* root, int* time, int type) {
	int sum = 0;

	for (int i = 1; i <= type; i++) {
		int times = time[i];
		int length = get_codelen(root, 1, i) - 1;//得到对应节点的层数，len为层数减一
		sum += times * length;
	}
	return sum;
}

int main() {
	int type;
	scanf("%d", &type);

	int* time = (int*)malloc(sizeof(int) * (type + 1));
	for (int i = 1; i <= type; i++) {
		scanf("%d", &time[i]);
	}

	NODE** heap = (NODE**)malloc(sizeof(NODE*));
	int size = 0;
	for (int i = 1; i <= type; i++) {
		NODE* new = (NODE*)malloc(sizeof(NODE));
		new->right = new->left = NULL;
		new->index = i;
		new->weight = time[i];
		insert(heap, &size, new);
	}

	NODE* root = build_tree(heap, &size, type);

	int min = get_min(root, time, type);
	printf("%d", min);

	return 0;
}








































