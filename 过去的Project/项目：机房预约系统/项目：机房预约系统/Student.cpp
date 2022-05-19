#include"Student.h"



Student::Student()
{
	this->Read_Login_In();
}
Student::~Student()
{

}

void Student::Student_main()			//��¼��������
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
			this->Login_In();
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
				this->Student_Using_main();
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

void Student::Show_Register_Menu()
{
	cout << "ѧ���˵�¼��ڣ�" << endl;
	cout << "�������˻���������" << endl;
	cout << endl;
	cout << "û���˺ţ������˺Ŵ�����Login����ע��" << endl;
}

void Student::Login_In()			//ע���˺�
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
	ofs.open(Login_S_A, ios::app);
	ofs <</*����*/++this->Now_Number << " " <</*�����˺�*/S_L_Account << " " <</*��������*/S_L_Password << " " <</*���״̬*/"�����" << endl;
	ofs.close();
}

void Student::Read_Login_In()			//��ȡ�˺�������ͨ����
{
	this->Now_Number = this->Get_Now_Number();
	ifstream ifs;
	ifs.open(Login_S_A, ios::in);

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

int Student::Get_Now_Number()			//��ȡ�������
{
	int num = 1000;
	ifstream ifs;
	ifs.open(Login_S_A, ios::in);
	char buf[1024] = { 0 };
	while (ifs.getline(buf, sizeof(buf)))
	{
		num++;
	}
	ifs.close();
	return num;
}
void Student::Student_Using_menu()
{
	cout << "��ӭʹ�û���ԤԼϵͳ  ѧ����" << endl;
	cout << "1.����ԤԼ����" << endl;
	cout << "2.�鿴�ҵ�ԤԼ" << endl;
	cout << "3.ȡ��ԤԼ" << endl;
	cout << "0.ע����¼" << endl;
}

void Student::Student_Using_main()
{
	string choicenum;
	while (1)
	{
		COS cos;
		this->Student_Using_menu();
		cout << endl;
		cout << "���л�������" << endl;
		cos.Show_All_CI();
		cout << endl;
		cout << "����������ѡ��" << endl;
		cin >> choicenum;
		if (choicenum == "1")			//����ԤԼ����
		{
			this->Apply_For_Computer();
			system("pause");
			system("cls");
		}	
		else if (choicenum == "2")		//�鿴�ҵ�ԤԼ
		{
			cout << "��������������ԤԼ" << endl;
			this->Show_All_My_Apply();
			system("pause");
			system("cls");
		}
		else if (choicenum == "3")		//ȡ��ԤԼ
		{
			cout << "��������������ԤԼ" << endl;
			this->delete_My_Apply();
			system("pause");
			system("cls");
		}
		else if (choicenum == "0")		//ע��
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

void Student::Apply_For_Computer()
{
	COS cos;
	int Room_Number;
	int C_Number;
	int Year;
	int Month;
	int Day;
	int Hour;
	int Minute;
	cout << "����������ҪԤԼ�Ļ������" << endl;
	cin >> Room_Number;
	cout << "����������ҪԤԼ�ĵ��Ա��" << endl;
	cin >> C_Number;
	cout << endl;
	/*չʾ��̨���Ե�����ԤԼ*/
	if (cos.static_CI_mp.find(Room_Number) == cos.static_CI_mp.end())		//���û�ҵ��û���
	{
		cout << "�û���������" << endl;
		return;
	}
	map<int, Computer_Information>::iterator it2 = cos.static_CI_mp.find(Room_Number);		//�û����ĵ�����
	if (it2->second.SC_mp.find(C_Number) == it2->second.SC_mp.end())			//���û�ҵ��õ���
	{
		cout << "�õ��Բ�����" << endl;
		return;
	}
	map<int, Computer_Information>::iterator it = cos.CI_mp.find(Room_Number);		//ԤԼ�ļ��иû����ĵ�����
	if (it == cos.CI_mp.end())
	{
		cout << "�õ�����ʱû�м�¼" << endl;
	}
	else
	{
		multimap<int, Single_Computer>::iterator it3 = it->second.SC_mp.find(C_Number);
		if (it3 == it->second.SC_mp.end())			//���ԤԼ�ļ���û�иõ���
		{
			cout << "�õ�����ʱû��ԤԼ��¼" << endl;
		}
		else
		{
			cout << "����Ϊ�õ��Ե�ԤԼ���" << endl;
			for (int i = 0; i < cos.CI_mp.find(Room_Number)->second.SC_mp.count(C_Number); i++)		//չʾ�õ�������ԤԼ
			{
				it3->second.Show_Information();
				it3++;
			}
		}

	}
	/*����ʱ��*/
	cout << "����������ҪԤԼ�Ŀ�ʼʱ��" << endl;
	cout << "�꣺";
	cin >> Year;
	cout << "�£�";
	cin >> Month;
	cout << "�գ�";
	cin >> Day;
	cout << "ʱ��";
	cin >> Hour;
	cout << "�֣�";
	cin >> Minute;
	Time B(Year, Month, Day, Hour, Minute);
	cout << "����������ҪԤԼ�Ľ���ʱ���" << endl;
	cout << "�꣺";
	cin >> Year;
	cout << "�£�";
	cin >> Month;
	cout << "�գ�";
	cin >> Day;
	cout << "ʱ��";
	cin >> Hour;
	cout << "�֣�";
	cin >> Minute;
	Time E(Year, Month, Day, Hour, Minute);
	ofstream ofs;
	ofs.open(SC, ios::app | ios::binary);
	/*д���ԤԼ*/
	Single_Computer C(cos.SC_O_Number + 1, Room_Number, C_Number, B, E, this->Admin_Number, 0);
	ofs.write((const char*)&C, sizeof(C));
	ofs.close();
	cout << "ԤԼ����ѳ����������ĵȴ�" << endl;
}

void Student::Show_All_My_Apply()
{
	/*������ԤԼ�˺��˺���ͬ��չʾ*/
	COS cos;
	for (map<int, Computer_Information>::iterator it = cos.CI_mp.begin(); it != cos.CI_mp.end(); it++)
		for (multimap<int, Single_Computer>::iterator it2 = it->second.SC_mp.begin(); it2 != it->second.SC_mp.end(); it2++)
		{
			if ((string)it2->second.Apply_Number == (string)this->Admin_Number)
			{
				it2->second.Show_Information();
			}
		}
}

void Student::delete_My_Apply()
{
	int Order = 0;
	COS cos;
	/*չʾ����ԤԼ*/
	this->Show_All_My_Apply();
	cout << endl;
	cout << "����������Ҫȡ��ԤԼ�ĵ���" << endl;
	cin >> Order;
	/*�����ҳ�������ͬ�ߣ�ɾ��*/
	for (map<int, Computer_Information>::iterator it = cos.CI_mp.begin(); it != cos.CI_mp.end(); it++)
		for (multimap<int, Single_Computer>::iterator it2 = it->second.SC_mp.begin(); it2 != it->second.SC_mp.end(); it2++)
		{
			if ((string)it2->second.Apply_Number == (string)this->Admin_Number)
			{
				if (it2->second.Order_Number == Order)
				{
					it->second.SC_mp.erase(it2);
					cos.Update_SC();			//д��ɾ�����map����������ԤԼ��Ϣ
					cout << "����ԤԼȡ���ɹ���" << endl;
					return;
				}
			}
		}
}