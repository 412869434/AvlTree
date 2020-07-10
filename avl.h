#include <string>
#include <map>
#include <iostream>
#include <vector>
using namespace std;
class AvlNode{  //结点 
public:
	string name;   //用户名
	string password; //密码 
	int height;  //高度          
	AvlNode* left = NULL; //左节点 
	AvlNode* right = NULL; //右节点 
	AvlNode(string n,string p):
		name(n),password(p),height(0),left(NULL),right(NULL){ } //构造函数	 
};

class AvlTree{
public:                     //public中的函数是供外部使用 
	AvlTree():root(NULL){ } //构造函数 
	~AvlTree(); //析构函数 
	
	int getHeight();  //获取树高 
	AvlNode* find(string k);  //查找值为k的结点 
	bool insert(string k,string s);  //插入值为k的结点 
	bool remove(string k);  //删除值为k的结点 
	string getMin();     //返回最小值 
	string getMax();     //返回最大值 
	
	void display();		//打印树 
	AvlNode* change(string n,string s,string p); //修改密码 
	void save();     //保存账号 
	void getName(AvlTree tree,string file);   //读取文件中的账号信息 
	
	void menu();           //菜单 
	void menus();         //登录后的操作菜单
	
	void inOrder();  		//中序 
private:                //private中的函数是内部使用的，方便递归 
	AvlNode* root;					//根节点
	void clear(AvlNode* &tree);   //删除结点 
	int getHeight(AvlNode* tree); //获取高度 
	AvlNode* find(AvlNode* tree,string k);  //查找值为k的结点 
	AvlNode* insert(AvlNode* &tree,string k,string s);  //插入值为k的结点 
	AvlNode* remove(AvlNode* &tree,string k);  //删除值为k的结点 
	
	void print(AvlNode* tree);   //打印树
	void left_left(AvlNode* &tree); //左旋操作 
	void right_right(AvlNode* &tree); //右旋操作 
	void left_right(AvlNode* &tree); //左右旋操作 
	void right_left(AvlNode* &tree); //右左旋操作 
	AvlNode* getMin(AvlNode* tree);   //找最小值的结点 
	AvlNode* getMax(AvlNode* tree);   //找最大值的结点
	
	void display(AvlNode* tree,int layer); //打印 
	void save(AvlNode* tree,ofstream &outfile) const; //保存 
	void inOrder(AvlNode* tree);   //中序 
	vector <string> s;
};
