#include "workmangersystem.h"

workmangersystem::workmangersystem()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open())
	{
		cout << "您目前没有职工管理文件" << endl;
		this->m_Emparr = NULL;
		this->m_Empnum = 0;
		this->m_File_is_empty = true;
		ifs.close();
		return;
	}
	char ch;		//读取文件的单个字符
	ifs >> ch;
	if (ifs.eof())		//判断文件是否为空
	{
		cout << "您的职工管理文件为空" << endl;
		this->m_Emparr = NULL;
		this->m_Empnum = 0;
		this->m_File_is_empty = true;
		ifs.close();
		return;
	}
	this->m_Empnum = this->get_empnum();
	this->m_Emparr = new Worker * [this->m_Empnum];		//开辟空间
	this->m_File_is_empty = false;
	this->update();			//初始化
	ifs.close();
}

workmangersystem::~workmangersystem()
{
	if (this->m_Emparr != NULL)
	{
		delete[]this->m_Emparr;
		this->m_Emparr = NULL;
	}
}

void workmangersystem::showmenu()			//展示菜单
{
	cout << "欢迎使用职工管理系统" << endl;
	cout << "1.增加职工信息" << endl;
	cout << "2.显示职工信息" << endl;
	cout << "3.删除职工信息" << endl;
	cout << "4.修改职工信息" << endl;
	cout << "5.查找职工信息" << endl;
	cout << "6.按照编号排序" << endl;
	cout << "0.退出管理系统" << endl;
	cout << "7.删除所有信息" << endl;
	cout << endl;
}

int workmangersystem::get_empnum()
{
	int num = 0;
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	char buf[1024] = { 0 };
	while (ifs.getline(buf, sizeof(buf)))
	{
		num++;
	}
	ifs.close();
	return num;
}

void workmangersystem::save()				//保存文件
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	for (int i = 0; i < this->m_Empnum; i++)
	{
		ofs << this->m_Emparr[i]->m_ID << " "
			<< this->m_Emparr[i]->m_DepartID << " "
			<< this->m_Emparr[i]->m_Name << " "
			<< this->m_Emparr[i]->m_Age << endl;
	}
	ofs.close();
}

void workmangersystem::update()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	string ID;
	string DepartID;
	string Name;
	int Age;

	int k = 0;
	while (ifs >> ID && ifs >> DepartID && ifs >> Name && ifs >> Age)
	{
		Worker* worker = NULL;
		if (DepartID == "1")
		{
			worker = new NormalWorker(ID, DepartID, Name, Age);
		}
		else if (DepartID == "2")
		{
			worker = new Manger(ID, DepartID, Name, Age);
		}
		else
		{
			worker = new Boss(ID, DepartID, Name, Age);
		}
		this->m_Emparr[k++] = worker;
	}
	ifs.close();
}

int workmangersystem::is_exist(string x)
{
	int a = 0;
	for (int i = 0; i < this->m_Empnum; i++)
	{
		if (this->m_Emparr[i]->m_ID == x)
		{
			a = i;
			return a;
		}
	}
	return -1;
}
void workmangersystem::exitsystem()			//退出系统
{
	cout << "欢迎下次使用！" << endl;
	system("pause");
	exit(0);
}

void workmangersystem::add_emp()			//添加新员工
{
	int addnum = 0;
	int newsize = 0;		//新的人数
	
	string ID, DepartID, Name;		//添加人员的信息
	int Age, choicenum;
	Worker* aim = NULL;

	cout << "请输入添加职工的数量： ";
	cin >> addnum;
	if (addnum > 0)
	{
		newsize = this->m_Empnum + addnum;

		Worker** newspace = new Worker * [newsize];		//开辟一个新数组

		if (this->m_Emparr != NULL)			//将原先数据转到新数组之中
		{
			for (int i = 0; i < this->m_Empnum; i++)
			{
				newspace[i] = this->m_Emparr[i];
			}
		}

		for (int j = m_Empnum; j < this->m_Empnum + addnum; j++)
		{
			cout << "请输入新职工的类别:  " << endl;
			cout << "1.码农" << endl;
			cout << "2.经理" << endl;
			cout << "3.总裁" << endl;
			cin >> choicenum;
			while (1)
			{
				if (choicenum != 1 && choicenum != 2 && choicenum != 3)
				{
					cout << "输入不合法，请重新输入" << endl;
					cin >> choicenum;
				}
				else
				{
					break;
				}
			}

			cout << "请输入新职工的编号： " << endl;
			cin >> ID;

			cout << "请输入新职工的部门编号  " << endl;
			cin >> DepartID;

			cout << "请输入新职工的姓名  " << endl;
			cin >> Name;

			cout << "请输入新职工的年龄  " << endl;
			cin >> Age;

			switch (choicenum)
			{
			case 1:
				aim = new NormalWorker(ID, DepartID, Name, Age);
				break;

			case 2:
				aim = new Manger(ID, DepartID, Name, Age);
				break;

			case 3:
				aim = new Boss(ID, DepartID, Name, Age);
				break;

			default:
				break;
			}
			newspace[j] = aim; 
		}
		delete[] this->m_Emparr;
		this->m_Emparr = newspace;
		this->m_Empnum = newsize;

		cout << "成功添加" << addnum << "名员工信息！" << endl;
		this->save();
		this->m_File_is_empty = false;			//文件不为空
	}
	else
	{
		cout << "输入非法，请重新输入！" << endl;
	}
	system("pause");
	system("cls");
}

void workmangersystem::show_emp()
{
	if (this->m_File_is_empty)
	{
		cout << "文件不存在或者文件为空！" << endl;
		system("pause");
		system("cls");
		return;
	}
	else
	{
		for (int i = 0; i < this->m_Empnum; i++)
		{
			this->m_Emparr[i]->showinfo();
		}
	}
	system("pause");
	system("cls");
}

void workmangersystem::del_emp()
{
	if (this->m_File_is_empty)
	{
		cout << "文件不存在或者文件为空！" << endl;
		system("pause");
		system("cls");
		return;
	}
	else
	{
		string x;
		int choice;
		cout << "请输入您所要删除的员工的编号： ";
		cin >> x;
		if (this->is_exist(x) == -1)
		{
			cout << "该编号不存在，请重新输入！" << endl;
			system("pause");
			system("cls");
			return;
		}
		else
		{
			cout << "已为您查询到该编号对应的员工" << endl;
			this->m_Emparr[this->is_exist(x)]->showinfo();
			cout << "如果您要删除该员工，请输入 1 ，若要取消该操作，则输入 0 " << endl;
			cin >> choice;
			while (1)
			{
				if (choice != 0 && choice != 1)
				{
					cout << "您的输入非法，请重新输入" << endl;
					cin >> choice;
				}
				else
				{
					break;
				}
			}
			if (choice == 0)
			{
				return;
			}
			else
			{
				for (int i = this->is_exist(x); i < this->m_Empnum; i++)
				{
					this->m_Emparr[i] = this->m_Emparr[i + 1];
				}
				this->m_Empnum--;
				cout << "该员工已被删除" << endl;
				this->save();
				system("pause");
				system("cls");
			}
			if (this->m_Empnum == 0)
			{
				this->m_File_is_empty = true;
			}
		}
	}
}

void workmangersystem::change_emp()
{
	if (this->m_File_is_empty)
	{
		cout << "文件不存在或者文件为空！" << endl;
		system("pause");
		system("cls");
		return;
	}
	else
	{
		string x;
		int choice;
		cout << "请输入您想要修改的员工的编号:  " << endl;
		cin >> x;
		if (this->is_exist(x) == -1)
		{
			cout << "该编号不存在，请重新输入！" << endl;
			system("pause");
			system("cls");
			return;
		}
		else
		{
			cout << "已为您查询到该员工" << endl;
			this->m_Emparr[this->is_exist(x)]->showinfo();
			cout << "若您要修改TA，请输入 1 ，如果想要退出，请输入 0 " << endl;
			cin >> choice;
			while (1)
			{
				if (choice != 0 && choice != 1)
				{
					cout << "您的输入非法，请重新输入" << endl;
					cin >> choice;
				}
				else
				{
					break;
				}
			}
			if (choice == 0)
			{
				return;
			}
			else
			{
				string ID, DepartID, Name;	
				int Age, choicenum;
				Worker* aim = NULL;
				cout << "请重新输入该员工的信息" << endl;
				cout << "请输入该职工的类别:  " << endl;
				cout << "1.码农" << endl;
				cout << "2.经理" << endl;
				cout << "3.总裁" << endl;
				cin >> choicenum;
				while (1)
				{
					if (choicenum != 1 && choicenum != 2 && choicenum != 3)
					{
						cout << "输入不合法，请重新输入" << endl;
						cin >> choicenum;
					}
					else
					{
						break;
					}
				}

				cout << "请输入新职工的编号： " << endl;
				cin >> ID;

				cout << "请输入新职工的部门编号  " << endl;
				cin >> DepartID;

				cout << "请输入新职工的姓名  " << endl;
				cin >> Name;

				cout << "请输入新职工的年龄  " << endl;
				cin >> Age;

				switch (choicenum)
				{
				case 1:
					aim = new NormalWorker(ID, DepartID, Name, Age);
					break;

				case 2:
					aim = new Manger(ID, DepartID, Name, Age);
					break;

				case 3:
					aim = new Boss(ID, DepartID, Name, Age);
					break;

				default:
					break;
				}
				this->m_Emparr[this->is_exist(x)] = aim;
				cout << "成功修改该员工的信息！" << endl;
				this->save();
				system("pause");
				system("cls");
			}
		}
	}
}

void workmangersystem::find_emp()
{
	if (this->m_File_is_empty)
	{
		cout << "文件不存在或者文件为空！" << endl;
		system("pause");
		system("cls");
		return;
	}
	else
	{
		string x;
		int choice;
		cout << "请输入您想要修改的员工的编号:  " << endl;
		cin >> x;
		if (this->is_exist(x) == -1)
		{
			cout << "该编号不存在，请重新输入！" << endl;
			system("pause");
			system("cls");
			return;
		}
		else
		{
			cout << "已为您查询到该员工" << endl;
			this->m_Emparr[this->is_exist(x)]->showinfo();
			system("pause");
			system("cls");
		}
	}
}

bool cmp_age_up(Worker* a, Worker* b)		//年龄升序排列
{
	return a->m_Age < b->m_Age;
}

bool cmp_age_down(Worker* a, Worker* b)		//年龄降序排列
{
	return a->m_Age > b->m_Age;
}

bool cmp_departid(Worker* a, Worker* b)		//部门编号降序排列
{
	return a->m_DepartID > b->m_DepartID;
}

bool cmp_id(Worker* a, Worker* b)			//职工编号升序排列
{
	return a->m_ID < b->m_ID;
}

void workmangersystem::sort_emp()
{
	if (this->m_File_is_empty)
	{
		cout << "文件不存在或者文件为空！" << endl;
		system("pause");
		system("cls");
		return;
	}
	else
	{
		int choice;
		int agechoice;
		cout << "按照职工编号排序请输入 1 " << endl;
		cout << "按照部门编号排序请输入 2 " << endl;
		cout << "按照年龄进行排序请输入 3 " << endl;
		cin >> choice;
		while (1)
		{
			if (choice != 1 && choice != 2 && choice != 3)
			{
				cout << "您输入非法，请重新输入" << endl;
			}
			else
			{
				break;
			}
		}
		if (choice == 1)
		{
			sort(this->m_Emparr, this->m_Emparr + this->m_Empnum, cmp_id);
			cout << "排序成功！" << endl;
		}
		else if (choice == 2)
		{
			sort(this->m_Emparr, this->m_Emparr + this->m_Empnum, cmp_departid);
			cout << "排序成功！" << endl;
		}
		else
		{
			cout << "若要进行升序排列，请输入 1 " << endl;
			cout << "若要进行降序排列，请输入 2 " << endl;
			cin >> agechoice;
			while (1)
			{
				if (agechoice != 1 && agechoice != 2)
				{
					cout << "您的输入非法，请重新输入" << endl;
					cin >> agechoice;
				}
				else
				{
					break;
				}
			}
			if (agechoice == 1)
			{
				sort(this->m_Emparr, this->m_Emparr + this->m_Empnum, cmp_age_up);
				cout << "排序成功！" << endl;
			}
			else
			{
				sort(this->m_Emparr, this->m_Emparr + this->m_Empnum, cmp_age_down);
				cout << "排序成功！" << endl;
			}
		}
		this->save();
		system("pause");
		system("cls");
	}
}

void workmangersystem::clear_emp()
{
	if (this->m_File_is_empty)
	{
		cout << "文件不存在或者文件为空！" << endl;
		system("pause");
		system("cls");
		return;
	}
	else
	{
		int choice;
		cout << "此操作将会删除您管理系统中所有数据，您确定要进行此操作？" << endl;
		cout << "若要执行此操作，请输入 1 " << endl;
		cout << "若要返回，请输入 0 " << endl;
		cin >> choice;
		while (1)
		{
			if (choice != 0 && choice != 1)
			{
				cout << "您的输入非法，请重新输入" << endl;
				cin >> choice;
			}
			else
			{
				break;
			}
		}
		if (choice == 0)
		{
			return;
		}
		else
		{
			if (this->m_Emparr != NULL)
			{
				for (int i = 0; i < this->m_Empnum; i++)
				{
					delete this->m_Emparr[i];				//删除数组的每个元素（都在堆区）
				}
			}
			delete[]this->m_Emparr;
			this->m_Emparr = NULL;
			this->m_Empnum = 0;
			this->m_File_is_empty = true;
			cout << "删除成功！" << endl;
			this->save();
			system("pause");
			system("cls");
		}
	}
}