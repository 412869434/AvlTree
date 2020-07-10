#include "avl.cpp"
#include <iostream>
#include <string>
using namespace std;
int main(){
	AvlTree a;						//新建一个树 
	 
	string sname,spass;
	a.getName(a,"name.txt");		//读取文件中的内容 
	a.menu();						//显示主菜单 
	int num;
	while(cin>>num){				//选择操作内容 
		if(num == 1){
			cout << " 请输入账号：" << endl;
			cin >> sname;
			AvlNode* tmp = a.find(sname);
			if(tmp == NULL){
				cout << " 你登录的账号不存在！" << endl;
				a.menu();
			}				
			else{
				cout << " 请输入密码：" << endl;
				cin >> spass;
				if (tmp->password == spass){
					cout << " 登录成功！ " << endl;
					a.menus();						//登录成功，弹出登录后的菜单 
					int mm;
					cin >> mm;
					if(mm == 1){
						string ren;
						cout << " 输入修改的密码：" << endl;
						cin >> ren;
						a.change(sname,spass,ren);
						cout << " 修改成功！ "<<endl;
					}
					else if(mm == 2){
						if(a.remove(sname))	
							cout << " 删除成功！ " << endl;
						else
							cout << " error！" <<endl;
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
					cout << " 密码错误！ " << endl;
				a.menu();
			}
		}
		else if(num == 2){
			cout << " 输出新建的账号：" << endl;
			cin >> sname;
			AvlNode* tmp = a.find(sname);
			if(tmp != NULL){
				cout << " 账号已存在！ " << endl;				
			}
			else{
				cout << " 请输入密码： " << endl;
				cin >> spass;
				if(a.insert(sname,spass))
					cout << " 创建成功！ " << endl;
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
