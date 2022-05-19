#pragma once
#include<iostream>
#include<string>
#include<map>
#include"ComputerOrderSystem.h"
#include"AccountInformation.h"
using namespace std;
#define Login_T_A "Login_T_A.txt"

class Teacher
{
public:
	Teacher();
	~Teacher();
	//登陆前
	void Teacher_main();			//教师登录主界面

	void Show_Register_Menu();			//展示登录界面

	int Get_Now_Number();			//获取当前最新注册的单号

	void T_Login_In();			//教师注册

	void Read_Login_In();			//读取已经通过的账号
	//登陆后
	void Teacher_Using_menu();		//操作界面显示

	void Teacher_Using_main();		//操作主界面

	void Pass_Apply();		//通过预约申请

	void Show_All_Apply();			//展示所有预约信息

	int Now_Number;					//现在的单号

	char Admin_Number[20];			//登录账号

	map<string, Account_Information>Login_In_List;		//注册账号的表
};