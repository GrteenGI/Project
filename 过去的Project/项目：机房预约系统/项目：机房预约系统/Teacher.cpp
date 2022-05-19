#include"Teacher.h"

Teacher::Teacher()
{
	this->Read_Login_In();
}

Teacher::~Teacher()
{

}

void Teacher::Show_Register_Menu()
{
	cout << "��ʦ�˵�¼��ڣ�" << endl;
	cout << "�������˻���������" << endl;
	cout << endl;
	cout << "û���˺ţ������˺Ŵ�����Login����ע��" << endl;
}

void Teacher::T_Login_In()
{
	string S_L_Account;
	string S_L_Password;
	string temp;
	cout << "��������Ҫע����˺�" << endl;
	cin >> S_L_Account;
	while (S_L_Account == "Login" || this->Login_In_List.count(S_L_Account) == 1)
	{
		cout << "ע���˺ŷǷ����Ѵ��ڣ�����������" << endl;
		cin >> S_L_Account;
	}
	cout << "����������" << endl;
	cin >> S_L_Password;
	temp = S_L_Password;
	cout << "���ٴ���������" << endl;
	cin >> S_L_Password;
	while (S_L_Password != temp)
	{
		cout << "�������벻һ�£����������룡" << endl;
		cin >> S_L_Password;
	}
	system("cls");
	cout << "ע�������ѷ����������ĵȴ���" << endl;
	ofstream ofs;
	ofs.open(Login_T_A, ios::app);
	ofs <</*����*/++this->Now_Number << " " <</*�����˺�*/S_L_Account << " " <</*��������*/S_L_Password << " " <</*���״̬*/"�����" << endl;
	ofs.close();
}

int Teacher::Get_Now_Number()			//��ȡ�������
{
	int num = 1000;
	ifstream ifs;
	ifs.open(Login_T_A, ios::in);
	char buf[1024] = { 0 };
	while (ifs.getline(buf, sizeof(buf)))
	{
		num++;
	}
	ifs.close();
	return num;
}

void Teacher::Read_Login_In()			//��ȡ�˺�������ͨ����
{
	this->Now_Number = this->Get_Now_Number();
	ifstream ifs;
	ifs.open(Login_T_A, ios::in);

	int Number;
	string S_L_Account;
	string S_L_Password;
	string Condition;

	while (ifs >> Number && ifs >> S_L_Account && ifs >> S_L_Password && ifs >> Condition)
	{
		if (Condition == "ͨ��")
		{
			this->Login_In_List.insert(make_pair(S_L_Account, Account_Information(S_L_Account, S_L_Password, Condition)));
		}
	}
	ifs.close();
}

void Teacher::Teacher_main()
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
		if (Register_Choice == "Login")
		{
			this->T_Login_In();
		}
		else if (Register_Choice == "0")
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
				this->Teacher_Using_main();
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

void Teacher::Teacher_Using_menu()
{
	cout << "��ӭ����ԤԼϵͳ  ��ʦ��" << endl;
	cout << "1.����ѧ��ԤԼ" << endl;
	cout << "2.�鿴����ԤԼ" << endl;
	cout << "0.ע����¼" << endl;
}

void Teacher::Teacher_Using_main()
{
	string choicenum;
	while (1)
	{
		this->Teacher_Using_menu();
		cout << "����������ѡ��" << endl;
		cin >> choicenum;
		if (choicenum == "1")			//����ѧ��ԤԼ
		{
			this->Pass_Apply();
			system("pause");
			system("cls");
		}
		else if (choicenum == "2")		//չʾ����ԤԼ
		{
			this->Show_All_Apply();
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

void Teacher::Pass_Apply()
{
	int Order = 0;
	int Passnum = 0;
	bool Find = false;
	bool Findany = false;
	cout << "����Ϊ������ԤԼ" << endl;
	COS cos;
	for (map<int, Computer_Information>::iterator it = cos.CI_mp.begin(); it != cos.CI_mp.end(); it++)
		for (multimap<int, Single_Computer>::iterator it2 = it->second.SC_mp.begin(); it2 != it->second.SC_mp.end(); it2++)
		{
			if (it2->second.Condition == 0)
			{
				Findany = true;
				it2->second.Show_Information();
			}
		}
	if (Findany)
	{
		cout << "��������Ҫ��˵�ԤԼ����" << endl;
		cin >> Order;
		for (map<int, Computer_Information>::iterator it = cos.CI_mp.begin(); it != cos.CI_mp.end(); it++)
			for (multimap<int, Single_Computer>::iterator it2 = it->second.SC_mp.begin(); it2 != it->second.SC_mp.end(); it2++)
			{
				if (it2->second.Order_Number == Order && it2->second.Condition == 0)
				{
					cout << "�õ�����Ϣ��" << endl;
					it2->second.Show_Information();
					cout << "��Ҫͨ����������1��������׼��������2" << endl;
					cin >> Passnum;
					while (Passnum != 1 && Passnum != 2)
					{
						cout << "�������벻�Ϸ�������������" << endl;
						cin >> Passnum;
					}
					it2->second.Condition = Passnum;
					cos.Update_SC();			//д���޸ĺ��map����������ԤԼ��Ϣ
					Find = true;		//�����ҵ��õ���
				}
			}
		if (!Find)
		{
			cout << "�õ��Ų����ڻ����������" << endl;
		}
	}
	else
	{
		cout << "û����Ҫ������ԤԼ" << endl;
	}
}

//չʾ����ԤԼ��Ϣ
void Teacher::Show_All_Apply()
{
	cout << "����Ϊ����ԤԼ��Ϣ" << endl;
	COS cos;
	for (map<int, Computer_Information>::iterator it = cos.CI_mp.begin(); it != cos.CI_mp.end(); it++)
		for (multimap<int, Single_Computer>::iterator it2 = it->second.SC_mp.begin(); it2 != it->second.SC_mp.end(); it2++)
		{
			it2->second.Show_Information();
		}
}