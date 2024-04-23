#include <graphics.h>
#include <conio.h>
#include <string>
#include <stdio.h>
#include <iostream>
using namespace std;
#define MAX 1000

typedef struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* leftp) :val(x), left(leftp), right(nullptr) {}
	TreeNode(int x, TreeNode* leftp, TreeNode* rightp) : val(x), left(leftp), right(rightp) {}
}TreeNode;

int monitorsNum = 0;
string temporaryString[MAX];//是储存输入时未转化的数值，例如0代表一个存在节点，null代表创建树时没有这个节点
//这个作用是例如将输入的0，null，0放到temporaryString[0]='0';temporaryString[1]='null';temporaryString[2]='0'
int fMarks = 0;		        //Fmarks是记录该录入节点的位置（footmarks角标）

int dfs(TreeNode* root);
int minCameraCoverNum(TreeNode* root);
void DataEntry();
TreeNode* initTree(int currentDepth);


int main() {
	for (int i = 0; i < MAX; i++) {
		temporaryString[i] = "null";
	}
	DataEntry();
	TreeNode* rt = initTree(0);
	int minCameraNum = minCameraCoverNum(rt);
	cout << minCameraNum << "\n";
	return 0;
}
int dfs(TreeNode* root) {

	// 0 表示没有被监控覆盖
	// 1 表示是监控
	// 2 表示是被监控覆盖

	if (root == nullptr) return 2; // 2 即为被监控覆盖
	// 如果树为空，那么没有节点需要被监视，即所有节点监视成功
	// 如果是树递归到这里的，说明是出度为零的叶子节点的左右孩子指针（nullptr），而因为其实是没有这两个的，也就不需要监控，所以定位为已监控

	int l = dfs(root->left), r = dfs(root->right);

	if (!l || !r) { // 如果有空白
		//(l==0||r==0) 
		//如果子节点的左节点或右节点是0（未被监控的），这里这个身为父节点的节点就需要安装个监控
		monitorsNum++;
		return 1; // 当前设置为监控
	}
	else if (l == 1 || r == 1) { // 1 如果子节点有监控
		//并且没有空白
		//则该节点被监控
		return 2;// 当前设置被监控
	}
	return 0; // 对于没有被安装/监视的点（或者是出度为零的叶子节点（因为叶子结点的左右孩子都是NULLptr，都被监视），此时将叶子节点定位未被监视的也未被安装摄像头的节点）
}
int minCameraCoverNum(TreeNode* root) {
	if (dfs(root) == 0) monitorsNum++;//单节点的树，必须要安装一个
	return monitorsNum;
}
void DataEntry() {
	int curMarks = 0;//curMarks是记录当前节点位置
	string s;
	getline(cin, s);
	s = s.substr(1, s.size() - 2);//将形式输入的那个括号给去了
	string t = "";
	for (int i = 0; i < s.size(); i++) {//将输入的数据按照顺序，依次放入
		if (s[i] == ',') {
			temporaryString[++curMarks] = t;
			t = "";
		}
		else {
			t = t + s[i];
		}
	}
	if (t != "null") {
		temporaryString[++curMarks] = t;
	}

	int ok = 0;
	if (temporaryString[curMarks - 1] != "null") ok += 2;
	if (temporaryString[curMarks] != "null") ok += 2;
	while (ok--)temporaryString[++curMarks] = "null";
}

TreeNode* initTree(int currentDepth) {
	TreeNode* rt = new TreeNode;

	if (currentDepth == 0) {
		// string ss;  cin>>ss;
		string ss;
		ss = temporaryString[++fMarks];
		rt->left = rt->right = NULL;
		if (ss == "nullptr")
			return rt;
	}

	// string s, t;  cin>>s>>t;
	string s, t;
	s = temporaryString[++fMarks];
	t = temporaryString[++fMarks];

	if (s == "null") {
		rt->left = NULL;
	}
	else {
		rt->val = s[0] - '0';
		rt->left = initTree(currentDepth + 1);
	}

	if (t == "null") {
		rt->right = NULL;
	}
	else {
		rt->val = s[0] - '0';
		rt->right = initTree(currentDepth + 1);
	}
	// cout<<dep<<":"<<rt->val<<"\n";
	return rt;
}

//调试
//[0,0,null,0,null,0,null,null,0]
//[0,0,null,0,0]
