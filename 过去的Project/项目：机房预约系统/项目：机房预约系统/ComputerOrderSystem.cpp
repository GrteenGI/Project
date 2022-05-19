#include"ComputerOrderSystem.h"
COS::COS()
{
	this->Read_SC_Apply();
	this->Read_SCI();
}

COS::~COS()
{

}

void COS::Show_MainMenu()		//页面
{
	cout << "欢迎使用你家健哥的机房预约系统!" << endl;
	cout << "1.学生端登录" << endl;
	cout << "2.教师端登录" << endl;
	cout << "3.管理员端登陆" << endl;
	cout << "0.退出系统" << endl;
}

void COS::Exit()			//退出
{
	cout << "感谢您的使用！" << endl;
	exit(0);
}

void COS::Update_SC()			//写入map容器内所有Single Computer的预约信息
{
	ofstream ofs;
	ofs.open(SC, ios::out | ios::binary);
	for (map<int, Computer_Information>::iterator it = this->CI_mp.begin(); it != this->CI_mp.end(); it++)
		for (multimap<int, Single_Computer>::iterator it2 = it->second.SC_mp.begin(); it2 != it->second.SC_mp.end(); it2++)
		{
			ofs.write((const char*)&(it2->second), sizeof(Single_Computer));
		}
	ofs.close();
}

void COS::Read_SC_Apply()			//读取所有预约信息
{
	fstream fs;
	fs.open(SC, ios::in | ios::binary);
	Single_Computer T[100];
	memset(T, 0, sizeof(T));
	this->SC_O_Number = 10000;			//最新单号
	fs.read((char*)&T, sizeof(Single_Computer) * 100);
	for (int i = 0; i < sizeof(T) / sizeof(T[0]); i++)
	{
		if (T[i].Order_Number)				//如果单号不为0
		{
			this->SC_O_Number = T[i].Order_Number;				//更新单号
			if (this->CI_mp.count(T[i].Belong_Number) == 0)			//如果没有该机房编号
				this->CI_mp.insert(make_pair(T[i].Belong_Number, Computer_Information()));		//则添加该机房
			this->CI_mp[T[i].Belong_Number].SC_mp.insert(make_pair(T[i].Number, T[i]));		//并将电脑塞入该机房
		}
	}
	fs.close();
}

void COS::Read_SCI()
{
	fstream fs;
	fs.open(SCI, ios::in | ios::binary);
	Single_Computer T[150];
	memset(T, 0, sizeof(T));
	fs.read((char*)&T, sizeof(Single_Computer) * 150);
	for (int i = 0; i < sizeof(T) / sizeof(T[0]); i++)
	{
		if (T[i].Belong_Number)				//如果该机房编号不为0
		{
			if (this->static_CI_mp.count(T[i].Belong_Number) == 0)			//如果没有该机房编号
			{
				this->static_CI_mp[T[i].Belong_Number].Max_Size = 0;
				this->static_CI_mp[T[i].Belong_Number].Number = T[i].Belong_Number;
				this->static_CI_mp.insert(make_pair(T[i].Belong_Number, Computer_Information()));
			}
			this->static_CI_mp[T[i].Belong_Number].SC_mp.insert(make_pair(T[i].Number, T[i]));
			this->static_CI_mp[T[i].Belong_Number].Max_Size++;
		}
	}
	fs.close();
}

void COS::Update_Static_SC()				//将所有电脑和机房信息写入文件
{
	ofstream ofs;
	ofs.open(SCI, ios::out | ios::binary);
	for (map<int, Computer_Information>::iterator it = this->static_CI_mp.begin(); it != this->static_CI_mp.end(); it++)
		for (multimap<int, Single_Computer>::iterator it2 = it->second.SC_mp.begin(); it2 != it->second.SC_mp.end(); it2++)
		{
			ofs.write((const char*)&(it2->second), sizeof(Single_Computer));
		}
	ofs.close();
}

void COS::Show_All_CI()		//展示所有机房信息
{
	for (map<int, Computer_Information>::iterator it = this->static_CI_mp.begin(); it != this->static_CI_mp.end(); it++)
	{
		it->second.Show_Information();
	}
}