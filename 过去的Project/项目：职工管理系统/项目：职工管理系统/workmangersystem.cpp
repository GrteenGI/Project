#include "workmangersystem.h"

workmangersystem::workmangersystem()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open())
	{
		cout << "��Ŀǰû��ְ�������ļ�" << endl;
		this->m_Emparr = NULL;
		this->m_Empnum = 0;
		this->m_File_is_empty = true;
		ifs.close();
		return;
	}
	char ch;		//��ȡ�ļ��ĵ����ַ�
	ifs >> ch;
	if (ifs.eof())		//�ж��ļ��Ƿ�Ϊ��
	{
		cout << "����ְ�������ļ�Ϊ��" << endl;
		this->m_Emparr = NULL;
		this->m_Empnum = 0;
		this->m_File_is_empty = true;
		ifs.close();
		return;
	}
	this->m_Empnum = this->get_empnum();
	this->m_Emparr = new Worker * [this->m_Empnum];		//���ٿռ�
	this->m_File_is_empty = false;
	this->update();			//��ʼ��
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

void workmangersystem::showmenu()			//չʾ�˵�
{
	cout << "��ӭʹ��ְ������ϵͳ" << endl;
	cout << "1.����ְ����Ϣ" << endl;
	cout << "2.��ʾְ����Ϣ" << endl;
	cout << "3.ɾ��ְ����Ϣ" << endl;
	cout << "4.�޸�ְ����Ϣ" << endl;
	cout << "5.����ְ����Ϣ" << endl;
	cout << "6.���ձ������" << endl;
	cout << "0.�˳�����ϵͳ" << endl;
	cout << "7.ɾ��������Ϣ" << endl;
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

void workmangersystem::save()				//�����ļ�
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
void workmangersystem::exitsystem()			//�˳�ϵͳ
{
	cout << "��ӭ�´�ʹ�ã�" << endl;
	system("pause");
	exit(0);
}

void workmangersystem::add_emp()			//�����Ա��
{
	int addnum = 0;
	int newsize = 0;		//�µ�����
	
	string ID, DepartID, Name;		//�����Ա����Ϣ
	int Age, choicenum;
	Worker* aim = NULL;

	cout << "���������ְ���������� ";
	cin >> addnum;
	if (addnum > 0)
	{
		newsize = this->m_Empnum + addnum;

		Worker** newspace = new Worker * [newsize];		//����һ��������

		if (this->m_Emparr != NULL)			//��ԭ������ת��������֮��
		{
			for (int i = 0; i < this->m_Empnum; i++)
			{
				newspace[i] = this->m_Emparr[i];
			}
		}

		for (int j = m_Empnum; j < this->m_Empnum + addnum; j++)
		{
			cout << "��������ְ�������:  " << endl;
			cout << "1.��ũ" << endl;
			cout << "2.����" << endl;
			cout << "3.�ܲ�" << endl;
			cin >> choicenum;
			while (1)
			{
				if (choicenum != 1 && choicenum != 2 && choicenum != 3)
				{
					cout << "���벻�Ϸ�������������" << endl;
					cin >> choicenum;
				}
				else
				{
					break;
				}
			}

			cout << "��������ְ���ı�ţ� " << endl;
			cin >> ID;

			cout << "��������ְ���Ĳ��ű��  " << endl;
			cin >> DepartID;

			cout << "��������ְ��������  " << endl;
			cin >> Name;

			cout << "��������ְ��������  " << endl;
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

		cout << "�ɹ����" << addnum << "��Ա����Ϣ��" << endl;
		this->save();
		this->m_File_is_empty = false;			//�ļ���Ϊ��
	}
	else
	{
		cout << "����Ƿ������������룡" << endl;
	}
	system("pause");
	system("cls");
}

void workmangersystem::show_emp()
{
	if (this->m_File_is_empty)
	{
		cout << "�ļ������ڻ����ļ�Ϊ�գ�" << endl;
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
		cout << "�ļ������ڻ����ļ�Ϊ�գ�" << endl;
		system("pause");
		system("cls");
		return;
	}
	else
	{
		string x;
		int choice;
		cout << "����������Ҫɾ����Ա���ı�ţ� ";
		cin >> x;
		if (this->is_exist(x) == -1)
		{
			cout << "�ñ�Ų����ڣ����������룡" << endl;
			system("pause");
			system("cls");
			return;
		}
		else
		{
			cout << "��Ϊ����ѯ���ñ�Ŷ�Ӧ��Ա��" << endl;
			this->m_Emparr[this->is_exist(x)]->showinfo();
			cout << "�����Ҫɾ����Ա���������� 1 ����Ҫȡ���ò����������� 0 " << endl;
			cin >> choice;
			while (1)
			{
				if (choice != 0 && choice != 1)
				{
					cout << "��������Ƿ�������������" << endl;
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
				cout << "��Ա���ѱ�ɾ��" << endl;
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
		cout << "�ļ������ڻ����ļ�Ϊ�գ�" << endl;
		system("pause");
		system("cls");
		return;
	}
	else
	{
		string x;
		int choice;
		cout << "����������Ҫ�޸ĵ�Ա���ı��:  " << endl;
		cin >> x;
		if (this->is_exist(x) == -1)
		{
			cout << "�ñ�Ų����ڣ����������룡" << endl;
			system("pause");
			system("cls");
			return;
		}
		else
		{
			cout << "��Ϊ����ѯ����Ա��" << endl;
			this->m_Emparr[this->is_exist(x)]->showinfo();
			cout << "����Ҫ�޸�TA�������� 1 �������Ҫ�˳��������� 0 " << endl;
			cin >> choice;
			while (1)
			{
				if (choice != 0 && choice != 1)
				{
					cout << "��������Ƿ�������������" << endl;
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
				cout << "�����������Ա������Ϣ" << endl;
				cout << "�������ְ�������:  " << endl;
				cout << "1.��ũ" << endl;
				cout << "2.����" << endl;
				cout << "3.�ܲ�" << endl;
				cin >> choicenum;
				while (1)
				{
					if (choicenum != 1 && choicenum != 2 && choicenum != 3)
					{
						cout << "���벻�Ϸ�������������" << endl;
						cin >> choicenum;
					}
					else
					{
						break;
					}
				}

				cout << "��������ְ���ı�ţ� " << endl;
				cin >> ID;

				cout << "��������ְ���Ĳ��ű��  " << endl;
				cin >> DepartID;

				cout << "��������ְ��������  " << endl;
				cin >> Name;

				cout << "��������ְ��������  " << endl;
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
				cout << "�ɹ��޸ĸ�Ա������Ϣ��" << endl;
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
		cout << "�ļ������ڻ����ļ�Ϊ�գ�" << endl;
		system("pause");
		system("cls");
		return;
	}
	else
	{
		string x;
		int choice;
		cout << "����������Ҫ�޸ĵ�Ա���ı��:  " << endl;
		cin >> x;
		if (this->is_exist(x) == -1)
		{
			cout << "�ñ�Ų����ڣ����������룡" << endl;
			system("pause");
			system("cls");
			return;
		}
		else
		{
			cout << "��Ϊ����ѯ����Ա��" << endl;
			this->m_Emparr[this->is_exist(x)]->showinfo();
			system("pause");
			system("cls");
		}
	}
}

bool cmp_age_up(Worker* a, Worker* b)		//������������
{
	return a->m_Age < b->m_Age;
}

bool cmp_age_down(Worker* a, Worker* b)		//���併������
{
	return a->m_Age > b->m_Age;
}

bool cmp_departid(Worker* a, Worker* b)		//���ű�Ž�������
{
	return a->m_DepartID > b->m_DepartID;
}

bool cmp_id(Worker* a, Worker* b)			//ְ�������������
{
	return a->m_ID < b->m_ID;
}

void workmangersystem::sort_emp()
{
	if (this->m_File_is_empty)
	{
		cout << "�ļ������ڻ����ļ�Ϊ�գ�" << endl;
		system("pause");
		system("cls");
		return;
	}
	else
	{
		int choice;
		int agechoice;
		cout << "����ְ��������������� 1 " << endl;
		cout << "���ղ��ű������������ 2 " << endl;
		cout << "��������������������� 3 " << endl;
		cin >> choice;
		while (1)
		{
			if (choice != 1 && choice != 2 && choice != 3)
			{
				cout << "������Ƿ�������������" << endl;
			}
			else
			{
				break;
			}
		}
		if (choice == 1)
		{
			sort(this->m_Emparr, this->m_Emparr + this->m_Empnum, cmp_id);
			cout << "����ɹ���" << endl;
		}
		else if (choice == 2)
		{
			sort(this->m_Emparr, this->m_Emparr + this->m_Empnum, cmp_departid);
			cout << "����ɹ���" << endl;
		}
		else
		{
			cout << "��Ҫ�����������У������� 1 " << endl;
			cout << "��Ҫ���н������У������� 2 " << endl;
			cin >> agechoice;
			while (1)
			{
				if (agechoice != 1 && agechoice != 2)
				{
					cout << "��������Ƿ�������������" << endl;
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
				cout << "����ɹ���" << endl;
			}
			else
			{
				sort(this->m_Emparr, this->m_Emparr + this->m_Empnum, cmp_age_down);
				cout << "����ɹ���" << endl;
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
		cout << "�ļ������ڻ����ļ�Ϊ�գ�" << endl;
		system("pause");
		system("cls");
		return;
	}
	else
	{
		int choice;
		cout << "�˲�������ɾ��������ϵͳ���������ݣ���ȷ��Ҫ���д˲�����" << endl;
		cout << "��Ҫִ�д˲����������� 1 " << endl;
		cout << "��Ҫ���أ������� 0 " << endl;
		cin >> choice;
		while (1)
		{
			if (choice != 0 && choice != 1)
			{
				cout << "��������Ƿ�������������" << endl;
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
					delete this->m_Emparr[i];				//ɾ�������ÿ��Ԫ�أ����ڶ�����
				}
			}
			delete[]this->m_Emparr;
			this->m_Emparr = NULL;
			this->m_Empnum = 0;
			this->m_File_is_empty = true;
			cout << "ɾ���ɹ���" << endl;
			this->save();
			system("pause");
			system("cls");
		}
	}
}