#include<iostream>
#include<string>
#define maxnum 200
using namespace std;

struct person {									//联系人结构体
	string name;
	int age;
	int sex;
	string ph;
	string add;
};

struct book {									//通讯录结构体
	struct person parr[maxnum];					
	int size;									//通讯录中人数
};

void showmenu()									//菜单界面
{
	cout << "1：添加联系人" << endl;
	cout << "2：显示联系人" << endl;
	cout << "3：删除联系人" << endl;
	cout << "4：查找联系人" << endl;
	cout << "5：修改联系人" << endl;
	cout << "6：清空联系人" << endl;
	cout << "0：退出通讯录" << endl;
}

void addperson(person parr[],int *size)				//添加人员功能
{
	if (*size >= maxnum)
	{
		cout << "您的通讯录已满" << endl;
		return;
	}
	cout << "新联系人的姓名为  ";
	cin >> parr[*size].name;
	cout << endl;

	cout << "新联系人的年龄为  ";
	cin >> parr[*size].age;

	while (parr[*size].age < 0)
	{
		cout << "您输入了一个非法数值!" << endl;
		cout << "请再次输入:  ";
		cin >> parr[*size].age;
	}

	cout << endl;

	cout << "新联系人的性别为(1为男性，2为女性)  ";
	cin >> parr[*size].sex;

	while (parr[*size].sex !=1 && parr[*size].sex != 2)
	{
		cout << "您输入了一个非法数值，仅能够输入1或者2！" << endl;
		cout << "请再次输入:  ";
		cin >> parr[*size].sex;
	}

	cout << endl;

	cout << "新联系人的电话号码为  ";
	cin >> parr[*size].ph;
	cout << endl;

	cout << "新联系人的家庭住址为  ";
	cin >> parr[*size].add;
	cout << endl;

	*size = *size + 1;

	cout << "新联系人添加成功!" << endl;
}

void showperson(person parr[],int *size)						//显示联系人功能
{
	if (*size == 0)
	{
		cout << "您的通讯录中目前没有任何联系人。" << endl;
	}
	else
	{
		cout << "序号\t" << "姓名\t" << "年龄\t" << "性别\t" << "电话号码\t" << "家庭住址\t" << endl;
		for (int i = 0; i < *size; i++)
		{
			if (parr[i].sex == 1)
			{
				cout << i+1 << "\t" << parr[i].name << "\t" << parr[i].age << "\t" << "男性\t" << parr[i].ph << "\t\t" << parr[i].add << endl;
			}
			else
			{
				cout << i+1 << "\t" << parr[i].name << "\t" << parr[i].age << "\t" << "女性\t" << parr[i].ph << "\t\t" << parr[i].add << endl;
			}
		}
	}
}

void deleteperson(person parr[], int* size)			//删除联系人功能
{
	string p_person;
	int num0 = 0;						//查找到的人员个数
	int to_delete_num = 0;				//删除命令
	int flag = 0;						//仅查找到一个人时的编号
	string to_delete_phone;				//细化查找方式
	struct person temp_parr[maxnum];		//将查找到的相同的人的所有信息储存进来
	int temp = 0;						//配合上方
	int fa_count = 0;					//没有查找到的次数
	int temp_arr[maxnum] = {};			//将查找到的相同的人的编号储存进来
	int temp_order = 0;					//temp_arr的顺序，用以查找是第几个位置的编号
	cout << "请输入您想要删除的人的姓名:" << endl;
	cin >> p_person;
	for (int j = 0; j < *size; j++)
	{
		if (parr[j].name == p_person)
		{
			if (parr[j].sex == 1)
			{
				cout << j + 1 << "\t" << parr[j].name << "\t" << parr[j].age << "\t" << "男性\t" << parr[j].ph << "\t\t" << parr[j].add << endl;
			}
			else
			{
				cout << j + 1 << "\t" << parr[j].name << "\t" << parr[j].age << "\t" << "女性\t" << parr[j].ph << "\t\t" << parr[j].add << endl;
			}
			num0 = num0 + 1;
			flag = j;
			temp_parr[temp].name = parr[j].name;
			temp_parr[temp].age = parr[j].age;
			temp_parr[temp].sex = parr[j].sex;
			temp_parr[temp].ph = parr[j].ph;
			temp_parr[temp].add = parr[j].add;
			temp_arr[temp] = j;
			temp = temp + 1;
		}
	}
	if (num0 >= 2)
	{
		cout << "找到了相同的人，请输入TA的手机号码来删除TA" << endl;
		cin >> to_delete_phone;
		system("cls");
		for (int m = 0; m < temp; m++)
		{
			if (temp_parr[m].ph == to_delete_phone)
			{
				cout << "查找成功，若要删除TA，请输入0，若要返回菜单，请输入其他键" << endl;
				if (temp_parr[m].sex == 1)
				{
					cout << temp_parr[m].name << "\t" << temp_parr[m].age << "\t" << "男性\t" << temp_parr[m].ph << "\t\t" << temp_parr[m].add << endl;
				}
				else
				{
					cout << temp_parr[m].name << "\t" << temp_parr[m].age << "\t" << "女性\t" << temp_parr[m].ph << "\t\t" << temp_parr[m].add << endl;
				}
				temp_order = m;
			}
			else
			{
				fa_count = fa_count + 1;
			}
		}
		if (fa_count == temp)
		{
			cout << "没有查找到对应的联系人" << endl;
			system("pause");
			system("cls");
		}
		else
		{
			cin >> to_delete_num;
			if (to_delete_num == 0)
			{
				for (int h = temp_arr[temp_order]; h < *size; h++)
				{
					parr[h].name = parr[h + 1].name;
					parr[h].age = parr[h + 1].age;
					parr[h].sex = parr[h + 1].sex;
					parr[h].ph = parr[h + 1].ph;
					parr[h].add = parr[h + 1].add;
				}
				cout << "删除成功" << endl;
				*size = *size - 1;
			}
			else
			{
				system("pause");
				system("cls");
			}
		}
	}
	else if (num0 ==1)
	{
		cout << "查找成功，请问您是否要删除TA？" << endl;
		cout << "若要删除TA，请输入0，若要返回菜单，请输入其他任意键" << endl;
		cin >> to_delete_num;
		if (to_delete_num == 0)
		{
			for (int k = flag; k < *size; k++)
			{
				parr[k].name = parr[k + 1].name;
				parr[k].age = parr[k + 1].age;
				parr[k].sex = parr[k + 1].sex;
				parr[k].ph = parr[k + 1].ph;
				parr[k].add = parr[k + 1].add;
			}
			cout << "删除成功" << endl;
			*size = *size - 1;
		}
		else
		{
			system("pause");
			system("cls");
		}
	}
	else
	{
		cout << "没有找到对应的联系人" << endl;
		system("pause");
		system("cls");
	}
}

void searchperson(person parr[], int* size)				//查找联系人功能
{
	string s_number;
	string name_person;
	int chosen_method = 0;
	int stop_num = 0;
	int check = 0;
	cout << "若要通过人名查找，请输入0。若要通过电话号码查找，请输入1。若要返回菜单，请输入其他键。" << endl;
	cin >> chosen_method;
	if (chosen_method == 0)
	{
		cout << "请输入所要查找的联系人的姓名:" << endl;
		cin >> name_person;
		for (int n = 0;n < *size;n++)
		{
			if (name_person == parr[n].name)
			{
				if (parr[n].sex == 1)
				{
					cout << n + 1 << "\t" << parr[n].name << "\t" << parr[n].age << "\t" << "男性\t" << parr[n].ph << "\t\t" << parr[n].add << endl;
				}
				else
				{
					cout << n + 1 << "\t" << parr[n].name << "\t" << parr[n].age << "\t" << "女性\t" << parr[n].ph << "\t\t" << parr[n].add << endl;
				}
				check = check + 1;
			}
		}
		if (check >= 1)
		{
			cout << "查找成功！" << endl;
		}
		else
		{
			cout << "没有找到相应的联系人。" << endl;
		}
		cout << "若要返回菜单，请输入0。" << endl;
		cin >> stop_num;
		if (stop_num==0)
		{
			system("pause");
			system("cls");
		}
		else
		{
			cout << "若要返回菜单，请输入0。" << endl;
		}
	}
	else if (chosen_method == 1)
	{
		cout << "请输入所要查找的联系人的电话号码：" << endl;
		cin >> s_number;
		for (int a = 0;a < *size;a++)
		{
			if (s_number == parr[a].ph)
			{
				if (parr[a].sex == 1)
				{
					cout << a + 1 << "\t" << parr[a].name << "\t" << parr[a].age << "\t" << "男性\t" << parr[a].ph << "\t\t" << parr[a].add << endl;
				}
				else
				{
					cout << a + 1 << "\t" << parr[a].name << "\t" << parr[a].age << "\t" << "女性\t" << parr[a].ph << "\t\t" << parr[a].add << endl;
				}
				check = check + 1;
			}
		}
		if (check >= 1)
		{
			cout << "查找成功！" << endl;
		}
		else
		{
			cout << "没有找到相应的联系人。" << endl;
		}
		cout << "若要返回菜单，请输入0。" << endl;
		cin >> stop_num;
		if (stop_num == 0)
		{
			system("pause");
			system("cls");
		}
		else
		{
			cout << "若要返回菜单，请输入0。" << endl;
		}
	}
	else
	{
		cout << "请输入正确的数字！" << endl;
		system("pause");
		system("cls");
	}
}

void changeperson(person parr[], int* size)
{
	string c_person;
	int com_num0 = 0;
	int c_flag = 0;
	int temp_c_arr[maxnum] = {};
	cout << "请输入您想要修改的联系人的姓名:" << endl;
	cin >> c_person;
	for (int b = 0; b < *size; b++)
	{
		if (c_person == parr[b].name)
		{
			if (parr[b].sex == 1)
			{
				cout << "编号: " << "\t" << com_num0 + 1 << b + 1 << "\t" << parr[b].name << "\t" << parr[b].age << "\t" << "男性\t" << parr[b].ph << "\t\t" << parr[b].add << endl;
			}
			else
			{
				cout << "编号: " << "\t" << com_num0 + 1 << b + 1 << "\t" << parr[b].name << "\t" << parr[b].age << "\t" << "女性\t" << parr[b].ph << "\t\t" << parr[b].add << endl;
			}
			temp_c_arr[com_num0] = b;
			com_num0 = com_num0 + 1;
			c_flag = b;
		}
	}
	if (com_num0 == 0)
	{
		cout << "没有查找到对应的联系人。" << endl;
		system("pause");
		system("cls");
	}
	else if (com_num0 == 1)
	{
		int chosen = 0;
		cout << "查找到了对应的联系人。" << endl;
		cout << "若要修改此联系人信息，请输入0。" << endl;
		cout << "若要返回菜单，请点击其他键。" << endl;
		cin >> chosen;
		if (chosen == 0)
		{
			cout << "联系人的姓名为  ";
			cin >> parr[c_flag].name;
			cout << endl;

			cout << "联系人的年龄为  ";
			cin >> parr[c_flag].age;

			while (parr[c_flag].age < 0)
			{
				cout << "您输入了一个非法数值!" << endl;
				cout << "请再次输入:  ";
				cin >> parr[c_flag].age;
			}

			cout << endl;

			cout << "联系人的性别为(1为男性，2为女性)  ";
			cin >> parr[c_flag].sex;

			while (parr[c_flag].sex != 1 && parr[c_flag].sex != 2)
			{
				cout << "您输入了一个非法数值，仅能够输入1或者2！" << endl;
				cout << "请再次输入:  ";
				cin >> parr[c_flag].sex;
			}

			cout << endl;

			cout << "联系人的电话号码为  ";
			cin >> parr[c_flag].ph;
			cout << endl;

			cout << "联系人的家庭住址为  ";
			cin >> parr[c_flag].add;
			cout << endl;
		}
		else
		{
			system("pause");
			system("cls");
		}
	}
	else
	{
		int chosen_c_much = 0;
		cout << "查找到了相同的人，请您输入他们的序号来确定要修改的人。" << endl;
		cin >> chosen_c_much;
		if (chosen_c_much>com_num0+2)
		{
			cout << "请输入正确的序号！" << endl;
		}
		else
		{
			cout << "联系人的姓名为  ";
			cin >> parr[temp_c_arr[chosen_c_much-1]].name;
			cout << endl;

			cout << "联系人的年龄为  ";
			cin >> parr[temp_c_arr[chosen_c_much - 1]].age;

			while (parr[temp_c_arr[chosen_c_much - 1]].age < 0)
			{
				cout << "您输入了一个非法数值!" << endl;
				cout << "请再次输入:  ";
				cin >> parr[temp_c_arr[chosen_c_much - 1]].age;
			}

			cout << endl;

			cout << "联系人的性别为(1为男性，2为女性)  ";
			cin >> parr[temp_c_arr[chosen_c_much - 1]].sex;

			while (parr[temp_c_arr[chosen_c_much - 1]].sex != 1 && parr[temp_c_arr[chosen_c_much - 1]].sex != 2)
			{
				cout << "您输入了一个非法数值，仅能够输入1或者2！" << endl;
				cout << "请再次输入:  ";
				cin >> parr[temp_c_arr[chosen_c_much - 1]].sex;
			}

			cout << endl;

			cout << "联系人的电话号码为  ";
			cin >> parr[temp_c_arr[chosen_c_much - 1]].ph;
			cout << endl;

			cout << "联系人的家庭住址为  ";
			cin >> parr[temp_c_arr[chosen_c_much - 1]].add;
			cout << endl;
			cout << "修改成功！" << endl;
		}
	}
}

void clearperson(person parr[], int* size)
{
	int more_cout = 0;
	cout << "警告：这将会清空通讯录中的所有内容，如果您确定要这么做，请再次输入6!" << endl;
	cout << "若要返回菜单，请输入其他键。" << endl;
	cin >> more_cout;
	if (more_cout == 6)
	{
		for (int c = 0;c < *size;c++)
		{
			*size = 0;
			cout << "已清空通讯录！" << endl;
		}
	}
	else
	{
		system("cls");
	}

}
int main()
{
	struct book books;		    //创建通讯录结构体;
	books.size = 0;

	struct person parr[maxnum] = {};

	int select = 0;
	while (true)				//操作完毕后回到menu
	{
		showmenu();
		cin >> select;
		switch (select)
		{
		case 1:
			system("cls");
			addperson(parr, &books.size);
			cout << "当前通讯录中的人员个数为  " << books.size << endl;
			system("pause");
			system("cls");					//清屏操作
			break;
		case 2:
			system("cls");
			showperson(parr, &books.size);
			system("pause");
			system("cls");
			break;
		case 3:
			system("cls");
			deleteperson(parr, &books.size);
			system("pause");
			system("cls");
			break;
		case 4:
			system("cls");
			searchperson(parr, &books.size);
			break;
		case 5:
			system("cls");
			changeperson(parr, &books.size);
			system("pause");
			system("cls");
			break;
		case 6:
			system("cls");
			clearperson(parr, &books.size);
			system("pause");
			system("cls");
			break;
		case 0:
			cout << "Good Luck！" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "请输入正确的数字。" << endl;
			system("pause");
			system("cls");
		}		
	}
	return 0;
}