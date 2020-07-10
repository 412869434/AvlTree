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

int AvlTree::getHeight(AvlNode* tree){  //��ȡ���� 
	if(tree != NULL)                      //���������ǿսڵ�ͷ��ظýڵ������ 
		return tree->height;
	else
		return 0;                         //����ǿսڵ�ͷ���0 
} 
int AvlTree::getHeight(){              //�ⲿ���ã�����debug 
	return getHeight(root);
} 

AvlNode* AvlTree::find(AvlNode* tree,string name){  //ͨ��ѭ�����ҵ�Ҫ���ҵ�ֵ�Ľ�� 
	AvlNode* tmp = tree;
	while((tmp != NULL) && (tmp->name != name)){
		if(name < tmp->name)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}
	return tmp;
} 
AvlNode* AvlTree::find(string name){         //�ⲿʹ�ã����ҵ�name�����ڵ� 
	return find(root,name);
}

void AvlTree::inOrder(AvlNode* tree){		//���� 
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

AvlNode* AvlTree::getMin(AvlNode* tree){   //�ҵ���Сֵ�Ľ�� 
	if(tree == NULL)
		return tree;
	while(tree->left != NULL)              //ͨ��ѭ�����ҵ����������½ǵĽ�� 
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

AvlNode* AvlTree::getMax(AvlNode* tree){   //�ҵ����ֵ�Ľ�� 
	if(tree == NULL)
		return tree;
	while(tree->right != NULL)      //ͨ��ѭ�����ҵ����������½ǵĽ�� 
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

void AvlTree::left_left(AvlNode* &tree){ //�������� 
	cout << " ����ǰ  " << endl;
	display(root,0);
	
	AvlNode* tmp = tree->left;  //tmpΪ��ƽ������ڵ�
           	
	tree->left = tmp->right;              //����ƽ������ڵ㻻��tmp���ҽڵ� 
	tmp->right = tree;                    //�����ӽڵ��ɵ�ǰ�ڵ�ĸ��ڵ�
	
	tree->height = max(getHeight(tree->left), getHeight(tree->right)) + 1;//���µ�ǰ�ڵ�ĸ߶�	
	tmp->height = max(getHeight(tmp->left), tree->height) + 1;//����ԭ���ӽڵ�߶�
	
	tree = tmp;//��ڵ�Ϊ�µĸ��ڵ�
	
	cout << " ������  " << endl;
	display(root,0);
}

void AvlTree::right_right(AvlNode* &tree){ //�������� 
	cout << " ����ǰ  " << endl;
	display(root,0);
	
	AvlNode* tmp = tree->right;  //tmpΪ��ƽ�����ҽڵ�	
	
	tree->right = tmp->left;			//����ƽ�����ҽڵ㻻��tmp����ڵ�
	tmp->left = tree;					//�����ӽڵ��ɵ�ǰ�ڵ�ĸ��ڵ�	
	
	tree->height = max(getHeight(tree->left), getHeight(tree->right)) + 1;//���µ�ǰ�ڵ�ĸ߶�
	tmp->height = max(getHeight(tmp->right), tree->height) + 1;//����ԭ���ӽڵ�߶�
	
	tree = tmp; //�ҽڵ�Ϊ�µĸ��ڵ�
	
	cout << " ������  " << endl;
	display(root,0);	
}

void AvlTree::left_right(AvlNode*& tree){ //���������� 	
	cout << " ������ǰ  " << endl;
	display(root,0);
	
	right_right(tree->left);//�Ƚ��в�ƽ������ڵ���������� 
	
	left_left(tree);//Ȼ���ٽ��в�ƽ������������   

	cout << " ��������  " << endl;
	display(root,0);
}

void AvlTree::right_left(AvlNode*& tree){ //���������� 
	 
	cout << " ������ǰ  " << endl;
	display(root,0);
	
	left_left(tree->right);  //�Ƚ��в�ƽ�����ҽڵ���������� 	
	
	right_right(tree);           //Ȼ���ٽ��в�ƽ������������ 
	
	cout << " ��������  " << endl;
	display(root,0);
}

AvlNode* AvlTree::insert(AvlNode*& tree, string name, string pw){
	if (tree == NULL){			//�ݹ���ֹ����������Avl���ĵײ�ʱ��ֹ���½��ڵ�
		// �½��ڵ�		
		tree = new AvlNode(name, pw);
		//cout<<tree->height<<" "<<endl;
	}
	else if (name < tree->name){ // Ӧ�ý�name���뵽"tree��������"�����
		insert(tree->left,name, pw);//�����ǵ����ĵ��ú��������Ǳߵ��ú�����������ָ��ָ��
		// ����ڵ����AVL��ʧȥƽ�⣬�������Ӧ�ĵ��ڡ�
		if (getHeight(tree->left) - getHeight(tree->right) == 2){
			//����ⲻƽ�����������Σ��ͽ����������������ֱ���;ͽ�����������
			if (name < tree->left->name)
				left_left(tree);
			else 
				left_right(tree);
		}
	}
	else if (name > tree->name){ // Ӧ�ý�name���뵽"tree��������"�����
		insert(tree->right, name, pw);
		// ����ڵ����AVL��ʧȥƽ�⣬�������Ӧ�ĵ��ڡ�
		if (getHeight(tree->right) - getHeight(tree->left) == 2){
			//����ⲻƽ�����������Σ��ͽ����������������ֱ���;ͽ����������� 
			if (name > tree->right->name)                     
				right_right(tree);
			else 
				right_left(tree);
		}
	}
	else {
	}                 //����Ѿ����ڵ�name���ͱ��� 
		//cout << "error" << endl;

	tree->height = max(getHeight(tree->left), getHeight(tree->right)) + 1;//�����½ڵ�ĸ߶�
	//cout<<tree->name <<" " << tree->height<<" "<<endl;
	return tree;
}


bool AvlTree::insert(string name,string pw){  //�ⲿʹ�ò��뺯�� 
	
	AvlNode* tmp = insert(root,name,pw);                     //�Ƚ��в������ 
	if(tmp == NULL)
		return false;
		
	fstream infile;                       //�򿪱����ļ� 
	infile.open("name.txt",ios::out | ios::app);
	infile << name <<" "<< pw <<endl;         //���²���Ľڵ㱣�浽�ļ��� 
	infile.close();

	return true;
}

AvlNode* AvlTree::remove(AvlNode* &tree,string name){
	if(tree == NULL) 		//����ǿգ�ֱ�ӷ��� 
		return NULL;
	if(name < tree->name){     		//��������ֵС�ڸý���ֵ
		remove(tree->left,name);  		//������ݹ� 
		if(getHeight(tree->right) - getHeight(tree->left) == 2){  //��������ֲ�ƽ�� 
			if(getHeight(tree->right->left) > getHeight(tree->right->right))//����������������
				right_left(tree);              //��������������������
			else                                
				right_right(tree);            //��֮�������������� 
		} 
	}
	else if(name > tree->name){  		//��������ֵ���ڸý���ֵ
		remove(tree->right,name); 		//�����ҵݹ�
		if(getHeight(tree->left) - getHeight(tree->right) == 2){  //��������ֲ�ƽ�� 
			if(getHeight(tree->left->left) < getHeight(tree->left->right)) //���������������� 
				left_left(tree);           //��������������������
			else
				left_right(tree);			//��֮��������������
		}
	}
	else{                          //�ҵ���Ҫɾ���Ľ�� 
		if(tree->left != NULL && tree->right != NULL){  //���ҽ�㶼��Ϊ�յ���� 
			if(getHeight(tree->left) > getHeight(tree->right)){    //�������ĸ߶ȴ��������� 
				AvlNode* ma = getMax(tree->left);             //���ҵ��������е����ֵ 
				tree->name = ma->name;
				tree->password = ma->password;                         
				tree->left = remove(tree->left,ma->name);					//������ɾ��ma��� 
			} 
			else{                                              //�������ĸ߶�С�������� 
				AvlNode* mi = getMin(tree->right);             //���ҵ��������е���Сֵ 
				tree->name = mi->name;     
				tree->password = mi->password ;                    
				tree->right = remove(tree->right,mi->name);					//������ɾ��mi��� 
			} 
		}
		else{                       //����ֻ����һ������������������ӽڵ��滻ɾ���ڵ� 
			AvlNode* tmp = tree;
			if(tree->left != NULL)
				tree = tree->left;
			else
				tree = tree->right;
			delete tmp;
		}
	}
	if(tree != NULL)
		tree->height = max(getHeight(tree->left),getHeight(tree->right)) + 1;     //�������� 
		
	return tree;
}
bool AvlTree::remove(string name){
	AvlNode* tmp = remove(root,name);   //�Ƚ���ɾ���ýڵ�Ĳ��� 
	if(tmp == NULL)
		return false;
		
	save();                           //�ٱ��� 
	return true;
}


void AvlTree::clear(AvlNode* &tree){   //ͨ���ݹ���ɾ�����еĽڵ� 
	if(tree == NULL)
		return ;
	if(tree->left != NULL)
		clear(tree->left);
	if(tree->right != NULL)
		clear(tree->right);
	delete tree;
}
AvlTree::~AvlTree(){              //��������������� 
	clear(root);
}

AvlNode* AvlTree::change(string name,string pw,string npw){ //�޸����� 
	AvlNode* ch = find(name);              //�ҵ��ýڵ� 
	if(ch->password == pw){					//���ж������Ƿ���ȷ 
		ch->password = npw;					//�޸����룬�ٽ��б��� 
		save();
	}		
	return ch;
}


void AvlTree::display(AvlNode* tree,int layer){  //�������δ�ӡ 
    if(tree == NULL)
        return;
    display(tree->right,layer+1);           //���ϵݹ��ȴ�ӡ���ұߵĽڵ� 
    for(int i = 0;i < layer; i++)      
        cout<<"       ";
    cout << "*" << tree->name << endl;    //�������������㣬�ò��������������λ��
    cout << endl;
    display(tree->left,layer+1);
}

void AvlTree::display(){                    //�ⲿʹ�ô�ӡ���� 
	display(root,0);
}


void AvlTree::save(AvlNode* tree,ofstream &outfile) const{  //���浽�ļ���
 
	if(tree != NULL){
		save(tree->left,outfile);                             //�ݹ�����еĽڵ����ݶ����浽�ļ��� 
		save(tree->right,outfile);
		outfile << tree->name << " " << tree->password <<"\n"; //�Կո���� 
	}
	
}

void AvlTree::save(){	                              //�ⲿʹ�ñ��溯����ֱ�ӱ��浽"name.txt"�ļ��� 
	ofstream outfile;
	outfile.open("name.txt",ios::out);
	save(root,outfile);
	outfile.close();
}

void AvlTree::getName(AvlTree tree,string file){        //��ȡ�ļ��е���Ϣ��������avl�� 
	ifstream infile;                               
	infile.open(file,ios::in); 							//���ļ� 
	string message;
	if(!infile.is_open()){
		exit(0);
	}
	while(getline(infile,message)){						//���ж�ȡ�ļ� 
		string name,pass;
		int pos = message.find(" ");					//ͨ���ո�����ȡ name �� password 
		name = message.substr(0,pos);
		pass = message.substr(pos+1);
		tree.insert(root,name,pass);					//���ýڵ���뵽���� 
	}
	infile.close();										//�ر��ļ� 
}


void AvlTree::menu(){                 //���˵��Ľ��� 
	cout << endl;
	cout << "-------------------------------" << endl;
	cout << "-----------ѡ�����------------" << endl;
	cout << "-------------------------------" << endl;
	cout << "-----------1����¼-------------" << endl;
	cout << "-----------2�����-------------" << endl;
	cout << "-----------3���˳�-------------" << endl;
	cout << "-------------------------------" << endl;
	cout << "-------------------------------" << endl;
	cout << endl;
}

void AvlTree::menus(){              //��¼�ɹ���Ľ��� 
	cout << endl;
	cout << "-------------------------------" << endl;
	cout << "-----------ѡ�����------------" << endl;
	cout << "-------------------------------" << endl;
	cout << "---------1���޸�����-----------" << endl;
	cout << "---------2��ɾ���˺�-----------" << endl;
	cout << "---------3����ӡ����-----------" << endl;
	cout << "---------4���˳�����-----------" << endl;
	cout << "-------------------------------" << endl;
	cout << "-------------------------------" << endl;
	cout << endl;
}





