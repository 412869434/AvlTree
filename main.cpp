#include "avl.cpp"
#include <iostream>
#include <string>
using namespace std;
int main(){
	AvlTree a;						//�½�һ���� 
	 
	string sname,spass;
	a.getName(a,"name.txt");		//��ȡ�ļ��е����� 
	a.menu();						//��ʾ���˵� 
	int num;
	while(cin>>num){				//ѡ��������� 
		if(num == 1){
			cout << " �������˺ţ�" << endl;
			cin >> sname;
			AvlNode* tmp = a.find(sname);
			if(tmp == NULL){
				cout << " ���¼���˺Ų����ڣ�" << endl;
				a.menu();
			}				
			else{
				cout << " ���������룺" << endl;
				cin >> spass;
				if (tmp->password == spass){
					cout << " ��¼�ɹ��� " << endl;
					a.menus();						//��¼�ɹ���������¼��Ĳ˵� 
					int mm;
					cin >> mm;
					if(mm == 1){
						string ren;
						cout << " �����޸ĵ����룺" << endl;
						cin >> ren;
						a.change(sname,spass,ren);
						cout << " �޸ĳɹ��� "<<endl;
					}
					else if(mm == 2){
						if(a.remove(sname))	
							cout << " ɾ���ɹ��� " << endl;
						else
							cout << " error��" <<endl;
					}
					else if(mm == 3){
						a.display();
					} 
					else{
						system("cls");
						a.menu();
					}
				}
				else
					cout << " ������� " << endl;
				a.menu();
			}
		}
		else if(num == 2){
			cout << " ����½����˺ţ�" << endl;
			cin >> sname;
			AvlNode* tmp = a.find(sname);
			if(tmp != NULL){
				cout << " �˺��Ѵ��ڣ� " << endl;				
			}
			else{
				cout << " ���������룺 " << endl;
				cin >> spass;
				if(a.insert(sname,spass))
					cout << " �����ɹ��� " << endl;
			}
			a.menu();
		}
		else{
			return 0;
		}
	}
	
	AvlTree b;
	b.insert("8","1"); 
	b.insert("2","2");
	b.insert("5","3");
	b.insert("1","4");
	b.insert("3","5");
	b.insert("6","6");
	b.insert("9","7");
	b.insert("8","8");
	b.insert("7","9");
	b.insert("13","1");
	b.insert("11","1");
	b.inOrder();
}
