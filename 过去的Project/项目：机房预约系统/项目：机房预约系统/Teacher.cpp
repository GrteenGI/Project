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
	cout << "教师端登录入口：" << endl;
	cout << "请输入账户名和密码" << endl;
	cout << endl;
	cout << "没有账号？请在账号处输入Login进行注册" << endl;
}

void Teacher::T_Login_In()
{
	string S_L_Account;
	string S_L_Password;
	string temp;
	cout << "请输入您要注册的账号" << endl;
	cin >> S_L_Account;
	while (S_L_Account == "Login" || this->Login_In_List.count(S_L_Account) == 1)
	{
		cout << "注册账号非法或已存在！请重新输入" << endl;
		cin >> S_L_Account;
	}
	cout << "请输入密码" << endl;
	cin >> S_L_Password;
	temp = S_L_Password;
	cout << "请再次输入密码" << endl;
	cin >> S_L_Password;
	while (S_L_Password != temp)
	{
		cout << "两次密码不一致，请重新输入！" << endl;
		cin >> S_L_Password;
	}
	system("cls");
	cout << "注册请求已发出，请耐心等待！" << endl;
	ofstream ofs;
	ofs.open(Login_T_A, ios::app);
	ofs <</*单号*/++this->Now_Number << " " <</*申请账号*/S_L_Account << " " <</*申请密码*/S_L_Password << " " <</*审核状态*/"待审核" << endl;
	ofs.close();
}

int Teacher::Get_Now_Number()			//获取最近单号
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

void Teacher::Read_Login_In()			//读取账号申请中通过者
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
		if (Condition == "通过")
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
		cout << "请输入账号" << endl;
		cout << "若要返回上一界面请输入0" << endl;
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
			cout << "请输入密码" << endl;
			cin >> Password;
			/*找到通过的账号中跟输入账号相同者*/
			if (this->Login_In_List.size() && this->Login_In_List.find(Register_Choice) != Login_In_List.end() && Password == this->Login_In_List.find(Register_Choice)->second.Password)
			{
				cout << "登录成功！" << endl;
				system("pause");
				system("cls");
				for (int i = 0; i < Register_Choice.length(); i++)			//记录当前系统登录的账号
					this->Admin_Number[i] = Register_Choice[i];
				this->Teacher_Using_main();
			}
			else
			{
				cout << "账号不存在或密码错误" << endl;
				system("pause");
				system("cls");
			}
		}
	}
}

void Teacher::Teacher_Using_menu()
{
	cout << "欢迎机房预约系统  教师端" << endl;
	cout << "1.审批学生预约" << endl;
	cout << "2.查看所有预约" << endl;
	cout << "0.注销登录" << endl;
}

void Teacher::Teacher_Using_main()
{
	string choicenum;
	while (1)
	{
		this->Teacher_Using_menu();
		cout << "请输入您的选项" << endl;
		cin >> choicenum;
		if (choicenum == "1")			//审批学生预约
		{
			this->Pass_Apply();
			system("pause");
			system("cls");
		}
		else if (choicenum == "2")		//展示所有预约
		{
			this->Show_All_Apply();
			system("pause");
			system("cls");
		}
		else if (choicenum == "0")			//注销
		{
			system("cls");
			break;
		}
		else
		{
			cout << "输入非法，请重新输入" << endl;
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
	cout << "以下为待审批预约" << endl;
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
		cout << "请输入您要审核的预约单号" << endl;
		cin >> Order;
		for (map<int, Computer_Information>::iterator it = cos.CI_mp.begin(); it != cos.CI_mp.end(); it++)
			for (multimap<int, Single_Computer>::iterator it2 = it->second.SC_mp.begin(); it2 != it->second.SC_mp.end(); it2++)
			{
				if (it2->second.Order_Number == Order && it2->second.Condition == 0)
				{
					cout << "该单号信息：" << endl;
					it2->second.Show_Information();
					cout << "若要通过，请输入1，若不批准，请输入2" << endl;
					cin >> Passnum;
					while (Passnum != 1 && Passnum != 2)
					{
						cout << "您的输入不合法，请重新输入" << endl;
						cin >> Passnum;
					}
					it2->second.Condition = Passnum;
					cos.Update_SC();			//写入修改后的map容器内所有预约信息
					Find = true;		//标明找到该单号
				}
			}
		if (!Find)
		{
			cout << "该单号不存在或已审批完毕" << endl;
		}
	}
	else
	{
		cout << "没有需要审批的预约" << endl;
	}
}

//展示所有预约信息
void Teacher::Show_All_Apply()
{
	cout << "以下为所有预约信息" << endl;
	COS cos;
	for (map<int, Computer_Information>::iterator it = cos.CI_mp.begin(); it != cos.CI_mp.end(); it++)
		for (multimap<int, Single_Computer>::iterator it2 = it->second.SC_mp.begin(); it2 != it->second.SC_mp.end(); it2++)
		{
			it2->second.Show_Information();
		}
}