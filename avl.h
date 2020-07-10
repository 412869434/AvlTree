#include <string>
#include <map>
#include <iostream>
#include <vector>
using namespace std;
class AvlNode{  //��� 
public:
	string name;   //�û���
	string password; //���� 
	int height;  //�߶�          
	AvlNode* left = NULL; //��ڵ� 
	AvlNode* right = NULL; //�ҽڵ� 
	AvlNode(string n,string p):
		name(n),password(p),height(0),left(NULL),right(NULL){ } //���캯��	 
};

class AvlTree{
public:                     //public�еĺ����ǹ��ⲿʹ�� 
	AvlTree():root(NULL){ } //���캯�� 
	~AvlTree(); //�������� 
	
	int getHeight();  //��ȡ���� 
	AvlNode* find(string k);  //����ֵΪk�Ľ�� 
	bool insert(string k,string s);  //����ֵΪk�Ľ�� 
	bool remove(string k);  //ɾ��ֵΪk�Ľ�� 
	string getMin();     //������Сֵ 
	string getMax();     //�������ֵ 
	
	void display();		//��ӡ�� 
	AvlNode* change(string n,string s,string p); //�޸����� 
	void save();     //�����˺� 
	void getName(AvlTree tree,string file);   //��ȡ�ļ��е��˺���Ϣ 
	
	void menu();           //�˵� 
	void menus();         //��¼��Ĳ����˵�
	
	void inOrder();  		//���� 
private:                //private�еĺ������ڲ�ʹ�õģ�����ݹ� 
	AvlNode* root;					//���ڵ�
	void clear(AvlNode* &tree);   //ɾ����� 
	int getHeight(AvlNode* tree); //��ȡ�߶� 
	AvlNode* find(AvlNode* tree,string k);  //����ֵΪk�Ľ�� 
	AvlNode* insert(AvlNode* &tree,string k,string s);  //����ֵΪk�Ľ�� 
	AvlNode* remove(AvlNode* &tree,string k);  //ɾ��ֵΪk�Ľ�� 
	
	void print(AvlNode* tree);   //��ӡ��
	void left_left(AvlNode* &tree); //�������� 
	void right_right(AvlNode* &tree); //�������� 
	void left_right(AvlNode* &tree); //���������� 
	void right_left(AvlNode* &tree); //���������� 
	AvlNode* getMin(AvlNode* tree);   //����Сֵ�Ľ�� 
	AvlNode* getMax(AvlNode* tree);   //�����ֵ�Ľ��
	
	void display(AvlNode* tree,int layer); //��ӡ 
	void save(AvlNode* tree,ofstream &outfile) const; //���� 
	void inOrder(AvlNode* tree);   //���� 
	vector <string> s;
};
