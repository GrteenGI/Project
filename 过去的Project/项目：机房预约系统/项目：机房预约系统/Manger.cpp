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
	cout << "管理员登录入口：" << endl;
	cout << "请输入账户名和密码" << endl;
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
		cout << "请输入账号" << endl;
		cout << "若要返回上一界面请输入0" << endl;
		cin >> Register_Choice;
		if (Register_Choice == "0")
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
				this->Manger_Using_main();
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

void Manger::Read_Login_In()			//读取账号申请中通过者
{
	ifstream ifs;
	ifs.open(Login_M_A, ios::in);

	string S_L_Account;
	string S_L_Password;
	string Condition;

	while (ifs >> S_L_Account && ifs >> S_L_Password && ifs >> Condition)
	{
		if (Condition == "通过")
		{
			this->Login_In_List.insert(make_pair(S_L_Account, Account_Information(S_L_Account, S_L_Password, Condition)));
		}
	}
	ifs.close();
}

void Manger::Read_Login_In_ST()		//读取所有学生和教师的账号申请信息
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
	cout << "欢迎机房预约系统  管理员" << endl;
	cout << "1.审批账号申请" << endl;
	cout << "2.查看账号信息" << endl;
	cout << "3.查看所有预约" << endl;
	cout << "4.修改机房信息" << endl;
	cout << "5.展示机房信息" << endl;
	cout << "0.注销登录" << endl;
}

void Manger::Manger_Using_main()
{
	string choicenum;
	while (1)
	{
		this->Manger_Using_menu();
		cout << "请输入您的选项" << endl;
		cin >> choicenum;
		if (choicenum == "1")			//审批账号申请
		{
			this->Pass_Account_A();
			system("pause");
			system("cls");
		}
		else if (choicenum == "2")		//查看账号信息
		{
			this->Show_All_Account();
			system("pause");
			system("cls");
		}
		else if (choicenum == "3")		//查看所有预约
		{
			this->Show_All_Apply();
			system("pause");
			system("cls");
		}
		else if (choicenum == "4")			//修改机房信息
		{
			this->Change_CI();
			system("pause");
			system("cls");
		}
		else if (choicenum == "5")			//展示机房所有信息
		{
			COS cos;;
			cos.Show_All_CI();
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

void Manger::Pass_Account_A()			//审批账号申请
{
	int Choice;
	cout << "要查看学生账号申请，请输入 1" << endl;
	cout << "要查看教师账号申请，请输入 2" << endl;
	cin >> Choice;
	while (Choice != 1 && Choice != 2)
	{
		cout << "您的输入不合法，请重新输入" << endl;
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
	bool Find = false;			//用于记录是否找到待审批学生
	cout << "以下为所有待审核的学生账号信息" << endl;
	for (map<int, Account_Information>::iterator it = this->Login_In_List_S.begin(); it != this->Login_In_List_S.end(); it++)
	{
		if (it->second.Condition == "待审核")
		{
			cout << it->first << " ";
			it->second.Show_Information();
			Find = true;			//找到了待审批账号
		}
	}
	if (!Find)			//没有找到待审批账号
	{
		cout << "没有待审批的学生账号" << endl;
		return;
	}
	/*找到了待审批账号*/
	int Number;		//单号
	cout << "请输入您想要审批的单号" << endl;
	cin >> Number;
	map<int, Account_Information>::iterator it2 = this->Login_In_List_S.find(Number);		//与输入单号相同者
	if (it2 != this->Login_In_List_S.end())
	{
		cout << "已找到该单号，以下为该单号信息" << endl;
		cout << it2->first << " ";
		it2->second.Show_Information();

		int Choice;			//审批选择
		cout << "若要通过申请，请输入1" << endl;
		cout << "若不通过申请，请输入0" << endl;
		cin >> Choice;

		while (Choice != 1 && Choice != 0)
		{
			cout << "您的输入非法，请重新输入" << endl;
			cin >> Choice;
		}
		if (Choice == 1)
			it2->second.Condition = "通过";				//修改该单号状态
		else
			it2->second.Condition = "未通过";
		cout << "审批结束" << endl;
		this->Update_Login_In_S();					//覆写该单号信息
	}
	else
	{
		cout << "未找到该单号信息" << endl;
	}
}

void Manger::Pass_Account_A_T()
{
	bool Find = false;
	cout << "以下为所有待审核的教师账号信息" << endl;
	for (map<int, Account_Information>::iterator it = this->Login_In_List_T.begin(); it != this->Login_In_List_T.end(); it++)
	{
		if (it->second.Condition == "待审核")
		{
			Find = true;			//找到了待审批账号
			cout << it->first << " ";
			it->second.Show_Information();
		}
	}
	if (!Find)				//没找到待审批账号
	{
		cout << "未找到待审批账号" << endl;
		return;
	}
	/*找到了待审批账号*/
	int Number;		//单号
	cout << "请输入您想要审批的单号" << endl;
	cin >> Number;
	map<int, Account_Information>::iterator it2 = this->Login_In_List_T.find(Number);		//与输入单号相同者
	if (it2 != this->Login_In_List_T.end())
	{
		cout << "已找到该单号，以下为该单号信息" << endl;
		cout << it2->first << " ";
		it2->second.Show_Information();

		int Choice;			//审批选择
		cout << "若要通过申请，请输入1" << endl;
		cout << "若不通过申请，请输入0" << endl;
		cin >> Choice;

		while (Choice != 1 && Choice != 0)
		{
			cout << "您的输入非法，请重新输入" << endl;
			cin >> Choice;
		}
		if (Choice == 1)
			it2->second.Condition = "通过";				//修改该单号的状态
		else
			it2->second.Condition = "未通过";
		cout << "审批结束" << endl;
		this->Update_Login_In_T();				//覆写该单号信息
	}
	else
	{
		cout << "未找到该单号信息" << endl;
	}
}

void Manger::Show_All_Account()			//展示所有账号信息
{
	int Choice;
	cout << "要查看学生账号，请输入 1" << endl;
	cout << "要查看教师账号，请输入 2" << endl;
	cin >> Choice;
	while (Choice != 1 && Choice != 2)
	{
		cout << "您的输入不合法，请重新输入" << endl;
		cin >> Choice;
	}
	if (Choice == 1)
	{
		this->Show_All_S_Account();			//学生
	}
	else if (Choice == 2)
	{
		this->Show_All_T_Account();			//教师
	}
}

void Manger::Show_All_S_Account()			//展示所有学生账号信息
{
	cout << "以下为所有学生账号的信息" << endl;
	for (map<int, Account_Information>::iterator it = this->Login_In_List_S.begin(); it != this->Login_In_List_S.end(); it++)
	{
		if (it->second.Condition == "通过")
		{
			it->second.Show_Information();
		}
	}
	cout << "若您要查看某位学生的所有预约情况，请输入该学生账号，若要退出，请输入0" << endl;
	string Account_Choice;			//输入的账号或者退出
	cin >> Account_Choice;
	if (Account_Choice == "0")
	{
		return;			//退出
	}
	else
	{
		cout << "以下为该学生所有的预约情况" << endl;
		Student stu;			//创建一个学生
		for (int i = 0; i < Account_Choice.length(); i++)			//使该学生账号与所要查找的学生账号信息相同
			stu.Admin_Number[i] = Account_Choice[i];
		stu.Show_All_My_Apply();			//展示该学生所有预约情况
	}
}

void Manger::Show_All_T_Account()			//展示所有学生账号信息
{
	cout << "以下为所有教师账号的信息" << endl;
	for (map<int, Account_Information>::iterator it = this->Login_In_List_T.begin(); it != this->Login_In_List_T.end(); it++)
	{
		if (it->second.Condition == "通过")
		{
			it->second.Show_Information();
		}
	}
}

void Manger::Show_All_Apply()
{
	cout << "以下为所有预约信息" << endl;
	COS cos;
	/*遍历所有预约信息，展示所有的预约信息*/
	for (map<int, Computer_Information>::iterator it = cos.CI_mp.begin(); it != cos.CI_mp.end(); it++)
		for (multimap<int, Single_Computer>::iterator it2 = it->second.SC_mp.begin(); it2 != it->second.SC_mp.end(); it2++)
		{
			it2->second.Show_Information();
		}
}

void Manger::Add_CI()
{
	COS cos;
	int CR_Number;		//机房编号
	int Cap;		//容量
	int Start_Number;			//初始编号
	cout << "请输入您要创建的机房编号" << endl;
	cin >> CR_Number;
	cout << "请输入该机房的最大容量" << endl;
	cin >> Cap;
	cout << "请输入该机房的第一台电脑的编号" << endl;
	cin >> Start_Number;
	cos.static_CI_mp.insert(make_pair(CR_Number, Computer_Information(CR_Number, Cap, Start_Number)));
	cos.Update_Static_SC();
	
	cout << "机房添加成功" << endl;
}

void Manger::Change_CI_Change()
{
	COS cos;
	int For_Change_CR_Number;		//要被修改的机房编号
	int CR_Number;		//机房编号
	int Cap;		//容量
	int Start_Number;			//初始编号
	cout << "请输入您想要修改的机房的编号" << endl;
	cin >> For_Change_CR_Number;
	cout << "请输入修改后的机房编号" << endl;
	cin >> CR_Number;
	cout << "请输入该机房的最大容量" << endl;
	cin >> Cap;
	cout << "请输入该机房的第一台电脑的编号" << endl;
	cin >> Start_Number;
	cos.static_CI_mp.erase(cos.static_CI_mp.find(For_Change_CR_Number));
	cos.static_CI_mp.insert(make_pair(CR_Number, Computer_Information(CR_Number, Cap, Start_Number)));
	cos.Update_Static_SC();
	cout << "机房信息修改成功" << endl;
}


void Manger::Change_CI()
{
	cout << "以下为当前所有机房信息" << endl;
	COS cos;
	cos.Show_All_CI();
	cout << endl;
	cout << "如果要添加机房，请输入1" << endl;
	cout << "如果要修改机房信息，请输入2" << endl;

	int Choice;			//选项
	cin >> Choice;
	while (Choice != 1 && Choice != 2)
	{
		cout << "您的输入非法，请重新输入" << endl;
		cin >> Choice;
	}
	if (Choice == 1)
	{
		this->Add_CI();		//添加机房
	}
	else
	{
		this->Change_CI_Change();			//修改机房信息
	}
}