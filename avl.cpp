#include "avl.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>
#include <stdio.h>
#include <iomanip>
using namespace std;

int AvlTree::getHeight(AvlNode* tree){  //获取树高 
	if(tree != NULL)                      //如果这个不是空节点就返回该节点的树高 
		return tree->height;
	else
		return 0;                         //如果是空节点就返回0 
} 
int AvlTree::getHeight(){              //外部调用，方便debug 
	return getHeight(root);
} 

AvlNode* AvlTree::find(AvlNode* tree,string name){  //通过循环来找到要查找的值的结点 
	AvlNode* tmp = tree;
	while((tmp != NULL) && (tmp->name != name)){
		if(name < tmp->name)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}
	return tmp;
} 
AvlNode* AvlTree::find(string name){         //外部使用，查找到name的树节点 
	return find(root,name);
}

void AvlTree::inOrder(AvlNode* tree){		//中序 
	if(tree != NULL){
		inOrder(tree->left);
		//cout << tree->name << " ";
		s.push_back( tree->name );
		inOrder(tree->right);
	}
	cout<<endl;
}
void AvlTree::inOrder(){
	inOrder(root);
	int num = s.size();
	for(int i=0;i<num-1;i++){
		if(s[i+1] == root->name)
			remove(s[i]);
	}
}

AvlNode* AvlTree::getMin(AvlNode* tree){   //找到最小值的结点 
	if(tree == NULL)
		return tree;
	while(tree->left != NULL)              //通过循环，找到树的最左下角的结点 
		tree = tree->left;
	return tree;
}
string AvlTree::getMin(){
	AvlNode* tmp = getMin(root);
	if(tmp != NULL)
		return tmp->name;
	else
		return 0;
}

AvlNode* AvlTree::getMax(AvlNode* tree){   //找到最大值的结点 
	if(tree == NULL)
		return tree;
	while(tree->right != NULL)      //通过循环，找到树的最右下角的结点 
		tree = tree->right;
	return tree;
}
string AvlTree::getMax(){
	AvlNode* tmp = getMax(root);
	if(tmp != NULL)
		return tmp->name;
	else
		return 0;
}

void AvlTree::left_left(AvlNode* &tree){ //左旋操作 
	cout << " 左旋前  " << endl;
	display(root,0);
	
	AvlNode* tmp = tree->left;  //tmp为不平衡点的左节点
           	
	tree->left = tmp->right;              //将不平衡点的左节点换成tmp的右节点 
	tmp->right = tree;                    //将左子节点变成当前节点的父节点
	
	tree->height = max(getHeight(tree->left), getHeight(tree->right)) + 1;//更新当前节点的高度	
	tmp->height = max(getHeight(tmp->left), tree->height) + 1;//更新原右子节点高度
	
	tree = tmp;//左节点为新的父节点
	
	cout << " 左旋后  " << endl;
	display(root,0);
}

void AvlTree::right_right(AvlNode* &tree){ //右旋操作 
	cout << " 右旋前  " << endl;
	display(root,0);
	
	AvlNode* tmp = tree->right;  //tmp为不平衡点的右节点	
	
	tree->right = tmp->left;			//将不平衡点的右节点换成tmp的左节点
	tmp->left = tree;					//将右子节点变成当前节点的父节点	
	
	tree->height = max(getHeight(tree->left), getHeight(tree->right)) + 1;//更新当前节点的高度
	tmp->height = max(getHeight(tmp->right), tree->height) + 1;//更新原左子节点高度
	
	tree = tmp; //右节点为新的父节点
	
	cout << " 右旋后  " << endl;
	display(root,0);	
}

void AvlTree::left_right(AvlNode*& tree){ //左右旋操作 	
	cout << " 左右旋前  " << endl;
	display(root,0);
	
	right_right(tree->left);//先进行不平衡点的左节点的右旋操作 
	
	left_left(tree);//然后再进行不平衡点的左旋操作   

	cout << " 左右旋后  " << endl;
	display(root,0);
}

void AvlTree::right_left(AvlNode*& tree){ //右左旋操作 
	 
	cout << " 右左旋前  " << endl;
	display(root,0);
	
	left_left(tree->right);  //先进行不平衡点的右节点的左旋操作 	
	
	right_right(tree);           //然后再进行不平衡点的右旋操作 
	
	cout << " 右左旋后  " << endl;
	display(root,0);
}

AvlNode* AvlTree::insert(AvlNode*& tree, string name, string pw){
	if (tree == NULL){			//递归终止条件，当到Avl树的底部时终止，新建节点
		// 新建节点		
		tree = new AvlNode(name, pw);
		//cout<<tree->height<<" "<<endl;
	}
	else if (name < tree->name){ // 应该将name插入到"tree的左子树"的情况
		insert(tree->left,name, pw);//并不是单单的调用函数，而是边调用函数，边设置指针指向
		// 插入节点后，若AVL树失去平衡，则进行相应的调节。
		if (getHeight(tree->left) - getHeight(tree->right) == 2){
			//如果这不平衡点呈现三角形，就进行左右旋，如果是直线型就进行左旋操作
			if (name < tree->left->name)
				left_left(tree);
			else 
				left_right(tree);
		}
	}
	else if (name > tree->name){ // 应该将name插入到"tree的右子树"的情况
		insert(tree->right, name, pw);
		// 插入节点后，若AVL树失去平衡，则进行相应的调节。
		if (getHeight(tree->right) - getHeight(tree->left) == 2){
			//如果这不平衡点呈现三角形，就进行右左旋，如果是直线型就进行右旋操作 
			if (name > tree->right->name)                     
				right_right(tree);
			else 
				right_left(tree);
		}
	}
	else {
	}                 //如果已经存在的name，就报错 
		//cout << "error" << endl;

	tree->height = max(getHeight(tree->left), getHeight(tree->right)) + 1;//配置新节点的高度
	//cout<<tree->name <<" " << tree->height<<" "<<endl;
	return tree;
}


bool AvlTree::insert(string name,string pw){  //外部使用插入函数 
	
	AvlNode* tmp = insert(root,name,pw);                     //先进行插入操作 
	if(tmp == NULL)
		return false;
		
	fstream infile;                       //打开保存文件 
	infile.open("name.txt",ios::out | ios::app);
	infile << name <<" "<< pw <<endl;         //将新插入的节点保存到文件中 
	infile.close();

	return true;
}

AvlNode* AvlTree::remove(AvlNode* &tree,string name){
	if(tree == NULL) 		//如果是空，直接返回 
		return NULL;
	if(name < tree->name){     		//如果插入的值小于该结点的值
		remove(tree->left,name);  		//就往左递归 
		if(getHeight(tree->right) - getHeight(tree->left) == 2){  //如果树出现不平衡 
			if(getHeight(tree->right->left) > getHeight(tree->right->right))//左子树比右子树高
				right_left(tree);              //采用先右旋再左旋操作
			else                                
				right_right(tree);            //反之，采用左旋操作 
		} 
	}
	else if(name > tree->name){  		//如果插入的值大于该结点的值
		remove(tree->right,name); 		//就往右递归
		if(getHeight(tree->left) - getHeight(tree->right) == 2){  //如果树出现不平衡 
			if(getHeight(tree->left->left) < getHeight(tree->left->right)) //左子树比右子树低 
				left_left(tree);           //采用先左旋再右旋操作
			else
				left_right(tree);			//反之，采用右旋操作
		}
	}
	else{                          //找到了要删除的结点 
		if(tree->left != NULL && tree->right != NULL){  //左右结点都不为空的情况 
			if(getHeight(tree->left) > getHeight(tree->right)){    //左子树的高度大于右子树 
				AvlNode* ma = getMax(tree->left);             //先找到左子树中的最大值 
				tree->name = ma->name;
				tree->password = ma->password;                         
				tree->left = remove(tree->left,ma->name);					//交换并删除ma结点 
			} 
			else{                                              //左子树的高度小于右子树 
				AvlNode* mi = getMin(tree->right);             //先找到右子树中的最小值 
				tree->name = mi->name;     
				tree->password = mi->password ;                    
				tree->right = remove(tree->right,mi->name);					//交换并删除mi结点 
			} 
		}
		else{                       //左右只存在一个有子树的情况，将子节点替换删除节点 
			AvlNode* tmp = tree;
			if(tree->left != NULL)
				tree = tree->left;
			else
				tree = tree->right;
			delete tmp;
		}
	}
	if(tree != NULL)
		tree->height = max(getHeight(tree->left),getHeight(tree->right)) + 1;     //更新树高 
		
	return tree;
}
bool AvlTree::remove(string name){
	AvlNode* tmp = remove(root,name);   //先进行删除该节点的操作 
	if(tmp == NULL)
		return false;
		
	save();                           //再保存 
	return true;
}


void AvlTree::clear(AvlNode* &tree){   //通过递归来删除所有的节点 
	if(tree == NULL)
		return ;
	if(tree->left != NULL)
		clear(tree->left);
	if(tree->right != NULL)
		clear(tree->right);
	delete tree;
}
AvlTree::~AvlTree(){              //析构函数，清空树 
	clear(root);
}

AvlNode* AvlTree::change(string name,string pw,string npw){ //修改密码 
	AvlNode* ch = find(name);              //找到该节点 
	if(ch->password == pw){					//先判断密码是否正确 
		ch->password = npw;					//修改密码，再进行保存 
		save();
	}		
	return ch;
}


void AvlTree::display(AvlNode* tree,int layer){  //横向树形打印 
    if(tree == NULL)
        return;
    display(tree->right,layer+1);           //不断递归先打印最右边的节点 
    for(int i = 0;i < layer; i++)      
        cout<<"       ";
    cout << "*" << tree->name << endl;    //按逆中序输出结点，用层深决定结点的左右位置
    cout << endl;
    display(tree->left,layer+1);
}

void AvlTree::display(){                    //外部使用打印函数 
	display(root,0);
}


void AvlTree::save(AvlNode* tree,ofstream &outfile) const{  //保存到文件中
 
	if(tree != NULL){
		save(tree->left,outfile);                             //递归把所有的节点内容都保存到文件中 
		save(tree->right,outfile);
		outfile << tree->name << " " << tree->password <<"\n"; //以空格隔开 
	}
	
}

void AvlTree::save(){	                              //外部使用保存函数，直接保存到"name.txt"文件中 
	ofstream outfile;
	outfile.open("name.txt",ios::out);
	save(root,outfile);
	outfile.close();
}

void AvlTree::getName(AvlTree tree,string file){        //获取文件中的信息，并建立avl树 
	ifstream infile;                               
	infile.open(file,ios::in); 							//打开文件 
	string message;
	if(!infile.is_open()){
		exit(0);
	}
	while(getline(infile,message)){						//按行读取文件 
		string name,pass;
		int pos = message.find(" ");					//通过空格来获取 name 和 password 
		name = message.substr(0,pos);
		pass = message.substr(pos+1);
		tree.insert(root,name,pass);					//将该节点插入到树中 
	}
	infile.close();										//关闭文件 
}


void AvlTree::menu(){                 //主菜单的界面 
	cout << endl;
	cout << "-------------------------------" << endl;
	cout << "-----------选择操作------------" << endl;
	cout << "-------------------------------" << endl;
	cout << "-----------1：登录-------------" << endl;
	cout << "-----------2：添加-------------" << endl;
	cout << "-----------3：退出-------------" << endl;
	cout << "-------------------------------" << endl;
	cout << "-------------------------------" << endl;
	cout << endl;
}

void AvlTree::menus(){              //登录成功后的界面 
	cout << endl;
	cout << "-------------------------------" << endl;
	cout << "-----------选择操作------------" << endl;
	cout << "-------------------------------" << endl;
	cout << "---------1：修改密码-----------" << endl;
	cout << "---------2：删除账号-----------" << endl;
	cout << "---------3：打印操作-----------" << endl;
	cout << "---------4：退出操作-----------" << endl;
	cout << "-------------------------------" << endl;
	cout << "-------------------------------" << endl;
	cout << endl;
}





