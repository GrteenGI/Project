#include<iostream>
#include<string>
#define maxnum 200
using namespace std;

struct person {									//��ϵ�˽ṹ��
	string name;
	int age;
	int sex;
	string ph;
	string add;
};

struct book {									//ͨѶ¼�ṹ��
	struct person parr[maxnum];					
	int size;									//ͨѶ¼������
};

void showmenu()									//�˵�����
{
	cout << "1�������ϵ��" << endl;
	cout << "2����ʾ��ϵ��" << endl;
	cout << "3��ɾ����ϵ��" << endl;
	cout << "4��������ϵ��" << endl;
	cout << "5���޸���ϵ��" << endl;
	cout << "6�������ϵ��" << endl;
	cout << "0���˳�ͨѶ¼" << endl;
}

void addperson(person parr[],int *size)				//�����Ա����
{
	if (*size >= maxnum)
	{
		cout << "����ͨѶ¼����" << endl;
		return;
	}
	cout << "����ϵ�˵�����Ϊ  ";
	cin >> parr[*size].name;
	cout << endl;

	cout << "����ϵ�˵�����Ϊ  ";
	cin >> parr[*size].age;

	while (parr[*size].age < 0)
	{
		cout << "��������һ���Ƿ���ֵ!" << endl;
		cout << "���ٴ�����:  ";
		cin >> parr[*size].age;
	}

	cout << endl;

	cout << "����ϵ�˵��Ա�Ϊ(1Ϊ���ԣ�2ΪŮ��)  ";
	cin >> parr[*size].sex;

	while (parr[*size].sex !=1 && parr[*size].sex != 2)
	{
		cout << "��������һ���Ƿ���ֵ�����ܹ�����1����2��" << endl;
		cout << "���ٴ�����:  ";
		cin >> parr[*size].sex;
	}

	cout << endl;

	cout << "����ϵ�˵ĵ绰����Ϊ  ";
	cin >> parr[*size].ph;
	cout << endl;

	cout << "����ϵ�˵ļ�ͥסַΪ  ";
	cin >> parr[*size].add;
	cout << endl;

	*size = *size + 1;

	cout << "����ϵ����ӳɹ�!" << endl;
}

void showperson(person parr[],int *size)						//��ʾ��ϵ�˹���
{
	if (*size == 0)
	{
		cout << "����ͨѶ¼��Ŀǰû���κ���ϵ�ˡ�" << endl;
	}
	else
	{
		cout << "���\t" << "����\t" << "����\t" << "�Ա�\t" << "�绰����\t" << "��ͥסַ\t" << endl;
		for (int i = 0; i < *size; i++)
		{
			if (parr[i].sex == 1)
			{
				cout << i+1 << "\t" << parr[i].name << "\t" << parr[i].age << "\t" << "����\t" << parr[i].ph << "\t\t" << parr[i].add << endl;
			}
			else
			{
				cout << i+1 << "\t" << parr[i].name << "\t" << parr[i].age << "\t" << "Ů��\t" << parr[i].ph << "\t\t" << parr[i].add << endl;
			}
		}
	}
}

void deleteperson(person parr[], int* size)			//ɾ����ϵ�˹���
{
	string p_person;
	int num0 = 0;						//���ҵ�����Ա����
	int to_delete_num = 0;				//ɾ������
	int flag = 0;						//�����ҵ�һ����ʱ�ı��
	string to_delete_phone;				//ϸ�����ҷ�ʽ
	struct person temp_parr[maxnum];		//�����ҵ�����ͬ���˵�������Ϣ�������
	int temp = 0;						//����Ϸ�
	int fa_count = 0;					//û�в��ҵ��Ĵ���
	int temp_arr[maxnum] = {};			//�����ҵ�����ͬ���˵ı�Ŵ������
	int temp_order = 0;					//temp_arr��˳�����Բ����ǵڼ���λ�õı��
	cout << "����������Ҫɾ�����˵�����:" << endl;
	cin >> p_person;
	for (int j = 0; j < *size; j++)
	{
		if (parr[j].name == p_person)
		{
			if (parr[j].sex == 1)
			{
				cout << j + 1 << "\t" << parr[j].name << "\t" << parr[j].age << "\t" << "����\t" << parr[j].ph << "\t\t" << parr[j].add << endl;
			}
			else
			{
				cout << j + 1 << "\t" << parr[j].name << "\t" << parr[j].age << "\t" << "Ů��\t" << parr[j].ph << "\t\t" << parr[j].add << endl;
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
		cout << "�ҵ�����ͬ���ˣ�������TA���ֻ�������ɾ��TA" << endl;
		cin >> to_delete_phone;
		system("cls");
		for (int m = 0; m < temp; m++)
		{
			if (temp_parr[m].ph == to_delete_phone)
			{
				cout << "���ҳɹ�����Ҫɾ��TA��������0����Ҫ���ز˵���������������" << endl;
				if (temp_parr[m].sex == 1)
				{
					cout << temp_parr[m].name << "\t" << temp_parr[m].age << "\t" << "����\t" << temp_parr[m].ph << "\t\t" << temp_parr[m].add << endl;
				}
				else
				{
					cout << temp_parr[m].name << "\t" << temp_parr[m].age << "\t" << "Ů��\t" << temp_parr[m].ph << "\t\t" << temp_parr[m].add << endl;
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
			cout << "û�в��ҵ���Ӧ����ϵ��" << endl;
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
				cout << "ɾ���ɹ�" << endl;
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
		cout << "���ҳɹ����������Ƿ�Ҫɾ��TA��" << endl;
		cout << "��Ҫɾ��TA��������0����Ҫ���ز˵������������������" << endl;
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
			cout << "ɾ���ɹ�" << endl;
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
		cout << "û���ҵ���Ӧ����ϵ��" << endl;
		system("pause");
		system("cls");
	}
}

void searchperson(person parr[], int* size)				//������ϵ�˹���
{
	string s_number;
	string name_person;
	int chosen_method = 0;
	int stop_num = 0;
	int check = 0;
	cout << "��Ҫͨ���������ң�������0����Ҫͨ���绰������ң�������1����Ҫ���ز˵�����������������" << endl;
	cin >> chosen_method;
	if (chosen_method == 0)
	{
		cout << "��������Ҫ���ҵ���ϵ�˵�����:" << endl;
		cin >> name_person;
		for (int n = 0;n < *size;n++)
		{
			if (name_person == parr[n].name)
			{
				if (parr[n].sex == 1)
				{
					cout << n + 1 << "\t" << parr[n].name << "\t" << parr[n].age << "\t" << "����\t" << parr[n].ph << "\t\t" << parr[n].add << endl;
				}
				else
				{
					cout << n + 1 << "\t" << parr[n].name << "\t" << parr[n].age << "\t" << "Ů��\t" << parr[n].ph << "\t\t" << parr[n].add << endl;
				}
				check = check + 1;
			}
		}
		if (check >= 1)
		{
			cout << "���ҳɹ���" << endl;
		}
		else
		{
			cout << "û���ҵ���Ӧ����ϵ�ˡ�" << endl;
		}
		cout << "��Ҫ���ز˵���������0��" << endl;
		cin >> stop_num;
		if (stop_num==0)
		{
			system("pause");
			system("cls");
		}
		else
		{
			cout << "��Ҫ���ز˵���������0��" << endl;
		}
	}
	else if (chosen_method == 1)
	{
		cout << "��������Ҫ���ҵ���ϵ�˵ĵ绰���룺" << endl;
		cin >> s_number;
		for (int a = 0;a < *size;a++)
		{
			if (s_number == parr[a].ph)
			{
				if (parr[a].sex == 1)
				{
					cout << a + 1 << "\t" << parr[a].name << "\t" << parr[a].age << "\t" << "����\t" << parr[a].ph << "\t\t" << parr[a].add << endl;
				}
				else
				{
					cout << a + 1 << "\t" << parr[a].name << "\t" << parr[a].age << "\t" << "Ů��\t" << parr[a].ph << "\t\t" << parr[a].add << endl;
				}
				check = check + 1;
			}
		}
		if (check >= 1)
		{
			cout << "���ҳɹ���" << endl;
		}
		else
		{
			cout << "û���ҵ���Ӧ����ϵ�ˡ�" << endl;
		}
		cout << "��Ҫ���ز˵���������0��" << endl;
		cin >> stop_num;
		if (stop_num == 0)
		{
			system("pause");
			system("cls");
		}
		else
		{
			cout << "��Ҫ���ز˵���������0��" << endl;
		}
	}
	else
	{
		cout << "��������ȷ�����֣�" << endl;
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
	cout << "����������Ҫ�޸ĵ���ϵ�˵�����:" << endl;
	cin >> c_person;
	for (int b = 0; b < *size; b++)
	{
		if (c_person == parr[b].name)
		{
			if (parr[b].sex == 1)
			{
				cout << "���: " << "\t" << com_num0 + 1 << b + 1 << "\t" << parr[b].name << "\t" << parr[b].age << "\t" << "����\t" << parr[b].ph << "\t\t" << parr[b].add << endl;
			}
			else
			{
				cout << "���: " << "\t" << com_num0 + 1 << b + 1 << "\t" << parr[b].name << "\t" << parr[b].age << "\t" << "Ů��\t" << parr[b].ph << "\t\t" << parr[b].add << endl;
			}
			temp_c_arr[com_num0] = b;
			com_num0 = com_num0 + 1;
			c_flag = b;
		}
	}
	if (com_num0 == 0)
	{
		cout << "û�в��ҵ���Ӧ����ϵ�ˡ�" << endl;
		system("pause");
		system("cls");
	}
	else if (com_num0 == 1)
	{
		int chosen = 0;
		cout << "���ҵ��˶�Ӧ����ϵ�ˡ�" << endl;
		cout << "��Ҫ�޸Ĵ���ϵ����Ϣ��������0��" << endl;
		cout << "��Ҫ���ز˵���������������" << endl;
		cin >> chosen;
		if (chosen == 0)
		{
			cout << "��ϵ�˵�����Ϊ  ";
			cin >> parr[c_flag].name;
			cout << endl;

			cout << "��ϵ�˵�����Ϊ  ";
			cin >> parr[c_flag].age;

			while (parr[c_flag].age < 0)
			{
				cout << "��������һ���Ƿ���ֵ!" << endl;
				cout << "���ٴ�����:  ";
				cin >> parr[c_flag].age;
			}

			cout << endl;

			cout << "��ϵ�˵��Ա�Ϊ(1Ϊ���ԣ�2ΪŮ��)  ";
			cin >> parr[c_flag].sex;

			while (parr[c_flag].sex != 1 && parr[c_flag].sex != 2)
			{
				cout << "��������һ���Ƿ���ֵ�����ܹ�����1����2��" << endl;
				cout << "���ٴ�����:  ";
				cin >> parr[c_flag].sex;
			}

			cout << endl;

			cout << "��ϵ�˵ĵ绰����Ϊ  ";
			cin >> parr[c_flag].ph;
			cout << endl;

			cout << "��ϵ�˵ļ�ͥסַΪ  ";
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
		cout << "���ҵ�����ͬ���ˣ������������ǵ������ȷ��Ҫ�޸ĵ��ˡ�" << endl;
		cin >> chosen_c_much;
		if (chosen_c_much>com_num0+2)
		{
			cout << "��������ȷ����ţ�" << endl;
		}
		else
		{
			cout << "��ϵ�˵�����Ϊ  ";
			cin >> parr[temp_c_arr[chosen_c_much-1]].name;
			cout << endl;

			cout << "��ϵ�˵�����Ϊ  ";
			cin >> parr[temp_c_arr[chosen_c_much - 1]].age;

			while (parr[temp_c_arr[chosen_c_much - 1]].age < 0)
			{
				cout << "��������һ���Ƿ���ֵ!" << endl;
				cout << "���ٴ�����:  ";
				cin >> parr[temp_c_arr[chosen_c_much - 1]].age;
			}

			cout << endl;

			cout << "��ϵ�˵��Ա�Ϊ(1Ϊ���ԣ�2ΪŮ��)  ";
			cin >> parr[temp_c_arr[chosen_c_much - 1]].sex;

			while (parr[temp_c_arr[chosen_c_much - 1]].sex != 1 && parr[temp_c_arr[chosen_c_much - 1]].sex != 2)
			{
				cout << "��������һ���Ƿ���ֵ�����ܹ�����1����2��" << endl;
				cout << "���ٴ�����:  ";
				cin >> parr[temp_c_arr[chosen_c_much - 1]].sex;
			}

			cout << endl;

			cout << "��ϵ�˵ĵ绰����Ϊ  ";
			cin >> parr[temp_c_arr[chosen_c_much - 1]].ph;
			cout << endl;

			cout << "��ϵ�˵ļ�ͥסַΪ  ";
			cin >> parr[temp_c_arr[chosen_c_much - 1]].add;
			cout << endl;
			cout << "�޸ĳɹ���" << endl;
		}
	}
}

void clearperson(person parr[], int* size)
{
	int more_cout = 0;
	cout << "���棺�⽫�����ͨѶ¼�е��������ݣ������ȷ��Ҫ��ô�������ٴ�����6!" << endl;
	cout << "��Ҫ���ز˵�����������������" << endl;
	cin >> more_cout;
	if (more_cout == 6)
	{
		for (int c = 0;c < *size;c++)
		{
			*size = 0;
			cout << "�����ͨѶ¼��" << endl;
		}
	}
	else
	{
		system("cls");
	}

}
int main()
{
	struct book books;		    //����ͨѶ¼�ṹ��;
	books.size = 0;

	struct person parr[maxnum] = {};

	int select = 0;
	while (true)				//������Ϻ�ص�menu
	{
		showmenu();
		cin >> select;
		switch (select)
		{
		case 1:
			system("cls");
			addperson(parr, &books.size);
			cout << "��ǰͨѶ¼�е���Ա����Ϊ  " << books.size << endl;
			system("pause");
			system("cls");					//��������
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
			cout << "Good Luck��" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "��������ȷ�����֡�" << endl;
			system("pause");
			system("cls");
		}		
	}
	return 0;
}