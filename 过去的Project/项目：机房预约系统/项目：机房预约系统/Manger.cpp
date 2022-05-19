#include"Manger.h"

Manger::Manger()
{
	this->Read_Login_In();
	this->Read_Login_In_ST();
}

Manger::~Manger()
{

}

void Manger::Show_Register_Menu()
{
	cout << "����Ա��¼��ڣ�" << endl;
	cout << "�������˻���������" << endl;
	cout << endl;
}

void Manger::Manger_main()
{
	string Register_Choice;
	string Password;
	while (1)
	{
		this->Show_Register_Menu();
		cout << endl;
		cout << "�������˺�" << endl;
		cout << "��Ҫ������һ����������0" << endl;
		cin >> Register_Choice;
		if (Register_Choice == "0")
		{
			system("cls");
			break;
		}
		else
		{
			cout << "����������" << endl;
			cin >> Password;
			/*�ҵ�ͨ�����˺��и������˺���ͬ��*/
			if (this->Login_In_List.size() && this->Login_In_List.find(Register_Choice) != Login_In_List.end() && Password == this->Login_In_List.find(Register_Choice)->second.Password)
			{
				cout << "��¼�ɹ���" << endl;
				system("pause");
				system("cls");
				for (int i = 0; i < Register_Choice.length(); i++)			//��¼��ǰϵͳ��¼���˺�
					this->Admin_Number[i] = Register_Choice[i];
				this->Manger_Using_main();
			}
			else
			{
				cout << "�˺Ų����ڻ��������" << endl;
				system("pause");
				system("cls");
			}
		}
	}
}

void Manger::Read_Login_In()			//��ȡ�˺�������ͨ����
{
	ifstream ifs;
	ifs.open(Login_M_A, ios::in);

	string S_L_Account;
	string S_L_Password;
	string Condition;

	while (ifs >> S_L_Account && ifs >> S_L_Password && ifs >> Condition)
	{
		if (Condition == "ͨ��")
		{
			this->Login_In_List.insert(make_pair(S_L_Account, Account_Information(S_L_Account, S_L_Password, Condition)));
		}
	}
	ifs.close();
}

void Manger::Read_Login_In_ST()		//��ȡ����ѧ���ͽ�ʦ���˺�������Ϣ
{
	ifstream ifs;
	ifs.open(Login_S_A, ios::in);

	int Number;
	string S_L_Account;
	string S_L_Password;
	string Condition;

	while (ifs >> Number && ifs >> S_L_Account && ifs >> S_L_Password && ifs >> Condition)
	{
		this->Login_In_List_S.insert(make_pair(Number, Account_Information(S_L_Account, S_L_Password, Condition)));
	}
	ifs.close();

	ifs.open(Login_T_A, ios::in);

	while (ifs >> Number && ifs >> S_L_Account && ifs >> S_L_Password && ifs >> Condition)
	{
		this->Login_In_List_T.insert(make_pair(Number, Account_Information(S_L_Account, S_L_Password, Condition)));
	}
	ifs.close();
}

void Manger::Update_Login_In_S()
{
	ofstream ofs;
	ofs.open(Login_S_A, ios::out);
	for (map<int, Account_Information>::iterator it = this->Login_In_List_S.begin(); it != this->Login_In_List_S.end(); it++)
	{
		ofs << it->first << " " << it->second.Account << " " << it->second.Password << " " << it->second.Condition << endl;
	}
	ofs.close();
}

void Manger::Update_Login_In_T()
{
	ofstream ofs;
	ofs.open(Login_T_A, ios::out);
	for (map<int, Account_Information>::iterator it = this->Login_In_List_T.begin(); it != this->Login_In_List_T.end(); it++)
	{
		ofs << it->first << " " << it->second.Account << " " << it->second.Password << " " << it->second.Condition << endl;
	}
	ofs.close();
}

void Manger::Manger_Using_menu()
{
	cout << "��ӭ����ԤԼϵͳ  ����Ա" << endl;
	cout << "1.�����˺�����" << endl;
	cout << "2.�鿴�˺���Ϣ" << endl;
	cout << "3.�鿴����ԤԼ" << endl;
	cout << "4.�޸Ļ�����Ϣ" << endl;
	cout << "5.չʾ������Ϣ" << endl;
	cout << "0.ע����¼" << endl;
}

void Manger::Manger_Using_main()
{
	string choicenum;
	while (1)
	{
		this->Manger_Using_menu();
		cout << "����������ѡ��" << endl;
		cin >> choicenum;
		if (choicenum == "1")			//�����˺�����
		{
			this->Pass_Account_A();
			system("pause");
			system("cls");
		}
		else if (choicenum == "2")		//�鿴�˺���Ϣ
		{
			this->Show_All_Account();
			system("pause");
			system("cls");
		}
		else if (choicenum == "3")		//�鿴����ԤԼ
		{
			this->Show_All_Apply();
			system("pause");
			system("cls");
		}
		else if (choicenum == "4")			//�޸Ļ�����Ϣ
		{
			this->Change_CI();
			system("pause");
			system("cls");
		}
		else if (choicenum == "5")			//չʾ����������Ϣ
		{
			COS cos;;
			cos.Show_All_CI();
			system("pause");
			system("cls");
		}
		else if (choicenum == "0")			//ע��
		{
			system("cls");
			break;
		}
		else
		{
			cout << "����Ƿ�������������" << endl;
			system("cls");
		}
	}
}

void Manger::Pass_Account_A()			//�����˺�����
{
	int Choice;
	cout << "Ҫ�鿴ѧ���˺����룬������ 1" << endl;
	cout << "Ҫ�鿴��ʦ�˺����룬������ 2" << endl;
	cin >> Choice;
	while (Choice != 1 && Choice != 2)
	{
		cout << "�������벻�Ϸ�������������" << endl;
		cin >> Choice;
	}
	if (Choice == 1)
	{
		this->Pass_Account_A_S();
	}
	else if (Choice == 2)
	{
		this->Pass_Account_A_T();
	}
}

void Manger::Pass_Account_A_S()
{
	bool Find = false;			//���ڼ�¼�Ƿ��ҵ�������ѧ��
	cout << "����Ϊ���д���˵�ѧ���˺���Ϣ" << endl;
	for (map<int, Account_Information>::iterator it = this->Login_In_List_S.begin(); it != this->Login_In_List_S.end(); it++)
	{
		if (it->second.Condition == "�����")
		{
			cout << it->first << " ";
			it->second.Show_Information();
			Find = true;			//�ҵ��˴������˺�
		}
	}
	if (!Find)			//û���ҵ��������˺�
	{
		cout << "û�д�������ѧ���˺�" << endl;
		return;
	}
	/*�ҵ��˴������˺�*/
	int Number;		//����
	cout << "����������Ҫ�����ĵ���" << endl;
	cin >> Number;
	map<int, Account_Information>::iterator it2 = this->Login_In_List_S.find(Number);		//�����뵥����ͬ��
	if (it2 != this->Login_In_List_S.end())
	{
		cout << "���ҵ��õ��ţ�����Ϊ�õ�����Ϣ" << endl;
		cout << it2->first << " ";
		it2->second.Show_Information();

		int Choice;			//����ѡ��
		cout << "��Ҫͨ�����룬������1" << endl;
		cout << "����ͨ�����룬������0" << endl;
		cin >> Choice;

		while (Choice != 1 && Choice != 0)
		{
			cout << "��������Ƿ�������������" << endl;
			cin >> Choice;
		}
		if (Choice == 1)
			it2->second.Condition = "ͨ��";				//�޸ĸõ���״̬
		else
			it2->second.Condition = "δͨ��";
		cout << "��������" << endl;
		this->Update_Login_In_S();					//��д�õ�����Ϣ
	}
	else
	{
		cout << "δ�ҵ��õ�����Ϣ" << endl;
	}
}

void Manger::Pass_Account_A_T()
{
	bool Find = false;
	cout << "����Ϊ���д���˵Ľ�ʦ�˺���Ϣ" << endl;
	for (map<int, Account_Information>::iterator it = this->Login_In_List_T.begin(); it != this->Login_In_List_T.end(); it++)
	{
		if (it->second.Condition == "�����")
		{
			Find = true;			//�ҵ��˴������˺�
			cout << it->first << " ";
			it->second.Show_Information();
		}
	}
	if (!Find)				//û�ҵ��������˺�
	{
		cout << "δ�ҵ��������˺�" << endl;
		return;
	}
	/*�ҵ��˴������˺�*/
	int Number;		//����
	cout << "����������Ҫ�����ĵ���" << endl;
	cin >> Number;
	map<int, Account_Information>::iterator it2 = this->Login_In_List_T.find(Number);		//�����뵥����ͬ��
	if (it2 != this->Login_In_List_T.end())
	{
		cout << "���ҵ��õ��ţ�����Ϊ�õ�����Ϣ" << endl;
		cout << it2->first << " ";
		it2->second.Show_Information();

		int Choice;			//����ѡ��
		cout << "��Ҫͨ�����룬������1" << endl;
		cout << "����ͨ�����룬������0" << endl;
		cin >> Choice;

		while (Choice != 1 && Choice != 0)
		{
			cout << "��������Ƿ�������������" << endl;
			cin >> Choice;
		}
		if (Choice == 1)
			it2->second.Condition = "ͨ��";				//�޸ĸõ��ŵ�״̬
		else
			it2->second.Condition = "δͨ��";
		cout << "��������" << endl;
		this->Update_Login_In_T();				//��д�õ�����Ϣ
	}
	else
	{
		cout << "δ�ҵ��õ�����Ϣ" << endl;
	}
}

void Manger::Show_All_Account()			//չʾ�����˺���Ϣ
{
	int Choice;
	cout << "Ҫ�鿴ѧ���˺ţ������� 1" << endl;
	cout << "Ҫ�鿴��ʦ�˺ţ������� 2" << endl;
	cin >> Choice;
	while (Choice != 1 && Choice != 2)
	{
		cout << "�������벻�Ϸ�������������" << endl;
		cin >> Choice;
	}
	if (Choice == 1)
	{
		this->Show_All_S_Account();			//ѧ��
	}
	else if (Choice == 2)
	{
		this->Show_All_T_Account();			//��ʦ
	}
}

void Manger::Show_All_S_Account()			//չʾ����ѧ���˺���Ϣ
{
	cout << "����Ϊ����ѧ���˺ŵ���Ϣ" << endl;
	for (map<int, Account_Information>::iterator it = this->Login_In_List_S.begin(); it != this->Login_In_List_S.end(); it++)
	{
		if (it->second.Condition == "ͨ��")
		{
			it->second.Show_Information();
		}
	}
	cout << "����Ҫ�鿴ĳλѧ��������ԤԼ������������ѧ���˺ţ���Ҫ�˳���������0" << endl;
	string Account_Choice;			//������˺Ż����˳�
	cin >> Account_Choice;
	if (Account_Choice == "0")
	{
		return;			//�˳�
	}
	else
	{
		cout << "����Ϊ��ѧ�����е�ԤԼ���" << endl;
		Student stu;			//����һ��ѧ��
		for (int i = 0; i < Account_Choice.length(); i++)			//ʹ��ѧ���˺�����Ҫ���ҵ�ѧ���˺���Ϣ��ͬ
			stu.Admin_Number[i] = Account_Choice[i];
		stu.Show_All_My_Apply();			//չʾ��ѧ������ԤԼ���
	}
}

void Manger::Show_All_T_Account()			//չʾ����ѧ���˺���Ϣ
{
	cout << "����Ϊ���н�ʦ�˺ŵ���Ϣ" << endl;
	for (map<int, Account_Information>::iterator it = this->Login_In_List_T.begin(); it != this->Login_In_List_T.end(); it++)
	{
		if (it->second.Condition == "ͨ��")
		{
			it->second.Show_Information();
		}
	}
}

void Manger::Show_All_Apply()
{
	cout << "����Ϊ����ԤԼ��Ϣ" << endl;
	COS cos;
	/*��������ԤԼ��Ϣ��չʾ���е�ԤԼ��Ϣ*/
	for (map<int, Computer_Information>::iterator it = cos.CI_mp.begin(); it != cos.CI_mp.end(); it++)
		for (multimap<int, Single_Computer>::iterator it2 = it->second.SC_mp.begin(); it2 != it->second.SC_mp.end(); it2++)
		{
			it2->second.Show_Information();
		}
}

void Manger::Add_CI()
{
	COS cos;
	int CR_Number;		//�������
	int Cap;		//����
	int Start_Number;			//��ʼ���
	cout << "��������Ҫ�����Ļ������" << endl;
	cin >> CR_Number;
	cout << "������û������������" << endl;
	cin >> Cap;
	cout << "������û����ĵ�һ̨���Եı��" << endl;
	cin >> Start_Number;
	cos.static_CI_mp.insert(make_pair(CR_Number, Computer_Information(CR_Number, Cap, Start_Number)));
	cos.Update_Static_SC();
	
	cout << "������ӳɹ�" << endl;
}

void Manger::Change_CI_Change()
{
	COS cos;
	int For_Change_CR_Number;		//Ҫ���޸ĵĻ������
	int CR_Number;		//�������
	int Cap;		//����
	int Start_Number;			//��ʼ���
	cout << "����������Ҫ�޸ĵĻ����ı��" << endl;
	cin >> For_Change_CR_Number;
	cout << "�������޸ĺ�Ļ������" << endl;
	cin >> CR_Number;
	cout << "������û������������" << endl;
	cin >> Cap;
	cout << "������û����ĵ�һ̨���Եı��" << endl;
	cin >> Start_Number;
	cos.static_CI_mp.erase(cos.static_CI_mp.find(For_Change_CR_Number));
	cos.static_CI_mp.insert(make_pair(CR_Number, Computer_Information(CR_Number, Cap, Start_Number)));
	cos.Update_Static_SC();
	cout << "������Ϣ�޸ĳɹ�" << endl;
}


void Manger::Change_CI()
{
	cout << "����Ϊ��ǰ���л�����Ϣ" << endl;
	COS cos;
	cos.Show_All_CI();
	cout << endl;
	cout << "���Ҫ��ӻ�����������1" << endl;
	cout << "���Ҫ�޸Ļ�����Ϣ��������2" << endl;

	int Choice;			//ѡ��
	cin >> Choice;
	while (Choice != 1 && Choice != 2)
	{
		cout << "��������Ƿ�������������" << endl;
		cin >> Choice;
	}
	if (Choice == 1)
	{
		this->Add_CI();		//��ӻ���
	}
	else
	{
		this->Change_CI_Change();			//�޸Ļ�����Ϣ
	}
}