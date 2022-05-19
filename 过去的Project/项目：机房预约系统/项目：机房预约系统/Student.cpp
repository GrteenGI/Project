#include"Student.h"



Student::Student()
{
	this->Read_Login_In();
}
Student::~Student()
{

}

void Student::Student_main()			//登录操作界面
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
			this->Login_In();
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
				this->Student_Using_main();
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

void Student::Show_Register_Menu()
{
	cout << "学生端登录入口：" << endl;
	cout << "请输入账户名和密码" << endl;
	cout << endl;
	cout << "没有账号？请在账号处输入Login进行注册" << endl;
}

void Student::Login_In()			//注册账号
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
	ofs.open(Login_S_A, ios::app);
	ofs <</*单号*/++this->Now_Number << " " <</*申请账号*/S_L_Account << " " <</*申请密码*/S_L_Password << " " <</*审核状态*/"待审核" << endl;
	ofs.close();
}

void Student::Read_Login_In()			//读取账号申请中通过者
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
		if (Condition == "通过")
		{
			this->Login_In_List.insert(make_pair(S_L_Account, Account_Information(S_L_Account, S_L_Password, Condition)));
		}
	}
	ifs.close();
}

int Student::Get_Now_Number()			//获取最近单号
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
	cout << "欢迎使用机房预约系统  学生端" << endl;
	cout << "1.申请预约机房" << endl;
	cout << "2.查看我的预约" << endl;
	cout << "3.取消预约" << endl;
	cout << "0.注销登录" << endl;
}

void Student::Student_Using_main()
{
	string choicenum;
	while (1)
	{
		COS cos;
		this->Student_Using_menu();
		cout << endl;
		cout << "现有机房如下" << endl;
		cos.Show_All_CI();
		cout << endl;
		cout << "请输入您的选项" << endl;
		cin >> choicenum;
		if (choicenum == "1")			//申请预约机房
		{
			this->Apply_For_Computer();
			system("pause");
			system("cls");
		}	
		else if (choicenum == "2")		//查看我的预约
		{
			cout << "以下是您的所有预约" << endl;
			this->Show_All_My_Apply();
			system("pause");
			system("cls");
		}
		else if (choicenum == "3")		//取消预约
		{
			cout << "以下是您的所有预约" << endl;
			this->delete_My_Apply();
			system("pause");
			system("cls");
		}
		else if (choicenum == "0")		//注销
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
	cout << "请输入您想要预约的机房编号" << endl;
	cin >> Room_Number;
	cout << "请输入您想要预约的电脑编号" << endl;
	cin >> C_Number;
	cout << endl;
	/*展示这台电脑的所有预约*/
	if (cos.static_CI_mp.find(Room_Number) == cos.static_CI_mp.end())		//如果没找到该机房
	{
		cout << "该机房不存在" << endl;
		return;
	}
	map<int, Computer_Information>::iterator it2 = cos.static_CI_mp.find(Room_Number);		//该机房的迭代器
	if (it2->second.SC_mp.find(C_Number) == it2->second.SC_mp.end())			//如果没找到该电脑
	{
		cout << "该电脑不存在" << endl;
		return;
	}
	map<int, Computer_Information>::iterator it = cos.CI_mp.find(Room_Number);		//预约文件中该机房的迭代器
	if (it == cos.CI_mp.end())
	{
		cout << "该电脑暂时没有记录" << endl;
	}
	else
	{
		multimap<int, Single_Computer>::iterator it3 = it->second.SC_mp.find(C_Number);
		if (it3 == it->second.SC_mp.end())			//如果预约文件中没有该电脑
		{
			cout << "该电脑暂时没有预约记录" << endl;
		}
		else
		{
			cout << "以下为该电脑的预约情况" << endl;
			for (int i = 0; i < cos.CI_mp.find(Room_Number)->second.SC_mp.count(C_Number); i++)		//展示该电脑所有预约
			{
				it3->second.Show_Information();
				it3++;
			}
		}

	}
	/*创建时间*/
	cout << "请输入您想要预约的开始时间" << endl;
	cout << "年：";
	cin >> Year;
	cout << "月：";
	cin >> Month;
	cout << "日：";
	cin >> Day;
	cout << "时：";
	cin >> Hour;
	cout << "分：";
	cin >> Minute;
	Time B(Year, Month, Day, Hour, Minute);
	cout << "请输入您想要预约的结束时间段" << endl;
	cout << "年：";
	cin >> Year;
	cout << "月：";
	cin >> Month;
	cout << "日：";
	cin >> Day;
	cout << "时：";
	cin >> Hour;
	cout << "分：";
	cin >> Minute;
	Time E(Year, Month, Day, Hour, Minute);
	ofstream ofs;
	ofs.open(SC, ios::app | ios::binary);
	/*写入该预约*/
	Single_Computer C(cos.SC_O_Number + 1, Room_Number, C_Number, B, E, this->Admin_Number, 0);
	ofs.write((const char*)&C, sizeof(C));
	ofs.close();
	cout << "预约审核已出发，请耐心等待" << endl;
}

void Student::Show_All_My_Apply()
{
	/*遍历，预约人和账号相同者展示*/
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
	/*展示所有预约*/
	this->Show_All_My_Apply();
	cout << endl;
	cout << "请输入您想要取消预约的单号" << endl;
	cin >> Order;
	/*遍历找出单号相同者，删除*/
	for (map<int, Computer_Information>::iterator it = cos.CI_mp.begin(); it != cos.CI_mp.end(); it++)
		for (multimap<int, Single_Computer>::iterator it2 = it->second.SC_mp.begin(); it2 != it->second.SC_mp.end(); it2++)
		{
			if ((string)it2->second.Apply_Number == (string)this->Admin_Number)
			{
				if (it2->second.Order_Number == Order)
				{
					it->second.SC_mp.erase(it2);
					cos.Update_SC();			//写入删除后的map容器内所有预约信息
					cout << "您的预约取消成功！" << endl;
					return;
				}
			}
		}
}