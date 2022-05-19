#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<map>
#include"ComputerOrderSystem.h"
#include"AccountInformation.h"

#define Login_S_A "Login_S_A.txt"
using namespace std;

class Student
{
public:
	Student();

	~Student();
	/*登录前*/

	void Student_main();			//登录主页面

	void Show_Register_Menu();		//登录显示

	void Login_In();				//注册操作

	void Read_Login_In();			//读取注册完的账号

	int Get_Now_Number();			//获取当前最新注册的单号

	/*登录后的界面*/
	void Student_Using_menu();		//操作界面显示

	void Student_Using_main();		//操作主界面

	void Apply_For_Computer();		//申请机房

	void Show_All_My_Apply();			//显示我的申请

	void delete_My_Apply();			//取消预约

	map<string, Account_Information>Login_In_List;			//注册账号的表

	int Now_Number;					//现在的单号

	char Admin_Number[20];			//登录账号
};